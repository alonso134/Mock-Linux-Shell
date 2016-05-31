//
//  hw02.cpp
//  hw02
//
//  Created by Kaichen Xiao on 5/29/16.
//  Copyright © 2016 Kaichen Xiao. All rights reserved.
//

#include <iostream>
#include <iterator>
#include <sstream>
#include <algorithm>
#include <exception>
#include <string>
#include <vector>
#include <deque>
#include <unistd.h>
#include <cstring>
#include "hw02.h"

using namespace std;

int main() {
    string usr = getlogin();
    string input;
    vector<string> cmd;
    vector<pair<int, string>> cmd_h; // command history
    deque<string> cwd_h;             // dir history
    int pc = 1;
    
    char cwd[1024];
    string dir = getcwd(cwd, sizeof(cwd));
    cwd_h.push_front(dir);
    while (input != "quit") {
        cout << "<" << pc << ' ' << usr << "> ";
        getline(cin, input);
        
        // catch stepback command
        if (input[0] == '!') {
            input = CmdStepBack(input, cmd_h);
        }
        
        istringstream iss(input);
        if (input.size() != 0)
            cmd_h.push_back(make_pair(pc, input));
        if (cmd_h.size() > 10) {
            cmd_h.erase(cmd_h.begin());
        }
        copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(cmd));
        /*for (auto i = cmd.begin(); i != cmd.end(); i++) {
         cout << *i << ' ';
         }*/
        
        if (input.size() != 0) {
            if (cmd[0] == "date") {
                if (cmd.size() == 1) {
                    PrintDate();
                }
                else{
                    cout << "'date' command takes no argument.";
                }
            }
            
            else if (cmd[0] == "curr") {
                if (cmd.size() == 1) {
                    PrintCurrDirectory();
                }
                else{
                    cout << "'curr' command takes no argument.";
                }
            }
            
            else if (cmd[0] == "env") {
                if (cmd.size() == 1) {
                    DisplayVar();
                }
                else{
                    cout << "'env' command takes no argument.";
                }
            }
            
            // Change Directory
            else if (cmd[0] == "cd") {
                if (cmd.size() == 2) {
                    int dc;
                    if (cmd[1] != "~") {
                        const char *path = cmd[1].c_str();
                        dc = chdir(path);
                    }
                    else if (cmd[1][0] == '~' && cmd[1].size() != 1){
                        string homedir = "/user/" + cmd[1].substr(1, cmd[1].size() - 1);
                        dc = chdir(homedir.c_str());
                    }
                    else {
                        dc = chdir(getenv("HOME"));
                    }
                    if (cmd[1][0] == '#' && cmd[1].size() > 1) {
                        string subCmd =cmd[1].substr(1, cmd[1].size() - 1);
                        // check if the input after '#' is a number
                        for (int i = 0; i < subCmd.size(); i++) {
                            if (isdigit(subCmd[i])) {
                                int stepCount = stoi(subCmd);
                                // Check if number out of range
                                if (stepCount <= cwd_h.size()) {
                                    const char *dirHistory = cwd_h[stepCount - 1].c_str();
                                    dc = chdir(dirHistory);
                                }
                                else{
                                    cout << "Invalid Step: Step out of range." << endl;
                                    break;
                                }
                                
                            }
                            else{
                                cout << "Invalid Step: Use 'cd #<step number>' to return previous directory." <<endl;
                                break;
                            }
                        }
                    }
                    else if (cmd[1][0] == '#' && cmd[1].size() <= 1) {
                        cout << "Usage: 'cd #<Step Number>'  Use 'dlist' to lookup step number." << endl;
                    }
                    if (dc == -1) {
                        cout << cmd[1] << ": No such file or directory.";
                    }
                    else if (dc == 0){
                        char cwd[1024];
                        string dir = getcwd(cwd, sizeof(cwd));
                        cwd_h.push_front(dir);
                        cout << dir;
                    }
                }
                else {
                    cout << "Usage: cd </file_path>";
                }
            }
            
            else if (cmd[0] == "hlist") {
                if (cmd.size() == 1) {
                    ExecHistory(cmd_h);
                }
                else {
                    cout << "command 'hlist' takes no arguments.";
                }
            }
            
            else if (cmd[0] == "dlist") {
                if (cmd.size() == 1) {
                    GetDirHistory(cwd_h);
                }
                else {
                    cout << "command 'dlist' takes no arguments.";
                }
            }
            
            else {
                if (cmd[0] == "quit") {
                    cout << "[Process Completed]" << endl;
                    exit(0);
                }
                int outCode = ExecExtCmd(cmd);
                if (outCode != 200) {
                    cout << outCode << ": Command not found." << endl;
                }
            }
        }
        if (input.size() != 0) {
            pc++;
        }
        cout << endl;
        cmd.clear();
    }
    
    cout << "[Process Completed]" << endl;
    return 0;
}

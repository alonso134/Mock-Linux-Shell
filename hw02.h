//
//  hw02.h
//  hw02
//
//  Created by Kaichen Xiao on 5/29/16.
//  Copyright © 2016 Kaichen Xiao. All rights reserved.
//

#ifndef HW02_H
#define HW02_H

#include <iostream>
#include <iterator>
#include <sstream>
#include <algorithm>
#include <string>
#include <vector>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

void PrintDate(){
    system("date");
}

void PrintCurrDirectory(){
    system("pwd");
}

void DisplayVar(){
    system("printenv");
}

void ExecHistory(vector<pair<int, string>> hlist){
    for (int i = 0; i < hlist.size(); i++) {
        cout << hlist[i].first << ' ' << hlist[i].second << endl;
    }
}

void GetDirHistory(deque<string> dlist){
    long max_i = (dlist.size() < 10) ? dlist.size() : 10;
    for (int i = 0; i < max_i; i++) {
        cout << i+1 << ' ' << dlist[i] << endl;
    }
}

string CmdStepBack(string input, vector<pair<int, string>> hlist){
    input = input.substr(1, input.size()  - 1);
    int cmdStep = -1;
    if (all_of(input.begin(), input.end(), ::isdigit)) {
        cmdStep = stoi(input);
        if (cmdStep - 1 < hlist.size()) {
            for (int i = 0; i < hlist.size(); i++) {
                if (hlist[i].first == cmdStep) {
                    return hlist[i].second;
                }
            }
        }
        else{
            cout << "Fatal Error: Command step out of range.";
        }
    }
    else{
        cout << "Invalid Step: Use !<step number> to redo previous steps.";
    }
    return "";
}

int ExecExtCmd(vector<string> arg){
    pid_t pid;
    int stat, cflag;
    bool fwait = true;
    char* argv[128]; // max argument size 128
    
    if (arg.back() == "&") {
        arg.pop_back();
        fwait = false;
    }
    
    for (int i = 0; i < arg.size(); i++) {
        const char* argChar = arg[i].c_str();
        char* castArgs = const_cast<char*>(argChar);
        argv[i] = castArgs;
    }
    argv[arg.size()] = nullptr;
    pid = fork();
    
    if (pid < 0) {
        perror("Fatal Error: Fork Fails.");
        return 404;
    }
    
    // Child
    else if (pid == 0){
        cflag = execvp(argv[0], argv);
        if (cflag < 0) {
            perror("Fatal Error: File Execution Error.");
            exit(6);
            return 405;
        }
    }
    
    // Parent
    else {
        if (fwait == true) {
            if (wait(&stat) != pid) {
                perror("Fatal Error: Wait Error");
                cout << wait(&stat) << ":" << pid;
                return 505;
            }
        }
    }
    return 200;
}


#endif /* HW02_H */

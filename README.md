# Mock-Linux-Shell
*Linux shell simulator (*`tcsh`*)*
Created and Developed by Kaichen Xiao (MaGicKaiChen)

###### Introduction
This is a `tcsh` shell simulator implemented by C++ and runs on Linux system, the mock shell takes *following built-in commands*:
  `quit`: terminate the shell process
  `date`: display current date and time
  `curr`: display absolute pathname of current directory
  `env`: display all environment variables
  `cd Dir`: move from the current directory to `Dir`
  `hlist`: display recent input lines
  `dlist`: display recent directories

The shell also takes other external linux commands such as `ls`, `mkdir`, `rm`, `mv` and other commands.

###### How to use it
* First `fork` and `clone` this project to your working directory, then in your linux terminal, switch to the directory where you store the projects.
* Use `magic` to start the shell, `make` programs if nessesary (simply use `make` to make file).
* All set, enjoy!

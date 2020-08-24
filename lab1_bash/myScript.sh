# Problem Statement: "Often I have to search for different files and directories within my computer system. 
#                     In order to do this I use the 'ls' command to help orient myself.
# Name of command: ls
# Example of its usage: 
# -bash-4.2$ ls
# Lab1  README.md


# Here is the myScript.sh script that can:
# 1. list the directories and how many total directories are in the current folder.
# 2. List them in a tree hierarchy.
# 3. List size of each file.

rm *sh~  # remove unnecessasry files
ls       # list what the current directory have
ls | wc -l  # count how many files
tree     # present a tree structure of the directory
du -h    # show the size of the directory
# usage: sh myScript.sh

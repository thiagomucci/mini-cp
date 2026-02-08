# mini-cp

A minimal implementation of the Unix cp utility using POSIX system calls
This project is also part of a personal study of the book Advanced Programming in the UNIX Environment (APUE)

## Description
Copies a file from a source directory to a destination directory using
openat/open, read, and write

## Build
cc -Wall -Wextra -pedantic mini-cp.c -o mini-cp

## Usage
./mini-cp `<source_dir>` `<file>` `<dest_dir>`  

## references
W. Richard Stevens, Advanced Programming in the UNIX Environment

Terry Ford Jr. - CS 4280 Scanner Project - implementation 2 - 10/15/2023
git - https://github.com/tfordjr/scanner

IMPLEMENTATION 2 - NO SPACES REQUIRED

Three options for invokation:
./P1                                      Read from stdin (stop input with Ctrl+D)
./P1 filename(exclude extention)          Read from file, .f23 file extention assumed
./P1 < filename(include extention)        Put file into stdin

implementation: 
scanner.cpp source code that returns a single token struct for each execution.
main.cpp source code including arg checking and a while loop to return many tokens.
three testing files 
simple makefile and readme included

Bug tracking: 
Out() function has flags active, scanner.getNextToken() is run twice and not working right




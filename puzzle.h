#include "puzzle.c"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

void initialmessage(void); // show initial message
void clearterminal(void); // clear every information in the terminal
void menu(void); // print the option menu
char getRandomChar(void); // get a randomically char
void fillGrid(char puzzleGrid[5][5]); // fill the grid with letters between 'A' and 'Z'
void printGrid(char puzzleGrid[5][5]); // print all the elements of the grid
void rotatePositionRow(char direction,int rowcolnumb,int numbdesloc, char puzzleGrid[5][5]); // rotate row by N times
void rowRotatePos1t(char direction,int rowcolnumb, char puzzleGrid[5][5]); // rotate row by 1 time
void movement(char rowcol, char direction,int rowcolnumb,int numbdesloc, char puzzleGrid[5][5]); // call functions for movement is row or column 

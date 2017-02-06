#include "puzzle.c"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include <time.h>

void initialmessage(void); // show initial message
void clearterminal(void); // clear every information in the terminal
void menu(void); // print the option menu
char getRandomChar(void); // get a randomically char
void fillGrid(char **puzzleGrid); // fill the grid with letters between 'A' and 'Z'
void printGrid(char **puzzleGrid); // print all the elements of the grid
void rotatePositionRow(char direction,int rowcolnumb,int numbdesloc, char **puzzleGrid); // rotate row by N times
void rowRotatePos1t(char direction,int rowcolnumb, char **puzzleGrid); // rotate row by 1 time
void rotatePositionCol(char direction,int rowcolnumb,int numbdesloc, char **puzzleGrid); // rotate col by N times
void colRotatePos1t(char direction,int rowcolnumb, char **puzzleGrid); // rotate col by 1 time
void movement(char option, char direction,int rowcolnumb,int numbdesloc, char **puzzleGrid); // call functions for movement is row or column 
void checkpoints(char* word); //see the points achieved by the user
void checkcols(FILE *fp, char **puzzleGrid); //check if there is a word in the columns
void checkrows(FILE *fp, char **puzzleGrid); //check if there is a word in the rows
void checkword(char option, char direction,int rowcolnumb,int numbdesloc, char **puzzleGrid); // check if a world was found in the board
void checktime(char level); //check if the time is over


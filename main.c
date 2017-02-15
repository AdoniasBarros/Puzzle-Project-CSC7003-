//[CSC7003] Software Engineering 17/02/2017 
//Students: Adonias Vicente da Silva Barros, Enzo Gabriel Belloto Furlan
//Word Search Puzzle Project

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include "puzzle.h"

int main(void){
	
	char option, direction, level; // decide movement 'r'=row or 'c'=column / direction of rotate 'l'=left or 'r'=right
	int i,numbdesloc, rowcolnumb; // number of desired deslocaments / number of the row or column of the desired deslocament
	char **puzzleGrid;
	
	//allocation of memory matrix puzzle grid
	puzzleGrid = (char**) malloc(5*sizeof(char*));
	for(i=0; i<6; i++){
		puzzleGrid[i] = (char*) malloc(5*sizeof(char));
	}
	
	// first informations about the game
	clearterminal();
	initialmessage();
	menu();
	fillGrid(puzzleGrid);
	
	// check if the user put 'e', 'm' or 'h'
	do{
		printf("Type difficulty: ");
		scanf(" %c",&level);
	}while((level!='e')&&(level!='m')&&(level!='h'));
	
	//start counting of the game
	time(&start);
	
	// main game loop
	while(1){
		printGrid(puzzleGrid);
		//receive entries of user
		printf("\nType your option: ");
		scanf(" %c",&option);
		
		//game options
		switch(option){
			// change row
			case 'r':
				do{
                                        printf("Type a valid row number (0-5): ");
                                        scanf("%d",&rowcolnumb);
                                }while((rowcolnumb<0)||(rowcolnumb>5));
				scanf(" %c",&direction);
				scanf("%d",&numbdesloc);
				//seeing the entry performs the movement
				movement(option,direction,rowcolnumb,numbdesloc,puzzleGrid);
				//check if any world was found
				checkword(option,direction,rowcolnumb,numbdesloc,puzzleGrid);
				break;
			//change column
			case 'c':
				do{
                                        printf("Type a valid row number (0-5): ");
                                        scanf("%d",&rowcolnumb);
                                }while((rowcolnumb<0)||(rowcolnumb>5));
				scanf(" %c",&direction);
				scanf("%d",&numbdesloc);
				//seeing the entry performs the movement
				movement(option,direction,rowcolnumb,numbdesloc,puzzleGrid);
				//check if any world was found
				checkword(option,direction,rowcolnumb,numbdesloc,puzzleGrid);
				break;
			//show game time
			case 't':
				showtime();
				printf("Total points: %d\n",points);
				break;
			// finishes the game immediately
			case 'f':
				showtime();
				printf("Total points: %d\n",points);
				printf("GAME FINISHED!\n");
				exit(0);
				break;
			default:
				printf("Invalid option\n");
		}
		// if option is get time do not finish the game until the user do the last movement
		if(option!='t'){
			time (&end);
			dif = dif + difftime (end,start); 
			showtime();
			printf("Total points: %d\n",points);
			checktime(level);
		}
	}
	return 0;
}



/* REQUIREMENTS 
*	The game was all developed in C language;
*	The game can be played by 1 player;
*	The grid (board) has the size of 5 letters per 5 letters (5x5);
*	The board generates random letters without considering the possible words;
*	The words used in the game are provided by the developer in a separated dictionary, a “dic.txt” file. It is possible for the user to change the dictionary, it is just *	necessary to put a file with the same name in the same folder as the executable game.;
*	The difficulty is defined by time, when chosen the difficulty the user has the following time to make the maximum points:
*	Easy Level: 5 minutes;
*	Medium Level: 3 minutes;
*	Hard Level: 2 minutes;
*	The punctuation follows the English Version of the Scrabble game which are:
*
*Letters
*	Points
*	E, A, I, O, N, R, T, L, S, U
*	1 point
*	D, G
*	2 points
*	B, C, M, P
*	3 points
*	F, H, V, W, Y
*	4 points
*	K
*	5 points
*	J, X
*	8 points
*	Q, Z
*	10 points
*
*The first screen is a Menu containing all the information necessary to the user, as instructions to play, to choose the level, to show the time, the punctuation and how to *exit;
*The user need to form words with the grid with the objective to obtain the maximum punctuation in the defined time;
*
*
* 
* TESTS
*difficulty entry in the first different from 'e', 'm' or 'h' the game will expect a right enter
*if option is not 'r' 'c' 't' or 'f' the entry is invalid
*
*
*
* FIXED PROBLEMS
*04/02/2016
*PROBLEM FIXED: Repeated positions in the random matrix, when changing rows or columns others were changed 
*The problem in the positions of the random matrix creation and in the rotatePositionRow was fixed
*changing the static matrix alocation by the dinamic matrix alocation
*all the calls of the functions were changed to adapt to the new dynamic allocation i.e char puzzleGrid[][] -> char **puzzleGrid 
*time to fix the bug: 5 hours
*
*
*02/02/2016
*PROBLEM FIXED: Different reponses in scanfs, miss behavior
*The problem in the scanf was fixed separating the letter and world scanfs and putting a space before the %c
*It was seen that the %c scanf accept special characters, so every loop when the user taps 'ENTER' the scanf catchs
*this entry and treat it as a new entry to the next scanf, so the space is needed to ignore this behavior of the scanf 
*time to fix the bug: 3 hours
*
*
*06/02/2016
*PROBLEM FIXED: Time elapse problem
*Time elapsing counting in a wrong way
*time to fix the bug: 2 hours
*
*
*06/02/2016
*PROBLEM FIXED: Dictionary problem
*Problem to scan words in the dictionary
*
*
*time to fix the bug: 5 hours
*
*
*
*bug: tipe difficult with more than one letter
*bug: negative rows and columns or values out of the 0 to 5 size
*improvement: pass the dictionary to an array
*change the name of the variables
*definir constantes para os numeros #define 
*
*
*
*
*/

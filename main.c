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
				scanf(" %c",&direction);
				scanf("%d %d",&rowcolnumb,&numbdesloc);
				//seeing the entry performs the movement
				movement(option,direction,rowcolnumb,numbdesloc,puzzleGrid);
				//check if any world was found
				checkword(option,direction,rowcolnumb,numbdesloc,puzzleGrid);
				break;
			//change column
			case 'c':
				scanf(" %c",&direction);
				scanf("%d %d",&rowcolnumb,&numbdesloc);
				//seeing the entry performs the movement
				movement(option,direction,rowcolnumb,numbdesloc,puzzleGrid);
				//check if any world was found
				checkword(option,direction,rowcolnumb,numbdesloc,puzzleGrid);
				break;
			//check time
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



/* Some Requirements 
* 1 player ou 2 players
* The board has a size 5x5
* Board = List of lists
* Random letters
* Difficulty determined by time/ easy: 5 minutes, medium: 3 minutes, hard: 2 minutes
* Ponctuation: scrabble english
*
*
*Next taks
*discover why rotaterow is changing other lines
*finish the column movement logic
*create dictionnary
*
*After It
*create function to anylize if the user made one good world
*point system for each good world achieved
*time for all the levels
*texts to help the user in the game
*
* 
*tests
*difficulty entry in the first different from e, m or h
*if option is not 'r' 'c' 't' or 'f' the entry is invalid
*
*
*
*
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
*time to fix the bug: 5 hours
*
*/

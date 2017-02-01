//Word search puzzle project

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "puzzle.h"



int main(void){
	char puzzleGrid[5][5]; // grid 5x5
	char rowcol, direction; // decide movement 'r'=row or 'c'=column / direction of rotate 'l'=left or 'r'=right
	int numbdesloc, rowcolnumb; // number of desired deslocaments / number of the row or column of the desired deslocament

	// first informations about the game
	clearterminal();
	initialmessage();
	fillGrid(puzzleGrid);
	printGrid(puzzleGrid);

	// main game loop
	while(1){
	
		printf("\nType your option: ");
		scanf(" %c %c",&rowcol,&direction);
		scanf("%d %d",&rowcolnumb,&numbdesloc);
		printf("%c %c %d %d\n\n",rowcol,direction,numbdesloc,rowcolnumb);
		movement(rowcol,direction,rowcolnumb,numbdesloc,puzzleGrid);
		
		clearterminal();
		initialmessage();
		printGrid(puzzleGrid);
	}
	return 0;
}



/* Some Requirements 
* 1 player ou 2 players
* The board has a size 10x10
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
*
*
*
*/

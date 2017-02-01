// Functions declared in "puzzle.h" header file

void clearterminal(void){
	system("clear");
}

void initialmessage(void){
	printf("*****************************************\n\n");
	printf("Welcome to the Word Dynamic Search Puzzle\n\n\n");
	printf("*****************************************\n\n");
	printf("\n\n");
}

void menu(void){

}

char getRandomChar(void){
	int rl;
	rl = rand()% 26 + 'A';
	return (char)rl;
}

void fillGrid(char puzzleGrid[][5]){
	int i,j;
	struct timeval t1;
	gettimeofday(&t1, NULL);
	srand(t1.tv_usec * t1.tv_sec);
	
	for(i=0;i<6;i++){
		for(j=0;j<6;j++){
			puzzleGrid[i][j]= getRandomChar();
		}
	}

}
void printGrid(char puzzleGrid[5][5]){
	int i,j;
	printf("   0 1 2 3 4 5\n\n");
	for(i=0;i<6;i++){
		printf("%d  ", i);
		for(j=0;j<6;j++){
			printf("%c ",puzzleGrid[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	printf("\n");
}
void rowRotatePos1t(char direction,int rowcolnumb, char puzzleGrid[][5]){
	int i,j,aux;
	
		if(direction=='l'){
			aux = puzzleGrid[rowcolnumb][0];
			for(i=1, j=0 ; i<6 ; i++, j++){
				puzzleGrid[rowcolnumb][j] = puzzleGrid[rowcolnumb][i];
			}
			puzzleGrid[rowcolnumb][5] = aux;
			for(i=0;i<6;i++){
				printf("%c ",puzzleGrid[rowcolnumb][i]);
				printf("\n");
			}		
		}
		else if(direction=='r'){
			aux = puzzleGrid[rowcolnumb][5];
			for(i=4, j=5 ; i>0, j>0 ; i--, j--){
				puzzleGrid[rowcolnumb][j] = puzzleGrid[rowcolnumb][i];
			}
			puzzleGrid[rowcolnumb][0] = aux;
			for(i=0;i<6;i++){
				printf("%c ",puzzleGrid[rowcolnumb][i]);
			}
			printf("\n");
		}
}

void rotatePositionRow(char direction,int rowcolnumb,int numbdesloc, char puzzleGrid[5][5]){
	int i;
	for(i=0; i<numbdesloc; i++){
		rowRotatePos1t(direction,rowcolnumb,puzzleGrid);
	
	}
}

void movement(char rowcol, char direction,int rowcolnumb,int numbdesloc, char puzzleGrid[5][5]){
	if(rowcol='r'){
		rotatePositionRow(direction,rowcolnumb,numbdesloc,puzzleGrid);
	}
	else if(rowcol='c'){
	
	}

}
/*
void changePosition(char rowcol,char direction,int rowcolnumb, int numbdesloc, char puzzleGrid[5][5]){
	int i,j;
	char aux[5];
		if(rowcol=='r'){
			if(direction=='l'){
				for(i=0; i<numbdesloc; i++){
					aux[i] = puzzleGrid[rowcolnumb][i];
				}
				for(i=numbdesloc, j=0 ; i<6 ; i++, j++){
					puzzleGrid[rowcolnumb][j] = puzzleGrid[rowcolnumb][i];
				}
				
				for(i = (5-numbdesloc)+1, j=0 ; i<6 ; i++, j++){
					puzzleGrid[rowcolnumb][i] = aux[j];
				}
			}
			else if(direction=='r'){
				for(j=0,i=6-numbdesloc; i>numbdesloc; i--, j++){
					aux[j] = puzzleGrid[rowcolnumb][i];
				}
				for(i=(6-numbdesloc), j=6 ; i<0 ; i--, j--){
					puzzleGrid[rowcolnumb][j] = puzzleGrid[rowcolnumb][i];
				}
				
				for(i = 0; i<numbdesloc ; i++){
					puzzleGrid[rowcolnumb][i] = aux[i];
				}
			}
		}
		else if(rowcol=='c'){
	
		}
}
*/


//http://www.geeksforgeeks.org/array-rotation/



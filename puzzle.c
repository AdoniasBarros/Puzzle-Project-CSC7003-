// Functions declared in "puzzle.h" header file
int points = 0;
time_t start, end;
double dif;

void clearterminal(void){
	system("clear");
}

void initialmessage(void){
	printf("*****************************************\n\n");
	printf("Welcome to the Word Dynamic Search Puzzle\n\n\n");
	printf("*****************************************");
	printf("\n\n");
}

void menu(void){
	printf("Rules:\n");
	printf("1. Difficulty -> 'e'asy:5m 'm' medium:3m 'h'hard:2m\n");
	printf("2. Movement -> (a,b,c,d)\n");
	printf("	a: to move a row 'r' / to move a column 'c'.\n");
	printf("	b: case 'r': to move left 'l' / to move right 'r' \n");
	printf("	b: case 'c': to move up   'u' /  to move down  'd'\n");
	printf("	c: row or column number \n");
	printf("	d: number of movements \n");
	printf("3. Time -> After the time the user has more one movement to end the game\n");
	printf("4. Other options\n");
	printf("	't' update the time\n");
	printf("	'f' finishes the game immediately\n");
	printf("5. Pontuation -> The pontuation is according to scrabble");
	printf("6. The game starts after chose the difficulty\n");
	printf("\n\n");
	
}

char getRandomChar(void){
	int rl;
	rl = rand()% 26 + 'A';
	return (char)rl;
}

void fillGrid(char **puzzleGrid){
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

void printGrid(char **puzzleGrid){
	int i,j;
	printf("\n\n");
	printf("   0 1 2 3 4 5\n\n");
	for(i=0;i<6;i++){
		printf("%d  ", i);
		for(j=0;j<6;j++){
			printf("%c ",puzzleGrid[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void rowRotatePos1t(char direction,int rowcolnumb, char **puzzleGrid){
	int i,j,aux;
	
		if(direction=='l'){
			aux = puzzleGrid[rowcolnumb][0];
			for(i=1, j=0 ; i<6 ; i++, j++){
				puzzleGrid[rowcolnumb][j] = puzzleGrid[rowcolnumb][i];
			}
			puzzleGrid[rowcolnumb][5] = aux;		
		}
		else if(direction=='r'){
			aux = puzzleGrid[rowcolnumb][5];
			for(i=4, j=5 ; i>0, j>0 ; i--, j--){
				puzzleGrid[rowcolnumb][j] = puzzleGrid[rowcolnumb][i];
			}
			puzzleGrid[rowcolnumb][0] = aux;
		}
}

void colRotatePos1t(char direction,int rowcolnumb, char **puzzleGrid){
	int i,j,aux;
	
		if(direction=='u'){
			aux = puzzleGrid[0][rowcolnumb];
			for(i=1, j=0 ; i<6 ; i++, j++){
				puzzleGrid[j][rowcolnumb] = puzzleGrid[i][rowcolnumb];
			}
			puzzleGrid[5][rowcolnumb] = aux;
		
		}
		else if(direction=='d'){
			aux = puzzleGrid[5][rowcolnumb];
			for(i=4, j=5 ; i>0, j>0 ; i--, j--){
				puzzleGrid[j][rowcolnumb] = puzzleGrid[i][rowcolnumb];
			}
			puzzleGrid[0][rowcolnumb] = aux;

		}
}

void rotatePositionRow(char direction,int rowcolnumb,int numbdesloc, char **puzzleGrid){
	int i;
	for(i=0; i<numbdesloc; i++){
		rowRotatePos1t(direction,rowcolnumb,puzzleGrid);
	}
}

void rotatePositionCol(char direction,int rowcolnumb,int numbdesloc, char **puzzleGrid){
	int i;
	for(i=0; i<numbdesloc; i++){
		colRotatePos1t(direction,rowcolnumb,puzzleGrid);
	}

}

void movement(char option, char direction,int rowcolnumb,int numbdesloc, char **puzzleGrid){
	if(option=='r'){
		rotatePositionRow(direction,rowcolnumb,numbdesloc,puzzleGrid);
	}
	else if(option=='c'){
		rotatePositionCol(direction,rowcolnumb,numbdesloc,puzzleGrid);
	}
}

void checkpoints(char* word){
	int i,aux=0;
	// next modification
	// put words in another file, if the user find a word there is in the dictionary dont get into the for, if not get into the forloop
	
	for (i=0; i<strlen(word); i++){
		if (word[i]=='E'|word[i]=='A'|word[i]=='I'|word[i]=='O'|word[i]=='N'|word[i]=='R'|word[i]=='T'|word[i]=='L'|word[i]=='S'|word[i]=='U'){
			aux = aux + 1;
		}else if (word[i]=='D'|word[i]=='G'){
			aux = aux + 2;
		}else if (word[i]=='B'|word[i]=='C'|word[i]=='M'|word[i]=='P'){
			aux = aux + 3;
		}else if (word[i]=='F'|word[i]=='H'|word[i]=='V'|word[i]=='W'|word[i]=='Y'){
			aux = aux + 4;
		}else if (word[i]=='K'){
			aux = aux + 5;
		}else if (word[i]=='J'|word[i]=='X'){
			aux = aux + 8;
		}else if (word[i]=='Q'|word[i]=='Z'){
			aux = aux + 10;
		}
	}
	points = points + aux;
	printf("You made %d points!\n\n", points);
	
}
void checkrows(FILE* fp, char **puzzleGrid){
	char word[5], str[5];
	int i,j;
	j=0;
	while(j<6){
		for(i=0;i<6;i++){
			word[i] = puzzleGrid[i][j];
		}

		while (fscanf(fp,"%s",str) != EOF ){ //read the file
			if (strstr(word,str) != NULL){ //see if there is the string
				printf("\nWord %s found! Congratulations!\n",str);
				checkpoints(str);
			}
		}
		fseek(fp, 0, SEEK_SET);
		j++;
	}
}

void checkcols(FILE *fp, char **puzzleGrid){
	char word[5], str[5];
	char* aux;
	int i,j;
	
	j=0;
	while(j<6){
		for(i=0;i<6;i++){
			word[i] = puzzleGrid[j][i];
		}
		
		while (fscanf(fp,"%s",str) != EOF){ //read the file
			if (strstr(word,str) != NULL){ //see if there is the string
				printf("\nWord %s found! Congratulations!\n",str);
				checkpoints(str);
			}
		}
		fseek(fp, 0, SEEK_SET);
		j++;
	}
}


void checkword(char option, char direction,int rowcolnumb,int numbdesloc, char **puzzleGrid){

	char word[5], str[5];
	int i,j;
	FILE *fp;

	fp = fopen("dic.txt","r");
	if (!fp){
		perror("\nError: \n");
		exit(0);
	}
	if(option=='r') checkrows(fp,puzzleGrid);
	if(option=='c') checkcols(fp,puzzleGrid);

	fclose(fp);
}


void checktime(char level){

	if(level=='e'){
		if(dif>=300){
			printf("GAME FINISHED!\n");
			exit(0);
		}
	}
	else if(level=='m'){
		if(dif>=180){
			printf("GAME FINISHED!\n");
			exit(0);
		}
	}
	else if(level=='h'){
		if(dif>=120){
			printf("GAME FINISHED!\n");
			exit(0);
		}
	}
}

void showtime(void){
	time (&end);
	dif = difftime (end,start); 
	printf ("Elasped time: %.2lf s\n", dif ); 
}
//http://www.geeksforgeeks.org/array-rotation/



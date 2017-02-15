// Functions declared in "puzzle.h" header file
int points = 0;
time_t start, end;
double dif;

//clear the information in the terminal
void clearterminal(void){
	system("clear");
}

// show initial message
void initialmessage(void){
	printf("*****************************************\n\n");
	printf("Welcome to the Word Dynamic Search Puzzle\n\n\n");
	printf("*****************************************");
	printf("\n\n");
}

// print the option menu
void menu(void){
	printf("Rules:\n");
	printf("1. Difficulty -> 'e'asy:5m 'm' medium:3m 'h'hard:2m\n");
	printf("2. Movement -> (a,b,c,d)\n");
	printf("	a: to move a row 'r' / to move a column 'c'.\n");
	printf("	b: row or column number \n");
	printf("	c: case 'r': to move left 'l' / to move right 'r' \n");
	printf("	c: case 'c': to move up   'u' /  to move down  'd'\n");
	printf("	d: number of movements \n");
	printf("3. Time -> After the time ends up, the user has one more movement to end his game\n");
	printf("4. Other options\n");
	printf("	't' show the current time\n");
	printf("	'f' finish the game immediately\n");
	printf("5. Score Grid -> The score is based on the Scrabble Game\n");
	printf("	1 point:  E, A, I, O, N, R, T, L, S, U\n");
	printf("	2 points: D, G\n");
	printf("	3 points: B, C, M, P\n");		
	printf("	4 points: F, H, V, W, Y\n");
	printf("	5 points: K\n");
	printf("	8 points: J, X\n");
	printf("	0 points: Q, Z\n");	
	printf("6. The game begins after the choice of difficulty\n");
	printf("\n\n");
	
}

// get a randomically char
char getRandomChar(void){
	int rl;
	rl = rand()% 26 + 'A';
	return (char)rl;
}

// fill the grid with letters between 'A' and 'Z'
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

// print all the elements of the grid with number of respective rows and columns
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

// rotate row by 1 time
void rowRotatePos1t(char direction,int rowcolnumb, char **puzzleGrid){
	int i,j,aux;
	
		if(direction=='l'){ // left direction
			aux = puzzleGrid[rowcolnumb][0];// save the first element of the array
			for(i=1, j=0 ; i<6 ; i++, j++){ // put all the characters from a position n+1 in n until the end of the array
				puzzleGrid[rowcolnumb][j] = puzzleGrid[rowcolnumb][i];
			}
			puzzleGrid[rowcolnumb][5] = aux; //put the first element in the last position		
		}
		else if(direction=='r'){ // right direction
			aux = puzzleGrid[rowcolnumb][5];// save the last element of the array
			for(i=4, j=5 ; i>0, j>0 ; i--, j--){// put all the characters from a position n+1 in n until the end of the array
				puzzleGrid[rowcolnumb][j] = puzzleGrid[rowcolnumb][i];
			}
			puzzleGrid[rowcolnumb][0] = aux;//put the first element in the last position
		}
}

// rotate column by 1 time
void colRotatePos1t(char direction,int rowcolnumb, char **puzzleGrid){
	int i,j,aux;
	
		if(direction=='u'){ // up direction
			aux = puzzleGrid[0][rowcolnumb];// save the first element of the array
			for(i=1, j=0 ; i<6 ; i++, j++){ // put all the characters from a position n+1 in n until the end of the array
				puzzleGrid[j][rowcolnumb] = puzzleGrid[i][rowcolnumb];
			}
			puzzleGrid[5][rowcolnumb] = aux; //put the first element in the last position
		
		}
		else if(direction=='d'){ // down direction
			aux = puzzleGrid[5][rowcolnumb];// save the last element of the array
			for(i=4, j=5 ; i>0, j>0 ; i--, j--){// put all the characters from a position n in n+1 until the end of the array
				puzzleGrid[j][rowcolnumb] = puzzleGrid[i][rowcolnumb];
			}
			puzzleGrid[0][rowcolnumb] = aux; //put the last element in the first position

		}
}

// execute the rotate position in a row by one time N times
void rotatePositionRow(char direction,int rowcolnumb,int numbdesloc, char **puzzleGrid){
	int i;
	for(i=0; i<numbdesloc; i++){
		rowRotatePos1t(direction,rowcolnumb,puzzleGrid);
	}
}

// execute the rotate position in a column by one time N times
void rotatePositionCol(char direction,int rowcolnumb,int numbdesloc, char **puzzleGrid){
	int i;
	for(i=0; i<numbdesloc; i++){
		colRotatePos1t(direction,rowcolnumb,puzzleGrid);
	}

}

//check which movement the user wants to do
void movement(char option, char direction,int rowcolnumb,int numbdesloc,  char **puzzleGrid){
	if(option=='r'){
		rotatePositionRow(direction,rowcolnumb,numbdesloc,puzzleGrid);
	}
	else if(option=='c'){
		rotatePositionCol(direction,rowcolnumb,numbdesloc,puzzleGrid);
	}
}

//see the points achieved by the user
void checkpoints(char* word){
	int i,aux=0;
	// punctuation following the scrabble letter distribution in english
	// when you find a letter, each word will have an especific ponctuation
	//https://en.wikipedia.org/wiki/Scrabble_letter_distributions
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

//check if there is a word in the rows
void checkrows(FILE* fp, char **puzzleGrid){
	char word[5], str[5];
	char buffer[20];
	int i,j;
	j=0;
	while(j<6){
		for(i=0;i<6;i++){
			word[i] = puzzleGrid[i][j];
		}

		while (fscanf(fp,"%s",str) != EOF ){ //read every string in the file until the end
			if (strstr(word,str) != NULL){ //see if there is the substring of the file inside the string of the row | column
				printf("\nWord %s found! Congratulations!\n",str);
				checkpoints(str); // once the word is found check the points the user made
				fseek(fp, 0, SEEK_CUR);
				fprintf(fp,"*\n");
			}
		}
		fseek(fp, 0, SEEK_SET); // set the pointer back to the beginning of the file 
		j++;
	}
}

//check if there is a word in the columns
void checkcols(FILE *fp, char **puzzleGrid){
	char word[5], str[5];
	char buffer[20];
	char* aux;
	int i,j;
	
	j=0;
	while(j<6){
		for(i=0;i<6;i++){
			word[i] = puzzleGrid[j][i];
		}
		
		while (fscanf(fp,"%s",str) != EOF){ //read every string in the file until the end
			if (strstr(word,str) != NULL){ //see if there is the substring of the file inside the string of the row | column
				printf("\nWord %s found! Congratulations!\n",str);
				checkpoints(str); // once the word is found check the points the user made
				fseek(fp, 0, SEEK_CUR);
				fprintf(fp,"*\n");
			}
		}
		fseek(fp, 0, SEEK_SET); // set the pointer back to the beginning of the file 
		j++;
	}
}

//check if there is a word in the rows
void checkword(char option, char direction,int rowcolnumb,int numbdesloc, char **puzzleGrid){

	char word[5], str[5];
	int i,j;
	FILE *fp;

	fp = fopen("dic.txt","r+"); 
	if (!fp){
		perror("\nError: \n");
		exit(0);
	}
	if(option=='r') checkrows(fp,puzzleGrid);
	if(option=='c') checkcols(fp,puzzleGrid);

	fclose(fp);
}

//check if the time is over in seconds to each level 'e' easy, 'm' medium, 'h' hard
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

//show the elapsed time
void showtime(void){
	time (&end);
	dif = difftime (end,start); 
	printf ("Elasped time: %.2lf s\n", dif ); 
}

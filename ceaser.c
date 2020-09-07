#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROW 8732
#define COL 16

//char dictWords[ROW][COL];
const int INITIAL_MAX_LINES = 2;
const int MAX_LINES_INC = 2;
const int INITIAL_MAX_LINE_LENGTH = 2;
const int MAX_LINE_LENGTH_INC = 2;

	//Reads dictionary2.txt and stores in array
	//Check if decrypted word is in array of dictionary words
	int openDict(char *decrypted){
		FILE *fp;
		fp = fopen("dictionary2.txt", "r");
		
		int nlines = 0, i;
		char **inputFile, *buffer;
		int maxLines, c, buflen, bufp, endline;

		maxLines = INITIAL_MAX_LINES;

		inputFile = (char **)malloc(maxLines*sizeof(char*));

		//Checks to make sure file was opened
		if(fp == 0){
			printf("Cannot open file\n");
		}
		else{
			bufp = 0;
			buflen = INITIAL_MAX_LINE_LENGTH;
			buffer = (char *) malloc(buflen * sizeof(char*));

			c = 0;

			while(c != EOF){
				endline = 0;
				c = fgetc(fp);

				if(c==EOF || c=='\n' || c=='\r'){
					endline = 1;
					//Discard this character
				}
				//Check if there is enough memory then put character in buffer
				//Leave room for null character
				else{
					if(bufp >= buflen - 1){
						buflen+=MAX_LINE_LENGTH_INC;
						buffer = (char *) realloc(buffer, buflen * sizeof(char));
					}

					buffer[bufp] = c;
					bufp++;
				}
				
				if(endline){
					//Get a new buffer and check if we need more memory
					if(nlines >= maxLines){
						maxLines += MAX_LINES_INC;
						inputFile = (char**) realloc(inputFile, maxLines * sizeof(char*));
					}
					//Null terminate buffer
					buffer[bufp++] = 0;
					
					inputFile[nlines] = buffer;
					nlines++;

					bufp = 0;
					buflen = INITIAL_MAX_LINE_LENGTH;
					buffer = (char*) malloc(buflen * sizeof(char*));
				}
			}
		}
		int result;
		//printf("%s\n", decrypted);
		int notfound = 0;
		int found = 0;
		//printf("%d lines\n", nlines);
		for(int i=0; i<nlines;i++){
			//printf("%s\n", inputFile[i]);
			result = strcmp(inputFile[i], decrypted);
			if(result == 0){
				//printf("Found\n");
				found++;
				//return 1;
			}
			else{
				//printf("not found\n");
				notfound++;
				//return 0;
			}
		}
		printf("Not found %d\n", notfound);
		printf("found %d\n", found);
		for(int w=0; w<nlines;w++){
			free(inputFile[w]);
		}
		fclose(fp);
	}
	
	char* decrypt(char *word){
		//printf("\n%s\n", word);
		char ch;
		//char decrypted[150];
		char *decrypted;
		decrypted = (char*) calloc(1,sizeof(char));
		int d=0;
		char A[26][2];
		int value = 0;
		for(int key = 1; key < 26; key++){
			for(int i=0; word[i] != '\0'; ++i){
				int k = 0;
				d++;
				ch = word[i];

				if(ch >= 'A' && ch <= 'Z'){
					ch = ch - key;

					if (ch < 'A'){
						ch = ch + 'Z' - 'A' + 1;
					}

					 decrypted[i]= ch;
				}
				
			}	
			printf("Shift Key: %d %s\n",key, decrypted);
			openDict(decrypted);
			/*for(int j=0; j<26; j++){
				A[key][j] = value;
				if(r == 1){
					value+=1;
					A[key][j] = value;
				}
			}*/
			//break;
		}
		/*
		int MAX = 0;

		for(int p = 1; p<26; p++){
			for(int q=0; q < 2; q++){
				if(A[p][q] > MAX){
					MAX = A[p][q];
				}
			}
		}
		printf("%d\n", MAX);*/
		free(decrypted);
	}

	//Takes in sentence from encrypted_text
	//Splits sentence into words using strtok()
	int split(char *l){
		int counter = 0;
		char **words= 0;
		int tempCounter = 0;
		
		char *token = strtok(l, " ");
		
		while(token != NULL)
		{
			//NULL passed as first argument in order to
			//continue with the same string (line)
			if(tempCounter == 0){
				token = strtok(NULL, " ");
				tempCounter++;
			}
			//grows **words with realloc
			//allocates size of each element of words using malloc
			//copies token to words[counter] as counter is incremented
			else{
				words = realloc(words, (counter+ 1) * sizeof(char *));
				words[counter] = malloc(strlen(token) + 1);
				decrypt(strcpy(words[counter++], token));
				//wordPossible(strcpy(words[counter++], token));
				token = strtok(NULL, " ");
			}
			
			counter = 0;
			//How do I reset **words / change the pointers?
		}
	}	


	//Reads encrypted_text using getline()
	int main(){
		
		char *line = NULL;
		size_t len = 0;
		size_t read = 0;
		
		
		while((read = getline(&line, &len, stdin)) <= 50)
		{
			split(line);
			//trying first sentence
			//break;
			//printf("\nNew Sentence\n");
		}
	}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SHIFTS 25

const int INITIAL_MAX_LINES = 2;
const int MAX_LINES_INC = 2;
const int INITIAL_MAX_LINE_LENGTH = 2;
const int MAX_LINE_LENGTH_INC = 2;

char shifts[SHIFTS];
int max_index;


	//Reads dictionary2.txt and stores in array
	//Check if decrypted word is in array of dictionary words
	//If word is in dictionary, count occurrences of each shift and find max
	int openDict(char *decrypted, int key){
		FILE *fp;
		fp = fopen("dictionary2.txt", "r");
		
		int lines = 0, i, max, value, result, found;
		char **file, *buffer;
		int maxLines, c, buflen, bufp, endline;

		maxLines = INITIAL_MAX_LINES;
		
		//Allocating memory for inputFile
		file = (char **)malloc(maxLines*sizeof(char*));

		//Checks to make sure file was opened successfully
		if(fp == 0){
			printf("Cannot open file\n");
		}
		else{
			//Initialize buffer len and position.
			//Allocates memory for buffer
			bufp = 0;
			buflen = INITIAL_MAX_LINE_LENGTH;
			buffer = (char *) malloc(buflen * sizeof(char*));

			c = 0;

			while(c != EOF){
				
				endline = 0;

				//Grabbing characters
				c = fgetc(fp);

				//Discard character
				if(c==EOF || c=='\n' || c=='\r'){
					//Setting end of line to true/1
					endline = 1;
				
				}
				//Putting character in buffer
				//Check if there is enough memory
				//buflen-1 leaving room for null character
				//Incrementing buffer position
				else{
					if(bufp >= buflen - 1){
						buflen+=MAX_LINE_LENGTH_INC;
						buffer = (char *) realloc(buffer, buflen * sizeof(char));
					}
					
					buffer[bufp] = c;
					bufp++;
				}
				
				//If end of line was reached, get a new buffer
				//Check if more memory is needed
				//Realloc memory to inputFile
				if(endline){
					if(lines >= maxLines){
						maxLines += MAX_LINES_INC;
						file = (char**) realloc(file, maxLines * sizeof(char*));
					}
					//Null terminate buffer
					buffer[bufp++] = 0;
					
					//Add buffer to inputFile
					//Increment line
					file[lines] = buffer;
					lines++;

					//Resets buffer
					bufp = 0;
					buflen = INITIAL_MAX_LINE_LENGTH;
					buffer = (char*) malloc(buflen * sizeof(char*));
				}
			}
		}
		
		//printf("Key: %d %s\n",key, decrypted);
		
		//printf("%d lines\n", nlines);
		
		//Go through dictionary and compare dictionary word to decrypted word
		//Increment found if result == 0
		for(int i=0; i<lines;i++){
			//printf("%s\n", inputFile[i]);
			result = strcmp(file[i], decrypted);

			if(result == 0){
				//printf("Found\n");
				found++;	
				//return 1;		
			}
			else{
				//printf("not found\n");
			}
			
		}
		
		//printf("Dictionary: %d\n", found);
		
		max = shifts[0];
		
		//If word is in the dictionary, find shift with max occurences
		if(found == 4){
			shifts[key] += 1;
			//printf("Occurences: %d\n", shifts[key]);
			//Ignore max shift occurences == 1
			if(shifts[key] == 1){
				
			}
			else{
				if(shifts[key] > max){
					max_index = key;
				}
			}
		}

		//Free dictionary words
		for(int w=0; w<lines;w++){
			free(file[w]);
		}
		
		fclose(fp);
		return 0;
	}

	//Decrypts word(s) from sentences
	//Passes decrypted word and key/shift to openDict() to check 
	//if it's in the dictionary
	char* decrypt(char *word){
		//printf("\n%s\n", word);
		char ch;
		
		char *decrypted;
		decrypted = (char*) calloc(1,sizeof(char));
		
		for(int key = 1; key < 26; key++){
			for(int i=0; word[i] != '\0'; ++i){
				int k = 0;
				
				ch = word[i];

				if(ch >= 'A' && ch <= 'Z'){
					ch = ch - key;

					if (ch < 'A'){
						ch = ch + 'Z' - 'A' + 1;
					}

					 decrypted[i]= ch;
				}
				
			}	
			//printf("Shift Key: %d %s\n",key, decrypted);
			openDict(decrypted, key);
		}
		
		free(decrypted);
	}

	//Takes in sentence from encrypted_text
	//Splits sentence into words using strtok()
	//Pass word to decrypt()
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
				token = strtok(NULL, " ");
			}
			
			counter = 0;
		}
	}	


	//Reads encrypted_text using getline()
	int main(){
		
		char *line = NULL;
		size_t len = 0;
		size_t read = 0;
		
		FILE *fp;
		fp = fopen("shifts.txt", "w");

		while((read = getline(&line, &len, stdin)) != EOF)
		{
			split(line);
			
			//Writes best shift to shifts.txt
			fprintf(fp, "%d\n", max_index);
			
			//printf("\nBest Shift: %d\n", max_index);
			
			//Resets occurences of each shift for each sentence
			for(int i = 1; i<26; i++){
				shifts[i] = 0;
			}
		}

		fclose(fp);
	}

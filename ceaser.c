#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SHIFTS 25

char shifts[SHIFTS];
int max_index;
FILE *f;

	int isWord(char* decrypted){
		//printf("%s\n", decrypted);
		//FILE *f;
		f = fopen("dictionary2.txt", "r");
		
		if(NULL == f){
			perror("fopen() failed");
			exit(EXIT_FAILURE);
		}
		char w[] = "LETS";
		char readValue[100];
		while(fgets(readValue, 100, f) != NULL){
			readValue[strcspn(readValue,"\r\n")] = '\0';
			
			if(strcmp(readValue, decrypted) == 0){
				//printf("%s\n", readValue);
				return 1;
			}
			//printf("%s\n", readValue);
			
		}
		return 0;
		fclose(f);
	}

	//Decrypts word(s) from sentences
	//Passes decrypted word and key/shift to openDict() to check 
	//if it's in the dictionary
	char* decrypt(char *word){
		//printf("\n%s\n", word);
		char ch;
		int max;
		
		char *decrypted;
		decrypted = (char*) calloc(1,sizeof(char));
		//char decrypted[100];
		max = shifts[0];
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
			printf("\nShift Key: %d %s\n",key, decrypted);
			//openDict(decrypted, key);
			//dict(decrypted, key);
			/*	
			if(isWord(decrypted) == 1){
				printf("%d\n", key);
				shifts[key]++;
				if(shifts[key] > max){
					max_index = key;
				}
			}*/	
			//isWord();
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
		//token = strtok(NULL, " ");
		while(token != NULL)
		{
			/*
			//NULL passed as first argument in order to
			//continue with the same string (line)
			if(tempCounter == 0){
				token = strtok(NULL, " ");
				tempCounter++;
			}*/
			//grows **words with realloc
			//allocates size of each element of words using malloc
			//copies token to words[counter] as counter is incremented
			
				words = realloc(words, (counter+ 1) * sizeof(char *));
				words[counter] = malloc(strlen(token) + 1);
				decrypt(strcpy(words[counter++], token));
				token = strtok(NULL, " ");
			
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
		if(fp == NULL){
			perror("fopen() failed");
			exit(EXIT_FAILURE);
		}
		
		while((read = getline(&line, &len, stdin)) <= EOF)
		{
			split(line);
			
			//Writes best shift to shifts.txt
			fprintf(fp, "%d\n", max_index);
			
			printf("\nBest Shift: %d\n", max_index);
			
			//Resets occurences of each shift for each sentence
			for(int i = 1; i<26; i++){
				shifts[i] = 0;
			}

		}
		//isWord();
		fclose(fp);
	}

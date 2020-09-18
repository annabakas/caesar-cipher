#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SHIFTS 25

const int INITIAL_MAX_LINES = 50;
const int MAX_LINES_INC = 50;
const int INITIAL_MAX_LINE_LENGTH = 50;
const int MAX_LINE_LENGTH_INC = 50;

char shifts[SHIFTS];
int max_index;

char dictWords[8732][100];
char encryptedSentence[330];
	//Reads dictionary2.txt and stores in array
	//Check if decrypted word is in array of dictionary words
	//If word is in dictionary, count occurrences of each shift and find max
	int openDict(char *decrypted, int key){
		//printf("%d %s\n", key, decrypted);
		//char w[4] = "LETS";
		
		FILE *fp;
		fp = fopen("dictionary2.txt", "r");
		
		int i, max, result;
		max = shifts[0];
		for(i=0; i < 8732; i++){
			fscanf(fp, "%s", dictWords[i]);
			result = strcmp(dictWords[i], decrypted);
			if(result == 0){
				//printf("match\n");
				shifts[key]++;
				if(shifts[key] > max){
					max_index = key;
				}
			}
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
		decrypted = malloc(330 * sizeof *decrypted);
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
		return 0;
	}

	//Takes in sentence from encrypted_text
	//Splits sentence into words using strtok()
	//Pass word to decrypt()
	int split(char *l){
		char word[37240][20];
		char ch;
		int i, j, ctr;
		j=0; ctr = 0;

		for(i = 0; i <= (strlen(l)); i++){
			if(l[i] == ' ' || l[i] == '\0'){
				word[ctr][j] = '\0';
				ctr++;
				j = 0;
			}
			else{
				word[ctr][j] = l[i];
				j++;
			}
		}

		for(i = 0; i < ctr; i++){
			decrypt(word[i]);
			//printf("%s\n", word[i]);
		}

		return 0;
	}	


	//Reads encrypted_text using getline()
	int main(){
		char *line = NULL;
		
		size_t len = 0;
		size_t read = 0;
		
		FILE *fp;
		fp = fopen("shifts.txt", "w");

		//openDict();
		
		char buffer[330];
		int count = 0;
		while((fgets(buffer, 330, stdin)) != NULL){
			count++;
			printf("%d\n", count);
			//printf("%d: %s\n",count, buffer);
			split(buffer);

			//printf("\nBest Shift: %d\n", max_index);
			
			fprintf(fp, "%d\n", max_index);

			for(int x = 1; x < 26; x++){
				shifts[x] = 0;
			}

			//break;
		}
		/*
		while((read = getline(&line, &len, stdin)) != EOF)
		{
			
			//split(line);
			printf("%s\n", line);
			line++;
			//Writes best shift to shifts.txt
			fprintf(fp, "%d\n", max_index);
			
			//printf("\nBest Shift: %d\n", max_index);
			
			
			//Resets occurences of each shift for each sentence
			for(int i = 1; i<26; i++){
				shifts[i] = 0;
			}
			//break;
			//fprintf(stderr, "error");
		
		}*/

		fclose(fp);
		return 0;
	}

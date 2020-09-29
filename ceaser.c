#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SHIFTS 25
#define DICTLINES 8732
#define MAX_WORD_LENGTH 330
#define TOTAL_WORDS 37240

char shifts[SHIFTS];
int max_index;

char dictWords[DICTLINES][100];
char encryptedSentence[MAX_WORD_LENGTH];

	//Opens dictionary2.txt and storing in dictWords
	//Checks if dictionary2.txt was opened successfully
	int openDict(char* filename){
		FILE *fp;
		fp = fopen(filename, "r");
		
		if(fp == NULL){
			printf("Error opening the file\n");
		}
		for(int x = 0; x < DICTLINES; x++){
			fscanf(fp, "%s", dictWords[x]);
		}
		fclose(fp);
		return 0;
	}

	//Sorts dictionary alphabetically using selection sort
	//Compares word extracted by outer loop to all words below it
	//If word above is alphabetically greater than word below, then swap the words
	int sort(){
		int i, j;
		char temp[MAX_WORD_LENGTH];
		
		openDict("dictionary2.txt");	
			
		for(i = 0; i < DICTLINES - 1; i++){
			for(j = i + 1; j < DICTLINES; j++){
				if(strcmp(dictWords[i], dictWords[j]) > 0){
					strcpy(temp, dictWords[i]);
					strcpy(dictWords[i], dictWords[j]);
					strcpy(dictWords[j], temp);
				}
			}
		}
		return 0;
	}

	//Compare decrypted word against dictionary word
	//Returns 0 if found and 1 if not found
	int stringCompare(char *dict, char *decrypted){
		int result;
		result = strcmp(dict, decrypted);
		if(result == 0){
			return 0;
		}
		else{
			return 1;
		}
	}
	//Checks decrypted word against dictionary words
	//If decrypted word is found in dictionary, increment shift key
	//If shift key count is greater than 5, set that as max
	int findInDict(char *decrypted, int key){
		//printf("%d %s\n", key, decrypted);	
		int i;
		
		for(i=0; i < DICTLINES; i++){
			//printf("%s\n", dictWords[i]);
			//result = strcmp(dictWords[i], decrypted);
			if(stringCompare(dictWords[i], decrypted) == 0){
				shifts[key]++;
				//printf("Found: %d\n", shifts[key]);
			}
		}
		return 0;
	}

	//Shifts each word of the sentence
	//Checks all characters are in range A-Z
	//Loops around if character is not in the range of A-Z
	//Returns shifted word
	char* shift(char* word, int key){
		char ch;
		char *decrypted;
		decrypted = malloc(MAX_WORD_LENGTH * sizeof *decrypted);

		for(int i=0; word[i] != '\0'; ++i){
			int k=0;
			ch = word[i];
			if(ch >= 'A' && ch <= 'Z'){
				ch = ch - key;
				if(ch < 'A'){
					ch = ch + 'Z' - 'A' + 1;
				}
			}

			decrypted[i] = ch;
		}
		return decrypted;
	}
	

	//Decrypts each word from sentences
	//Tries all twenty-six shifts
	//Passes word and key to shift() to do the shifts
	//Passes decrypted word and key/shift to compare() to check if it's an English word
	char* decrypt(char *word){
		//printf("\n%s\n", word);
		char ch;
		char *decrypted;
		decrypted = malloc(MAX_WORD_LENGTH * sizeof *decrypted);
		
		for(int key = 1; key < 26; key++){
			decrypted = shift(word, key);	
			findInDict(decrypted, key);
		}
		
		free(decrypted);
		return 0;
	}

	//Takes in sentence from encrypted_text
	//Splits sentence into words at spaces
	//Pass word to decrypt()
	char* split(char *l){
		char word[TOTAL_WORDS][20];
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
	
	//Reset shift count
	char clearShifts(){
		int sum;
		for(int x = 1; x < 26; x++){
			shifts[x] = 0;
		}
		for(int h = 1; h < 26; h++){
			return shifts[h];
		}
	}

	//Find best shift
	int bestShift(){
		int n = sizeof(shifts)/sizeof(shifts[0]);
		int max = shifts[0];
		for(int i = 1; i < 26; i++){
			if(shifts[i] > max){
				max = shifts[i];
				max_index = i;
			}
		}

		return max_index;
	}

	int main(){
		FILE *fp;
		fp = fopen("shifts.txt", "w");
		char buffer[MAX_WORD_LENGTH];
		int count = 0, max = shifts[0];

		sort();
		int n;
		while((fgets(buffer, MAX_WORD_LENGTH, stdin)) != NULL){
			count++;
			printf("%d\n", count);
			split(buffer);

			fprintf(fp, "%d\n", bestShift());

			clearShifts();
			if(count == 50){
				break;
			}
		}
		fclose(fp);
		return 0;
	}


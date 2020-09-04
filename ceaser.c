#include <stdio.h>
#include <stdlib.h>	
#include <string.h>

	int openDictionary(){
		FILE *fp;
 		fp = fopen("dictionary2.txt", "r");

		char c;

 		//creating array of strings with size 8732
 		char** words;
 		words = (char**) malloc(sizeof(char*)*8732);

 		//checks to make sure file was opened successfully
 		if(fp == NULL){
 			printf("Error while opening the file");
 		}

		//allocating memory for elements
 		for(int x=0; x<8732; x++){
 			words[x]=(char*) malloc(sizeof(char)*8732);
 		}

 		//reads line from dictionary2.txt and stores it in words
 		for(int i=0; i<8732; i++){
 			fgets(words[i], sizeof(char)*8732, fp);
 			printf("%s\n", words[i]);
 		}

 		fclose(fp);

 		//deallocating memory
 		free(words);

 	}

	int decrypt(char *word){
		//printf("%s\n", word);
		
		int i = 0;
		char ch;
		char decrypted[100];
		for(int key = 0; key < 26; key++){
			for(int i=0; word[i] != '\0'; ++i){
				ch = word[i];
				
				if(ch >= 'A' && ch <= 'Z'){
					ch = ch - key;

					if (ch < 'A'){
						ch = ch + 'Z' - 'A' + 1;
					}

					decrypted[i] = ch;
				}
			}

			printf("Key:%d %s\n", key, decrypted);
		}

	}

	int split(){
		int counter = 0;
		char **words= 0;
		int tempCounter = 0;

		char *line = NULL;
		size_t len = 0;
		size_t read = 0;
		
		//Read encrypted_text using getline()
		//Splits sentences into words at spaces using strtok()		
		while((read = getline(&line, &len, stdin)) != EOF)
		{	
			char *token = strtok(line, " ");
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
				}
				token = strtok(NULL, " ");
			}
		}


		//prints words
		for(int i=0; i<counter; i++){
			//printf("%d: %s\n", i, words[i]);
		}
	}


	int main(int argc, char* argv[]){
		split();
	}



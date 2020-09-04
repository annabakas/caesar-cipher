#include <stdio.h>
#include <stdlib.h>	
#include <string.h>

	
	
	//Opens dictionary2.txt using getline()
	int openDictionary(){
		FILE *fp;
 		fp = fopen("dictionary2.txt", "r");

		char *line = NULL;
		size_t len = 0;
		size_t read = 0;
		
		while((read = getline(&line, &len, fp)) != -1){
			printf("%s\n", line);
		}

		fclose(fp);


	}

	//Takes in *word from split() with individual words
	//Checks individual characters  in range A-Z  with every shift (1-26)
	//Second if statement checks if character is past Z and
	//loops it back around so that the character is back within the range of A-Z
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

	//Reads encrypted_text using getline() and splits 
	//sentences into words at spaces using strtok().
	int split(){
		int counter = 0;
		char **words= 0;
		int tempCounter = 0;

		char *line = NULL;
		size_t len = 0;
		size_t read = 0;
				
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
		/*
		for(int i=0; i<counter; i++){
			//printf("%d: %s\n", i, words[i]);
		}*/
	}


	int main(int argc, char* argv[]){
		split();
		//openDictionary();
	}



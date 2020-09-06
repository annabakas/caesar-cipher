#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINES 8732
#define WORDLENGTH 100

char dictWords[LINES][WORDLENGTH];

	//Reads dictionary2.txt and stores in 2D array
	/*char* openDictionary(){
		FILE *fp;
		fp = fopen("dictionary2.txt", "r");
		
		int i = 0;
		while(1){
			char r = (char)fgetc(fp);
			int k = 0;
			//Read until EOF
			while(!feof(fp)){
				dictWords[i][k++] = r;
				r = (char)fgetc(fp);
			}
			
			//Make last character of string null
			dictWords[i][k] = 0;
			
			//Check for EOF
			if(feof(fp)){
				break;
			}

			i++;
		}

		int j;

		for(j = 0; j <= i; j++){
			printf("%s\n", dictWords[j]);
			return dictWords[j];
		}

		fclose(fp);

	}*/
	
	int decrypt(char *word){
		//printf("%s\n", word);

		char ch;
		char decrypted[100];

		//int g = openDictionary();
		for(int key = 1; key < 27; key++){
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
			printf("Shift:%d %s\n", key, decrypted);
		}
	}

	//Takes in sentence from encrypted_text
	//Splits sentence into words using strtok()
	int compare(char *line){

		int counter = 0;
		char **words= 0;
		int tempCounter = 0;

		char *token = strtok(line, " ");

		char ch;
		char decrypted[100];

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
			//How do I rest **words / change the pointers?
		}

	}


	//Reads encrypted_text using getline()
	int main(){
		
		char *line = NULL;
		size_t len = 0;
		size_t read = 0;

		while((read = getline(&line, &len, stdin)) != EOF)
		{
			compare(line);	
		}

		
	}

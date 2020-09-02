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

	int main(int argc, char* argv[]){

		char *line = NULL;
		size_t len = 0;
		size_t read;
		//int total = 0;
		
		//Read encrypted_text using getline() while read != EOF
		//Splits sentences at spaces into words using strtok()
		while((read = getline(&line, &len, stdin)) != EOF){
			//printf("%s\n", line);
		
			char* token = strtok(line, " ");
			while(token != NULL){
				printf("%s\n", token);
				token = strtok(NULL, " ");
			}
			//total +=1;
			//printf("TOTAL: %d\n", total);
		}

		free(line);
	}

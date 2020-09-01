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

	int main(){

		char* string = malloc(4004*sizeof(char));

		int count = 0;
		char c = 0;
		
		
		//Reads and prints encrypted_text.txt from standard input
		while((c=getchar()) != EOF){
			if(c=='\n' || c == 0){
				printf("%s\n", string);	
				free(string);
				string = calloc(4004, sizeof(char));
				count = 0;
			}
			else{
				string = realloc(string, count+1);
				string[count] = c;
				count +=1;
			}
		}

		//openDictionary();
	}
		
	




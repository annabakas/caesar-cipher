#include <stdio.h>
#include <stdlib.h>

	/*Opens encrypted_text.txt and prints the output. Also checks to make sure the
	 * file was successfully opened.*/
	int openEncrypted(){
		FILE *fp;
		fp = fopen("encrypted_text.txt", "r");

		char c;
		
		//creating array of strings with size 4004
		char** sentences;
		sentences = (char**) malloc(sizeof(char*)*4004);

		//checks to make sure file was opened successfully
		if(fp == NULL){
			printf("Error while opening the file");
		}

		//allocating memory for string elements
		for(int x=0; x<4004; x++){
			sentences[x]=(char*) malloc(sizeof(char)*4004);
		}

		//reads line from encrypted_text.txt and stores it in sentences
		for(int i=0; i<4004; i++){
			fgets(sentences[i], sizeof(char)*4004, fp);
			printf("%s\n", sentences[i]);
		}

		fclose(fp);
		
		//deallocating memory
		free(sentences);
		
		/*
		do{
			c = fgetc(fp);
			putchar(c);
		}while(c != EOF);*/
	}

	/*Opens dictionary2.txt and checks to make sure that it was
	 * successfully opened. */

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
		
		//openEncrypted();
		openDictionary();

	}



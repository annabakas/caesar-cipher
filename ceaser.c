#include <stdio.h>

	/*Opens encrypted_text.txt and prints the output. Also checks to make sure the
	 * file was successfully opened.*/
	int openEncrypted(){
		FILE *fp;
		fp = fopen("encrypted_text.txt", "r");

		char c;

		if(fp == NULL){
			printf("Error while opening the file");
		}

		do{
			c = fgetc(fp);
			putchar(c);
		}while(c != EOF);
	}

	/*Opens dictionary2.txt and checks to make sure that it was
	 * successfully opened. */

	int openDictionary(){
		FILE *fp;
		fp = fopen("dictionary2.txt", "r");

		char c;

		if(fp == NULL){
			printf("Error while opening the file");
		}
	}

	char* alphabet(){
		char letters[27] = "abcdefghijklmnopqrstuvwxyz";
		return letters;
	}
	

	int main(){
		
		openEncrypted();
		openDictionary();
	}



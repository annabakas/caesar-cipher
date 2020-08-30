#include <stdio.h>

	int main(){

		/*opens file*/
		FILE *fp;
		fp = fopen("encrypted_text.txt", "r");

		char c;
		
		/*checks to see if file was successfully opened*/

		if (fp == NULL){
		       	printf("Error while opening file");
		}
		
		/*prints output of text file*/

		do{ 
			c = fgetc(fp);
			putchar(c);
		}while(c!=EOF);

		fclose(fp);

		return 0;
		
	}


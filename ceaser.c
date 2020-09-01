#include <stdio.h>
#include <stdlib.h>	
#include <string.h>

	int main(){

		char* string = malloc(4004*sizeof(char));

		int count = 0;
		char c = 0;
		
		//Reads and prints encrypted_text.txt from standard input
		while((c=getchar()) != EOF){
			if(c == '\n' || c == 0){
				printf("%s\n", string);	
				free(string);
				string = malloc(4004*sizeof(char));
				count = 0;
			}
			else{
				string = realloc(string, count+1);
				string[count] = c;
				count +=1;
			}
		}
	}
		
	




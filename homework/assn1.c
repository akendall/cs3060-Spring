#include <stdio.h>
#include <string.h>

/*Andrew Kendall
cs3060-001 Spring
assn1

I promise that this source code file has, in its entirety, been written by
myself and by no other person. If at any time an exact copy of this source
code is found to be used by another person in this term, I understand that
both myself and the student that submitted the copy will recieve zero on this
project*/

int main(int argc, char *argv[]){
	//loop through argv and print the contents to the console

	int i = 0;
	while(i < argc){
		printf("Arguments %d: %s\n", i, argv[i]);
		i++;
	}
	printf("number of arguments printed %d\n", argc);
	return 0;
}

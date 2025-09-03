#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
	int i;
	char *num = argv[1];
	
	fprintf(stdout, "arg[1] = %s \n", argv[1]);
	
	for (i = 0; 1 < strlen(argv[1]); i++)
	    fprintf(stdout, "num[%d] = %c \n", i, num[i]);
	    
	return 0;
}

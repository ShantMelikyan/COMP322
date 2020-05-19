#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv)
{
    FILE* file = NULL;
    char PATH[1024];
	strcpy(PATH, getenv("HOME"));
	strcat(PATH, "/lab6.log");  

  
    file = fopen(PATH, "a");
    if (file == NULL) {
        perror("Error opening file: ");
    }
    else{
        fprintf(file, "Pop %s\n", argv[1]);
        fclose(file);
    }
    while(1){};
    
    return 0;
    
}




#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    static FILE* file = NULL;
  
    file = fopen("/lab6.log", "a");
    if (file == NULL) {
        perror("Error opening file: ");
    }
    else{
        fprintf(file, "Pop %s\n", argv[0]);
        fclose(file);
    }
    
    return 0;
    
}



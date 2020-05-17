#include <stdio.h>
#include <stdlib.h>
#include <time.h> 


int main(int argc, char** argv)
{

    if (argc != 2) {
        fprintf(stderr, "Inccorrect input. Try again!\n");
        exit(EXIT_FAILURE);
    }

    int matrix_size = atoi(argv[1]);
    srand(time(0));
    
    /* generate random matrix size*size */ 
    for(int i = 0; i < matrix_size; i++){
        for( int j = 0; j < matrix_size; j++)
            printf("%d ", (rand() % (100 - (-100) + 1)) + (-100));
        printf("\n");
    }


    return 0;
}

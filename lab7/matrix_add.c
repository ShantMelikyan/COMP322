#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/times.h>
#include <time.h>
#include <limits.h>
#include <aio.h>

void matrix_add();

int main(int argc, char** argv)
{
    if (argc != 3){
        fprintf(stderr, "Inccorrect input. Try again!\n");
    }
    time_t start_time, end_time;
    srand(time(0)); 
    int matrix_size = atoi(argv[1]);
    int blocks = atoi(argv[2]);
    int block_size = matrix_size / atoi(argv[2]);
    const int BUF_SIZE = block_size * block_size * 4;
    int scalar = (rand() % (100 - (-100) + 1)) + (-100);

    if(matrix_size % blocks){
        fprintf(stderr, "WRONG PARAMETERS OF SIZE OR BLOCK");
        exit(EXIT_FAILURE);
    }

    time(&start_time);
    fprintf(stderr,"START: %d\n", (int)start);
    fprintf(stderr,"BUF_SIZE: %d\n", BUF_SIZE);
    fprintf(stderr,"MATRIX_SIZE: %d\n", matrix_size);
    fprintf(stderr,"BLOCK_SIZE: %d\n", block_size);
    fprintf(stderr, "SCALAR: %d\n", scalar);

    for(i = 0; i < blocks*blocks-1; i++)
    {
        // for y = 1 .. blocks
        //     async read request matrix[x, y]
        //     block = async read return matrix[x, y]
        //     matrix_add(block, block_size, scaler)
        //     async write request block
        //     async write return block

    }
    time(&end_time);
    fprintf(stderr,"STOP:  %ld\n", start);

    return 0;
}


void matrix_add()
{

    

}



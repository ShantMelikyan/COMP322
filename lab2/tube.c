//In this software project, you are to write a command-line tool that launches two child processes, 
//and sets up a pipe between them for inter-process communication.  
/*
#include<stdio.h>

int main()
{

printf("tube\n");

// The program allocates a pipe 					(see pipe(2))
// The program forks two children
// The parent process prints the PID of both children on stderr 	(see fprintf(3))
// The parent process closes access to the pipe and the child processes wires the pipe to allow for inter-process communication			(see dup2(2))
    // via the standard stdout-stdin approach			(see close(2))
// The first process executes the first command, and the second process executes the second command  						(see execve(2))
    // for the first iteration keep it simple — i.e., the child has no command line args
    // enhance your program to allow for an arbitrary number of command line args
// The program prints the return value of the first child and then the second child on stderr


    return 0;

}
*/
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define READ_END 0
#define WRITE_END 1

int main(int argc, char **argv)
{
    if(argc < 2){
		printf("No Input!");	
		return 0;
	}

    int pipe_fd[2];
    pid_t child1, child2;
    
    if (pipe(pipe_fd) == -1){ // The program allocates a pipe
        perror("pipe");
        exit(EXIT_FAILURE); 
    }
    child1 = fork();
    child2 = fork();

    if (child1 == -1){
        printf("Can't create a child1 process :( ");
        exit(EXIT_FAILURE);
    }
    if (child2 == -1){
        printf("Can't create a child2 process :( ");
        exit(EXIT_FAILURE);
    }
    if(child1 > 0 && child2 > 0){ 

        fprintf(stderr, "%s: $$ = %d\n", argv[1], child1);
        fprintf(stderr, "%s: $$ = %d\n", argv[1], child2);

        close(pipe_fd[READ_END]);
        //close(pipe_fd[WRITE_END]);
    }
    else{


    }

   // printf("***%s", argv[1]);
 
}
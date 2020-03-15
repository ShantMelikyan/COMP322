//In this software project, you are to write a command-line tool that launches two child processes, 
//and sets up a pipe between them for inter-process communication.  

#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define READ_END 0
#define WRITE_END 1

int comma_pos(char **argv, int argc);
void create_new_argv(char **argv, char **new_argv, int start_at, int size);

int main(int argc, char **argv)
{
    /* check if input is provided */
    if(argc < 2){
		printf("No Input!");	
		return 0;
	}
    int pipe_fd[2];
    pid_t child1;
    int status1, status2;
    int comma_index = 0;
    char *envr[] = {NULL};
    /*allocate a pipe*/
    if (pipe(pipe_fd) == -1){
        printf("can't allocate a pipe");
        exit(EXIT_FAILURE); 
    }
    comma_index = comma_pos(argv, argc);
    child1 = fork();
    
    if (child1 == -1){
        printf("Can't create a process 1");
        exit(EXIT_FAILURE);
    }
    else if(child1 == 0){
        dup2(pipe_fd[WRITE_END], 1);
        char *new_argv[argc - comma_index + 1];
        create_new_argv(argv, new_argv, 1, comma_index);
        execve(new_argv[0], new_argv, envr);
        exit(EXIT_SUCCESS);
    }
    else{
        pid_t child2 = fork(); // forking second child(process)
        if (child1 == -1){
            printf("Can't create a process 2");
            exit(EXIT_FAILURE);
        }
        else if(child2 == 0){
            dup2(pipe_fd[READ_END], 0);
            char *new_argv[comma_index];
            create_new_argv(argv, new_argv, comma_index + 1, argc);
            execve(new_argv[0], new_argv, envr);
            exit(EXIT_SUCCESS);
        }
        else{
            fprintf(stderr, "%s: $$ = %d\n", argv[1], child1);
            fprintf(stderr, "%s: $$ = %d\n", argv[comma_index+1], child2);
            close(pipe_fd[0]);
            close(pipe_fd[1]);
            waitpid(child2, &status2, WUNTRACED);
			waitpid(child1, &status1, WUNTRACED);
            fprintf(stderr, "%s: $? = %d\n", argv[1], status1);
			fprintf(stderr, "%s: $? = %d\n", argv[comma_index+1], status2);
        }
       
    }
    return 0;
}

/* looking for the comma and returning the position */
int comma_pos(char **argv, int argc)
{
	int index = -1;
	for(int i = 0; i < argc; i++){
		if(*argv[i] == ',')
			index = i;
	}
	return index;
}

/* preparing the new argv structure*/
void create_new_argv(char **argv, char *new_argv[], int start_at, int size)
{
    
    int j = 0;
    for(int i = start_at; i < size; i++){
        new_argv[j] = argv[i];
        j++;
    }
	new_argv[j] = NULL;

}
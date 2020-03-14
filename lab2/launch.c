//launch:  In this software project, you are to write a command-line tool that launches another process 
//and then have this process execute a particular program.

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    if(argc < 2){ // check if any argv input
		printf("No Input!");
		return 0;
	}

	pid_t pid;
	int status;
    pid = fork(); // The program forks a child process

	// checking if the fork was successfully made 
    if (pid == -1){
		printf("Can't create a process :( ");
		exit(EXIT_FAILURE);
    }
	if(pid == 0){
		char *envr[] = { NULL };
		char *new_argv[argc-1];

		/* preparing the new argv structure*/
		for(int i = 0; i < argc-1; i++){
			new_argv[i] = argv[i+1];
		}
		new_argv[argc-1] = NULL;

		/* The child process executes the supplied command 	(see execve(2))*/
		execve(argv[1], new_argv, envr);
		exit(EXIT_SUCCESS);
	}
	else{
		fprintf(stderr, "%s: $$ = %d\n", argv[1], pid); // The parent process prints the PID of the child on stderr
		waitpid(pid, &status, WUNTRACED);
		fprintf(stderr, "%s: $? = %d\n", argv[1], status); // The parent prints the return value of the child on stderr	(see waitpid(2))
	}

	return 0;
}
//launch:  In this software project, you are to write a command-line tool that launches another process 
//and then have this process execute a particular program. 

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    if(argc < 2){			// check if any argv input
		printf("No Input!");	
		return 0;
	}

	pid_t pid;
	int status;
    pid = fork(); // The program forks a child process				(see fork(2))

    if (pid == -1){               // checking if the fork was successfully made 
    	printf("Can't create a fork :( ");
        exit(EXIT_FAILURE);
    }

	if(pid == 0){ //child 
		char *envr[] = { NULL };
        char *new_argv[argc-1];

		for(int i = 0; i < argc-1; i++){
			new_argv[i] = argv[i+1];
		}
		new_argv[argc-1] = NULL;

		execve(argv[1], new_argv, envr); // The child process executes the supplied command 	(see execve(2))
		exit(EXIT_SUCCESS);
	}
	else{ // parent
		fprintf(stderr, "%s: $$ = %d\n", argv[1], pid); // The parent process prints the PID of the child on stderr	
		waitpid(pid, &status, WUNTRACED);
		fprintf(stderr, "%s: $? = %d\n", argv[1], status); // The parent prints the return value of the child on stderr	(see waitpid(2))
	}

	return 0;
}
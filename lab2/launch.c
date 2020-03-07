//launch:  In this software project, you are to write a command-line tool that launches another process 
//and then have this process execute a particular program. 

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    if(argc < 2){
		printf("No Input!");	
		return 0;
	}

	pid_t pid;
	int status;
    pid = fork();

    if (pid == -1) {               // checking if the fork was successfully made 
        printf("Can't create a fork :( ");
        exit(0);
    }

	if(pid == 0) { //child 
		char *env_args[] = { NULL };
		execve( (char*)argv[1], &argv[1], env_args);
		exit(EXIT_SUCCESS);
	}
	else { // parent
	
			fprintf(stderr, "%s:$$ = %d\n", argv[1], pid);
			pid_t tpid = waitpid(pid, &status, WUNTRACED);
			fprintf(stderr, "%s:$? = %d\n", argv[1], status);
            (void)tpid;
	}

	return 0;

}
// The program forks a child process				(see fork(2))
// The parent process prints the PID of the child on stderr	
// The child process executes the supplied command 	(see execve(2))
//     the child needs to prepare the new argv structure 	
// The parent prints the return value of the child on stderr	(see waitpid(2))

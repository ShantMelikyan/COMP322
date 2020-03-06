//launch:  In this software project, you are to write a command-line tool that launches another process 
//and then have this process execute a particular program. 

#include<stdio.h>

int main()
{
    printf("launch\n");

    
// The program forks a child process				(see fork(2))
// The parent process prints the PID of the child on stderr	
// The child process executes the supplied command 	(see execve(2))
// the child needs to prepare the new argv structure 	
// The parent prints the return value of the child on stderr	(see waitpid(2))

    return 0;
}
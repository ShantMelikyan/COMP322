#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <errno.h>

static int exit_flag = 0;

void eat();
void think();
void signal_handler(int signal);

struct Philosopher{
    int seats;
    int position;
    int cycles;
    sem_t* chopsticks[2];
    sem_t* returnVal;
    char buff1[32];
    char buff2[32];
    
}phil;

int main(int argc, char **argv)
{
    
    if(argc != 3){
		printf("Arguments required: 2, Arguments provided:%d \n", argc);
		exit(EXIT_FAILURE);
	}

    phil.seats = atoi(argv[1]);
	phil.position = atoi(argv[2]);
    phil.cycles = 0;

    if(phil.position > phil.seats){
        fprintf(stderr, "Seats are not avaliable for philosopher: %d \n", phil.position);
        return 0;
    }
    /* create name buffers for semaphores */ 
    char chopst_name1[32];
	char chopst_name2[32];
	sprintf(chopst_name1, "%d", phil.position);
	sprintf(chopst_name2, "%d", (phil.position+1) % phil.seats);

    phil.buff1[0] = '/';  
    strcat(phil.buff1, chopst_name1);
	phil.buff2[0] = '/';  
    strcat(phil.buff2, chopst_name2);

    /* create semaphores */  
	phil.returnVal = sem_open(phil.buff1, O_CREAT, 0666, 1);
    if(phil.returnVal == SEM_FAILED)
		perror("cant create semaphore 0");
    phil.chopsticks[0] = phil.returnVal;

    phil.returnVal = sem_open(phil.buff2, O_CREAT, 0666, 1);
    if(phil.returnVal == SEM_FAILED)
		perror("cant create semaphore 1");
    phil.chopsticks[1] = phil.returnVal;

    /* create signal handler */
    if(signal(SIGTERM, signal_handler) == SIG_ERR )
        fprintf(stderr, "Can't handle signal");

    int sval0, sval1;
    /* main logic algothithm */
    do{
        sem_getvalue(phil.chopsticks[0], &sval0);
		sem_getvalue(phil.chopsticks[1], &sval1);

        if(sval0 != 0 || sval1 != 0){
            sem_wait(phil.chopsticks[0]);
            sem_wait(phil.chopsticks[1]);
            eat(phil.position);
            
            sem_post(phil.chopsticks[0]);
            sem_post(phil.chopsticks[1]);
            think(phil.position);
            phil.cycles = phil.cycles + 1;
        }

    } while (exit_flag == 0);

}

void eat()
{
    printf("Philosopher %d is eating.\n", phil.position);
    usleep(rand() % 9999999);
}

void think()
{
    printf("Philosopher %d is thinking\n", phil.position);
    usleep(rand() % 9999999);
}

void signal_handler(int sig)
{
    signal(SIGTERM, signal_handler);
    if (sig == SIGTERM){
        sem_close(phil.chopsticks[0]);
		sem_close(phil.chopsticks[1]);
		sem_unlink(phil.buff1);
		sem_unlink(phil.buff2);
        exit_flag = 1;
    }
        
    fprintf(stderr, "Philosopher [%d] completed %d cycles\n", phil.position, phil.cycles);
}


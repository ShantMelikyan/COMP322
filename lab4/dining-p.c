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

#define CHOPSTICK1  "/chopstick_1"
#define CHOPSTICK2  "/chopstick_2"
static int exit_flag = 0;

void eat(int phil_po);
void think(int phil_po);
void signal_handler(int signal);

struct Philosopher{
    int seats;
    int position;
    int cycles;
    sem_t* chopsticks[2];
    
}phil;

int main(int argc, char **argv)
{
    //struct Philosopher phil;
    
    if(argc != 3){
		printf("Arguments required: 2, Arguments provided:%d \n", argc);
		exit(EXIT_FAILURE);
	}

    phil.seats = atoi(argv[1]);
	phil.position = atoi(argv[2]);
    phil.cycles = 0;

    if(phil.position > phil.seats) {
        fprintf(stderr, "Seats are not avaliable\n");
        return 0;
    }

	phil.chopsticks[0] = sem_open(CHOPSTICK1, O_CREAT, 0666, 1);
    if(phil.chopsticks[0]==SEM_FAILED)
		perror("cant creat semaphore 0");
    phil.chopsticks[1] = sem_open(CHOPSTICK2, O_CREAT, 0666, 1);
    if(phil.chopsticks[0]==SEM_FAILED)
		perror("cant creat semaphore 0");

    if(signal(SIGTERM, signal_handler) == SIG_ERR )
        fprintf(stderr, "Can't handle signal");

    do{
        sem_wait(phil.chopsticks[0]);
        sem_wait(phil.chopsticks[1]);
     
        eat(phil.position);
        
        sem_post(phil.chopsticks[0]);
        sem_post(phil.chopsticks[1]);
 
        think(phil.position);
        phil.cycles = phil.cycles + 1;
        
    } while (exit_flag == 0);

}

void eat(int phil_pos)
{
    printf("Philosopher %d is eating.\n", phil_pos);
    usleep(rand() % 9999999);
}
void think(int phil_pos)
{
    printf("Philosopher %d is thinking\n", phil_pos);
    usleep(rand() % 9999999);
}

void signal_handler(int sig)
{
    signal(SIGTERM, signal_handler);
    if (sig == SIGTERM) 
        exit_flag = 1;

    fprintf(stderr, "Philosopher [%d] completed %d cycles\n", phil.position, phil.cycles);
}


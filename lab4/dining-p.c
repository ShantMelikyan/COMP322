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
    int left_stick;
    int right_stick;
    int cycles;
    sem_t** chopsticks;
    sem_t* chopstick_alloc;
};

int main(int argc, char **argv)
{
    struct Philosopher phil;
    
    if(argc != 3){
		printf("Arguments required: 2, Arguments provided:%d \n", argc);
		exit(EXIT_FAILURE);
	}
    int cycles = 0;

    phil.seats = atoi(argv[1]);
	phil.position = atoi(argv[2]);
    phil.cycles = 0;

    if(phil.position > phil.seats) {
        fprintf(stderr, "Seats are not avaliable\n");
        return 0;
    }

    phil.chopsticks = malloc(sizeof (sem_t*) * phil.seats);
    for (int i = 0; i < phil.seats; i++) {
		phil.chopsticks[i] = sem_open(CHOPSTICK1, O_CREAT, 0666, 1);
	}
    phil.chopstick_alloc = sem_open("critical_section", O_CREAT, 0666, 1);

    if(signal(SIGTERM, signal_handler) == SIG_ERR )
        fprintf(stderr, "Can't handle signal");

    do{
        sem_wait(phil.chopstick_alloc);
        sem_wait(phil.chopstick_alloc);
     
        eat(phil.position);
        
        sem_post(phil.chopstick_alloc);
        sem_post(phil.chopstick_alloc);
 
        think(phil.position);/* think for awhile */
        cycles++;
    } while (exit_flag == 0);

}

void eat(int phil_pos)
{
    printf("Philosopher %d is eating.\n", phil_pos);
    usleep(rand() % 999);
}
void think(int phil_pos)
{
    printf("Philosopher %d is thinking\n", phil_pos);
    usleep(rand() % 999);
}

void signal_handler(int signal)
{
    if (signal == SIGTERM) 
        exit_flag = 1;
}


//= (possition + 1) % seats;
// = position % seats;
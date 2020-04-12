//In this lab, you will develop single program that catches signals.  When the program catches the signals,
// it writes particular information onto stdout.   

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

void handle_reg(int mysignal);
int sig_number(char*sig);

static const char* signals[27] = {  "HUP", "INT", "QUIT", "ILL", "TRAP", "ABRT", "IOT", "BUS", "FPE","USR1", 
                                    "SEGV", "USR2", "PIPE", "ALRM", "TERM", "STKFLT", "CHLD", "CONT", "TSTP", 
                                    "TTIN", "TTOU", "URG", "XCPU", "XFSZ", "VTALRM", "PROF", "WINCH"};


int main(int argc, char** argv)
{
    if(argc < 2){
        printf("no input!");
        return 0;
    }
    fprintf(stderr, "%s: $$ = %d\n", argv[0], getpid());

    for(int i = 1; i < argc; i++){
        if(signal(sig_number(argv[i]), handle_reg) == SIG_ERR )
            fprintf(stderr, "Can't handle signal");
    }

    while(1){
        pause();
    }

    return 0;
}

void handle_reg(int mysignal) 
{
    signal(mysignal, handle_reg);
    static int count_TERMs, total_sigs = 0;
    time_t start_time;
    time(&start_time);

    printf(stderr,"SIG%s caught at %d\n", signals[mysignal-1], (int)start_time);
    total_sigs++;
    
    if(mysignal == SIGTERM)
        count_TERMs++;
	else
        count_TERMs = 0;

    if(count_TERMs == 3){
        fprintf(stderr, "catcher: Total signals count = %d\n" , total_sigs);
        exit(EXIT_SUCCESS);
    }

}

int sig_number(char*sig) // this fucntion returns the Position of the signal 
{
    int ret_signal = -1;
    for(unsigned int i = 0; i < 27; i++){
        if(strcmp(sig, signals[i]) == 0)
            ret_signal = i;
    }
    return ++ret_signal;
}

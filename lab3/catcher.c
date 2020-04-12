#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

void handle_reg(int mysignal);
int sig_number(char*sig);

static const char* signals[27] = {  "HUP", "INT", "QUIT", "ILL", "TRAP", "ABRT", "IOT", "BUS", "FPE","USR1", 
                                    "SEGV", "USR2", "PIPE", "ALRM", "TERM", "STKFLT", "CHLD", "CONT", "TSTP", 
                                    "TTIN", "TTOU", "URG", "XCPU", "XFSZ", "VTALRM", "PROF", "WINCH"};



    for(int i = 1; i < argc; i++){
        if(signal(sig_number(argv[i]), handle_reg) == SIG_ERR )
            fprintf(stderr, "Can't handle signal");
    }

    while(1){
        pause();
    }

	size_t len = strlen(argv[0]);
	prog_name = calloc(len, 1);
	prog_name = argv[0];

	fprintf(stderr, "%s: $$ = %d\n", prog_name, getpid());   // show process ID

	// register a handler for each command line argument
	int i = 0;
	for(i = 1; i < argc; i++) {
		signal (sig_name2number(argv[i]), thandler);
	}

	for(;;){
		pause();   // pause self continually
	}

	return 0;
}

void handle_reg(int mysignal)
{

    signal(mysignal, handle_reg);
    static int count_TERMs, total_sigs = 0;
    time_t start_time;
    time(&start_time);

    fprintf(stderr,"SIG%s caught at %d\n", signals[mysignal-1], (int)start_time);
    total_sigs++;
    
    if(mysignal == SIGTERM){
        count_TERMs++;
	}
	else{
        count_TERMs = 0;
	}

    if(count_TERMs == 3){
        fprintf(stderr, "catcher: Total signals count = %d\n" , total_sigs);
        exit(EXIT_SUCCESS);
    }

}

int sig_number(char*sig)
{
    int ret_signal = -1;
    for(unsigned int i = 0; i < 27; i++){
        if(strcmp(sig, signals[i]) == 0){
            ret_signal = i;
        }
    }
    return ++ret_signal;
}

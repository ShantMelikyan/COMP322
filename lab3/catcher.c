//In this lab, you will develop single program that catches signals.  When the program catches the signals,
// it writes particular information onto stdout.   

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <string.h>
//#include <sys/times.h>

void handle_reg(int mysignal);

static const char* signals[27] = {  "HUP", "INT", "QUIT", "ILL", "TRAP", "ABRT", "IOT", "BUS", "FPE","USR1", 
                                    "SEGV", "USR2", "PIPE", "ALRM", "TERM", "STKFLT", "CHLD", "CONT", "TSTP", 
                                    "TTIN", "TTOU", "URG", "XCPU", "XFSZ", "VTALRM", "PROF", "WINCH" };


int main(int argc, char** argv)
{
    if(argc < 2){
        printf("no input!");
        return 0;
    }
    fprintf(stderr, "%s: $$ = %d\n", argv[0], getpid());

    int i = 0;
    for(int i = 1; i < argc; i++)
    {
        signal(SIGTERM, handle_reg);
    }

    while(1)
    {
        printf("i = %d\n" , i);
        i++;
        sleep(1);
        //pause();
    }

    return 0;
}

void handle_reg(int mysignal)
{
    static int count_TERMs, total_sigs = 0;
    time_t start_time;
	time(&start_time);

    printf("SIG%d caught at %d\n", mysignal, (int)start_time);
    total_sigs++;
    if(mysignal == SIGTERM){
		count_TERMs++;
	}
	else {
		count_TERMs = 0;
	}

    if(count_TERMs == 3){
        fprintf(stderr, "catcher: Total signals count = %d" , total_sigs);
    }

}

//+ The program processes the command line arguments
    //+ The arguments indicate which signals to catch
//+ The program emits a status line that includes its PID to stderr 
// The program registers a handler for each argument		              (see signal(2))
// The program pauses itself continually 				  (see pause(2))
// The handler registers itself again			(read about unreliable signals)
// The handler emits a line to stdout that indicates 
//      the signal caught, and 
//      the time it was caught 					    (see time(2))
// The program gracefully terminates after 
//      receiving three successive SIGTERM signals	   (hint: static int count)
// The program emits a final status message to stderr that indicates
//      the number of signals caught

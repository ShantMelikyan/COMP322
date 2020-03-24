//In this lab, you will develop single program that catches signals.  When the program catches the signals,
// it writes particular information onto stdout.   

#include<stdio.h>

int main()
{

    printf("hello world");

    return 0;
}

// The program processes the command line arguments
// The arguments indicate which signals to catch
// The program emits a status line that includes its PID to stderr
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

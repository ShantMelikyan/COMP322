#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <string.h>




void thandler(int);   // declare handler for signal
int sig_name2number(char*);   // declare function to get signal number
char* number2sig_name(int);   // decalre function too get signal name again

static int count = 0;  // count total number of caught signals

const char* prog_name;  // program name for print outs





int main(int argc, char **argv) {

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






void thandler (int signum) {
	signal (signum, thandler);   // registers itself again

	static int term_count = 0;

	// print epoch time when signal caught
	time_t start_time;
	start_time = time(NULL);
	printf("%s caught at %i\n", number2sig_name(signum), (int) start_time);
	count++;


	if(signum == SIGTERM) {
		term_count++;
	}
	else {
		term_count = 0;
	}

	if(term_count == 3) {    // gracefully terminate after 3 consecutive SIGTERM signals
		fprintf(stderr, "%s: Total signals count = %d\n", prog_name, count);   // print number of signals caught
		exit(0);
	}

}






int sig_name2number(char *s) {    // convert command line argument to signal number
  int signumber = -1;

  if (!strcmp(s, "HUP"))     { signumber = SIGHUP; }
  if (!strcmp(s, "INT"))     { signumber = SIGINT; }
  if (!strcmp(s, "QUIT"))    { signumber = SIGQUIT; }
  if (!strcmp(s, "ILL"))     { signumber = SIGILL; }
  if (!strcmp(s, "TRAP"))    { signumber = SIGTRAP; }
  if (!strcmp(s, "ABRT"))    { signumber = SIGABRT; }
  if (!strcmp(s, "IOT"))     { signumber = SIGIOT; }
  if (!strcmp(s, "BUS"))     { signumber = SIGBUS; }
  if (!strcmp(s, "FPE"))     { signumber = SIGFPE; }
  if (!strcmp(s, "KILL"))    { signumber = SIGKILL; }
  if (!strcmp(s, "USR1"))   { signumber = SIGUSR1; }
  if (!strcmp(s, "SEGV"))   { signumber = SIGSEGV; }
  if (!strcmp(s, "USR2"))   { signumber = SIGUSR2; }
  if (!strcmp(s, "PIPE"))   { signumber = SIGPIPE; }
  if (!strcmp(s, "ALRM"))   { signumber = SIGALRM; }
  if (!strcmp(s, "TERM"))   { signumber = SIGTERM; }
  if (!strcmp(s, "STKFLT")) { signumber = SIGSTKFLT; }
  if (!strcmp(s, "CHLD"))   { signumber = SIGCHLD; }
  if (!strcmp(s, "CONT"))   { signumber = SIGCONT; }
  if (!strcmp(s, "STOP"))   { signumber = SIGSTOP; }
  if (!strcmp(s, "TSTP"))   { signumber = SIGTSTP; }
  if (!strcmp(s, "TTIN"))   { signumber = SIGTTIN; }
  if (!strcmp(s, "TTOU"))   { signumber = SIGTTOU; }
  if (!strcmp(s, "URG"))    { signumber = SIGURG; }
  if (!strcmp(s, "XCPU"))   { signumber = SIGXCPU; }
  if (!strcmp(s, "XFSZ"))   { signumber = SIGXFSZ; }
  if (!strcmp(s, "VTALRM")) { signumber = SIGVTALRM; }
  if (!strcmp(s, "PROF"))   { signumber = SIGPROF; }
  if (!strcmp(s, "WINCH"))  { signumber = SIGWINCH; }

  return signumber;
}




char* number2sig_name(int num) {   // convert signal number to previously entered command line argument

  char* signame = malloc(25);

  if ( num == SIGHUP )  { signame = "SIGHUP"; }
  if ( num == SIGINT )  { signame = "SIGINT"; }
  if ( num == SIGQUIT )  { signame = "SIGQUIT"; }
  if ( num == SIGILL )  { signame = "SIGILL"; }
  if ( num == SIGTRAP )  { signame = "SIGTRAP"; }
  if ( num == SIGABRT )  { signame = "SIGABRT"; }
  if ( num == SIGIOT )  { signame = "SIGIOT"; }
  if ( num == SIGBUS )  { signame = "SIGBUS"; }
  if ( num == SIGFPE )  { signame = "SIGFPE"; }
  if ( num == SIGKILL )  { signame = "SIGKILL"; }
  if ( num == SIGUSR1 )  { signame = "SIGUSR1"; }
  if ( num == SIGSEGV )  { signame = "SIGSEGV"; }
  if ( num == SIGUSR2 )  { signame = "SIGUSR2"; }
  if ( num == SIGPIPE )   { signame = "SIGPIPE"; }
  if ( num == SIGALRM )  { signame = "SIGALRM"; }
  if ( num == SIGTERM )  { signame = "SIGTERM"; }
  if ( num == SIGSTKFLT )   { signame = "SIGSTKFLT"; }
  if ( num == SIGCHLD )   { signame = "SIGCHLD"; }
  if ( num == SIGCONT )   { signame = "SIGCONT"; }
  if ( num == SIGSTOP )    { signame = "SIGSTOP"; }
  if ( num == SIGTSTP )  { signame = "SIGTSTP"; }
  if ( num == SIGTTIN )  { signame = "SIGTTIN"; }
  if ( num == SIGTTOU )  { signame = "SIGTTOU"; }
  if ( num == SIGURG )  { signame = "SIGURG"; }
  if ( num == SIGXCPU )   { signame = "SIGXCPU"; }
  if ( num == SIGXFSZ )  { signame = "SIGXFSZ"; }
  if ( num == SIGVTALRM )  { signame = "SIGVTALRM"; }
  if ( num == SIGPROF )  { signame = "SIGPROF"; }
  if ( num == SIGWINCH )  { signame = "SIGWINCH"; }

  return signame;
}


//+ The program processes the command line arguments
    //+ The arguments indicate which signals to catch
//+ The program emits a status line that includes its PID to stderr 
//+ The program registers a handler for each argument		              (see signal(2))
//+ The program pauses itself continually 				  (see pause(2))
// The handler registers itself again			(read about unreliable signals)
// The handler emits a line to stdout that indicates 
//      the signal caught, and 
//+      the time it was caught 					    (see time(2))
//+ The program gracefully terminates after 
//+      receiving three successive SIGTERM signals	   (hint: static int count)
//+ The program emits a final status message to stderr that indicates
//+     the number of signals caught


/**
 * @author Jefferson Flores Herrera 
			Vanessa Mayra Macedo Huaman
 */

#include <stdio.h>   // puts(), printf()
#include <signal.h>  // SIGFPE, SIGSEGV, SIGINT
#include <stdlib.h>  // exit(), EXIT_SUCCESS, EXIT_FAIURE
#include <unistd.h>  // getpid(), pause()
#include <sys/wait.h>   // For wait and related macros.

#define TOTAL_SIGNALS 12
int signalsToReceive[TOTAL_SIGNALS] = {SIGHUP, SIGINT, SIGQUIT, SIGILL, SIGABRT, SIGFPE, SIGSEGV, SIGPIPE,
				 SIGALRM, SIGTERM, SIGCHLD, SIGTSTP};

void handler(int sig, siginfo_t *siginfo, void *context){
		
	printf("Signal number: %d Signal code: %d errno value: %d Sending process ID: %d\n",
			siginfo -> si_signo,
			siginfo -> si_code,
			siginfo -> si_errno,
			siginfo -> si_pid);		
	switch(sig){
		case SIGHUP:
			printf("Nueva senal recibida %d, con si_signo = %d, si_code = %d\n", sig, siginfo -> si_signo, siginfo -> si_code);
			break;
		case SIGINT:
			printf("Nueva senal recibida %d, con  si_signo= %d, si_code = %d\n", sig, siginfo -> si_signo, siginfo -> si_code);
			break;
		case SIGQUIT:
			printf("Nueva senal recibida %d, con si_signo = %d, si_code = %d\n", sig, siginfo -> si_signo, siginfo -> si_code);
			break;
		case SIGILL:
			printf("Nueva senal recibida %d, con si_signo = %d, si_code = %d\n", sig, siginfo -> si_signo, siginfo -> si_code);
			break;
		case SIGABRT:
			printf("Nueva senal recibida %d, con si_signo = %d, si_code = %d\n", sig, siginfo -> si_signo, siginfo -> si_code);
			break;
		case SIGFPE:
			printf("Nueva senal recibida %d, con si_signo = %d, si_code = %d\n", sig, siginfo -> si_signo, siginfo -> si_code);
			break;
		case SIGSEGV:
			printf("Nueva senal recibida %d, con si_signo = %d, si_code = %d\n", sig, siginfo -> si_signo, siginfo -> si_code);
			break;
		case SIGPIPE:
			printf("Nueva senal recibida %d, con si_signo = %d, si_code = %d\n", sig, siginfo -> si_signo, siginfo -> si_code);
			break;
		case SIGALRM:
			printf("Nueva senal recibida %d, con si_signo = %d, si_code = %d\n", sig, siginfo -> si_signo, siginfo -> si_code);
			break;
		case SIGTERM:
			printf("Nueva senal recibida %d, con si_signo = %d, si_code = %d\n", sig, siginfo -> si_signo, siginfo -> si_code);
			break;
		case SIGCHLD:
			printf("Nueva senal recibida %d, con si_signo = %d, si_code = %d\n", sig, siginfo -> si_signo, siginfo -> si_code);
			break;
		case SIGTSTP:
			printf("Nueva senal recibida %d, con si_signo = %d, si_code = %d\n", sig, siginfo -> si_signo, siginfo -> si_code);
			exit(EXIT_SUCCESS);
			break;
		default:
			printf("La senal no es soportada\n");
			exit(EXIT_FAILURE);
			break;
	}
}
void installSignalsCatcher(struct sigaction *action){
	for(int i = 0; i < TOTAL_SIGNALS; i++)
		sigaction(signalsToReceive[i], action ,NULL);
	
}
int main(){	

	struct sigaction act;
	act.sa_sigaction = &handler;
	act.sa_flags = SA_SIGINFO;
	installSignalsCatcher(&act);
	while(1){
		kill(getpid(),SIGSTOP);
	}

	return 0;
}

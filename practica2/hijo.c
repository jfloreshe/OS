/**
 * @author Jefferson Flores Herrera 
			Vanessa Mayra Macedo Huaman
 */
#include <stdio.h>   // puts(), printf()
#include <signal.h>  // SIGFPE, SIGSEGV, SIGINT
#include <stdlib.h>  // exit(), EXIT_SUCCESS, EXIT_FAIURE
#include <unistd.h>  // getpid(), pause()
#include <sys/wait.h>   // For wait and related macros.
#include <string.h>

#define TOTAL_SIGNALS 14
int i = 0;

void sendSignals(int);
void handlerSGCHLD(int, siginfo_t *, void *);

int signalsToSend[TOTAL_SIGNALS] = {SIGHUP, SIGINT, SIGQUIT, SIGILL, SIGABRT, SIGFPE, SIGKILL, SIGSEGV, SIGPIPE,
				 SIGALRM, SIGTERM, SIGCHLD, SIGSTOP, SIGTSTP};

int main(){	

	int status;

	pid_t w,pid = fork();
	if(pid < 0){
		perror("ERROR; no se pudo crear al nieto desde hijo.c\n");	
		exit(EXIT_FAILURE);
	}else if(pid == 0){//child process
		printf("creating nieto\n");
		execlp("./nieto","nieto",(char*)NULL);
		perror("ERROR: nieto.c no se ha ejecutado\n");
		exit(EXIT_FAILURE);
	}else{//parent process
		//TODO detectar si el proceso nieto muere
		do{
			w = waitpid(pid, &status, WUNTRACED | WCONTINUED);
			if(w == -1){
				perror("el pid que mando no es un proceso\n");
				exit(EXIT_FAILURE);
			}
			if(WIFSTOPPED(status)){
				sendSignals(pid);
			}
		}while(!WIFEXITED(status) && !WIFSIGNALED(status));
		printf("hijo.c acabo de ejecutarse\n");
	}
	
	return 0;
}

void sendSignals(int pidReceiver){
	int pidSender = getpid();
	printf("Desde proceso %d se esta enviando la senal %d al proceso %d\n",pidSender, signalsToSend[i], pidReceiver);
	kill(pidReceiver,SIGCONT);
	int signalSentStatus = kill(pidReceiver,signalsToSend[i]);
	sleep(5);
	if(signalSentStatus == 0)//succes
		i++;
}

void handlerSGCHLD(int sig, siginfo_t *siginfo, void *context){
	if(sig == SIGCHLD){
		if(siginfo -> si_code == CLD_KILLED) ;
		//add jump
		else if(siginfo -> si_code == CLD_STOPPED) ;
			//send signal to continue

	}
}
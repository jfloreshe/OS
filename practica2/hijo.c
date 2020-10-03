/**
 * @author Jefferson Flores Herrera 
			Vanessa Mayra Macedo Huaman
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/time.h>
#include <signal.h>
#include <time.h>

int main(){	
	pid_t pid = fork();
	int pidNieto;
	if(pid < 0){
		printf("Error");	
	}else if(pid == 0){//child process
	//	execlp("/usr/bin/gcc", "gcc","nieto.c","-lrt","-o","nieto",(char*)NULL);
		pidNieto = getpid();
		execlp("./nieto","nieto",NULL);
	}else{//parent process
		kill(pidNieto,SIGHUP);
		sleep(5);
		printf("executing SIGHUP\n");
		kill(pidNieto,SIGINT);
		sleep(5);
		printf("executing SIGINT\n");
		kill(pidNieto,SIGQUIT);
		sleep(5);
		printf("executing SIGQUIT\n");
		kill(pidNieto,SIGILL);
		sleep(5);
		printf("executing SIGILL\n");
		kill(pidNieto,SIGABRT);
		sleep(5);
		printf("executing SIGABRT\n");
		kill(pidNieto,SIGFPE);
		sleep(5);
		printf("executing SIGFPE\n");
		kill(pidNieto,SIGKILL);
		sleep(5);
		printf("executing SIGKILL\n");
		kill(pidNieto,SIGSEGV);
		sleep(5);
		printf("executing SIGSEGV\n");
		kill(pidNieto,SIGPIPE);
		sleep(5);
		printf("executing SIGPIPE\n");
		kill(pidNieto,SIGALRM);
		sleep(5);
		printf("executing SIGALRM\n");
		kill(pidNieto,SIGTERM);
		sleep(5);
		printf("executing SIGTERM\n");
		kill(pidNieto,SIGCHLD);
		sleep(5);
		printf("executing SIGCHLD\n");
		kill(pidNieto,SIGSTOP);
		sleep(5);
		printf("executing SIGSTOP\n");
		kill(pidNieto,SIGTSTP);
		sleep(5);
		printf("executing SIGTSTP\n");
		//TODO detectar si el proceso nieto muere
		int wstatus;
		wait(&wstatus);
		if(WIFEXITED(wstatus)){
			printf("[CHILD] nieto done %d\n", WEXITSTATUS(wstatus));
		}
	}
	
	return 0;
}

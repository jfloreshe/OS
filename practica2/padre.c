/**
 * @author Jefferson Flores Herrera 
			Vanessa Mayra Macedo Huaman
 */

#include <stdio.h>   // puts(), printf()
#include <signal.h>  // SIGFPE, SIGSEGV, SIGINT
#include <stdlib.h>  // exit(), EXIT_SUCCESS, EXIT_FAIURE
#include <unistd.h>  // getpid(), pause()
#include <sys/wait.h>   // For wait and related macros.


int main(){	
	pid_t pid = fork(); //Creando desde el padre un nuevo hijo
	if(pid < 0){
		perror("ERROR; no se pudo crear al hijo desde padre.c\n");	
		exit(EXIT_FAILURE);
	}else if(pid == 0){//child process
		execlp("./hijo","hijo",(char*)NULL);
		perror("ERROR: hijo.c no se ha ejecutado\n");
		exit(EXIT_FAILURE);
	}else{//parent process		
		int waitStatus;
		waitpid(-1, &waitStatus, WUNTRACED);
		if(WIFEXITED(waitStatus)){
			printf("hijo.c ha finalizado correctamente retornando %d\n", WEXITSTATUS(waitStatus));
			exit(EXIT_SUCCESS);
		}
	}
	
	return 0;
}

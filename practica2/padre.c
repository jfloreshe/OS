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
	if(pid < 0){
		printf("Error");	
	}else if(pid == 0){//child process
	//	execlp("/usr/bin/gcc", "gcc","hijo.c","-lrt","-o","hijo",(char*)NULL);
		execlp("./hijo","hijo",NULL);
	}else{//parent process
		int wstatus;
		wait(&wstatus);
		if(WIFEXITED(wstatus)){
			printf("[PARENT]child done %d", WEXITSTATUS(wstatus));
		}
	}
	
	return 0;
}

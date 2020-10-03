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
	while(1){
		printf("[NIETO] nieto\n");	
		sleep(5);
	}
	return 0;
}

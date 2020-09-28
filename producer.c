/**
 * Simple program demonstrating shared memory in POSIX systems.
 *
 * This is the producer process that writes to the shared memory region.
 *
 * Figure 3.16
 * 
 * To compile, enter
 * 	gcc shm-posix-producer.c -lrt
 *
 * @author Silberschatz, Galvin, and Gagne
 * Operating System Concepts  - Tenth Edition
 * Copyright John Wiley & Sons - 2018
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
#include <time.h>

#define BUFFER_SIZE 10

struct item{
	pid_t pid;
} ;

struct region{
	int in, out;
	struct item buffer[BUFFER_SIZE];
} ;

int main()
{
	srand(time(NULL));
	const int SIZE = sizeof(struct region);
	const char *name = "OS";
	struct region *rptr;
	int fd;
	
	fd = shm_open(name, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR); 
	ftruncate(fd,SIZE);
	rptr = mmap(NULL, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if(rptr == MAP_FAILED){
		printf("Map Failed\n");
		return -1;
	}
	
	rptr -> in	= 0;
	rptr -> out = 0;

	struct item next_produced;
	pid_t pid;	
	while(1){
		pid = fork();
		if(pid < 0){
			fprintf(stderr, "fork fallo");
			return 1;//error
		} else if(pid == 0){
			next_produced.pid = getpid();
			printf("[tiempo] P(%d): Creando Proceso %d (tiempo)\n", getppid(), next_produced.pid);
		} else{
			wait(NULL);
		}
		//TODO add time creation
		//TODO add tiempo

		while((((rptr -> in ) + 1) % BUFFER_SIZE) == (rptr -> out))
			;//buffer lleno no hacer nada
		rptr -> buffer[rptr -> in] = next_produced;
		rptr -> in = ((rptr -> in) + 1) % BUFFER_SIZE;

		//TODO add random in sleep 1 to 5
		int r = rand() % 5 + 1;
		sleep(r);
	}
	
	return 0;
}

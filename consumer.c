/**
 * Simple program demonstrating shared memory in POSIX systems.
 *
 * This is the consumer process
 *
 * Figure 3.18
 *
 * To compile, enter
 *	gcc shm-posix-consumer.c -lrt
 *
 * @author Gagne, Galvin, Silberschatz
 * Operating System Concepts - Tenth Edition
 * Copyright John Wiley & Sons - 2018
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <signal.h>
#include <time.h>
#include <string.h>

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

	/* open the shared memory segment */
	fd = shm_open(name, O_RDWR, S_IRUSR | S_IWUSR);
	if (fd == -1) {
		printf("shared memory failed\n");
		exit(-1);
	}

	/* now map the shared memory segment in the address space of the process */
	rptr = mmap(NULL,SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (rptr == MAP_FAILED) {
		printf("Map failed\n");
		exit(-1);
	}

	/* now read from the shared memory region */
	struct item next_consumed;
	while(1){
		while(rptr -> in == rptr -> out)
			; // buffer vacio no hacer nada
		next_consumed = rptr -> buffer[rptr -> out];
		rptr -> out = ((rptr -> out) + 1) % BUFFER_SIZE;
		//TODO add tiempo y tiempo vivido
		printf("[tiempo] C(%d): Matando Proceso %d (vivio tiempo)\n", getpid(), next_consumed.pid);
		kill(next_consumed.pid, SIGKILL);
		//TODO add random sleep
		int r = rand() % 5 + 1;
		sleep(r);
	}	
	/* remove the shared memory segment */
	if (shm_unlink(name) == -1) {
		printf("Error removing %s\n",name);
		exit(-1);
	}

	return 0;
}

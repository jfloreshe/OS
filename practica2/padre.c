/**
 * @author Jefferson Flores Herrera 
			Vanessa Mayra Macedo Huaman
 */

#include <stdio.h>   
#include <signal.h>  
#include <stdlib.h>  
#include <unistd.h>  
#include <sys/wait.h>   


int main(){	
	//Creacion de un hijo para ejecutar hijo.c desde padre.c
	pid_t pid = fork(); 
	if(pid < 0){
		//Manda error si no se pudo crear el hijo desde padre.c
		perror("ERROR; no se pudo crear al hijo desde padre.c\n");	
		exit(EXIT_FAILURE);
	}else if(pid == 0){
		//llamamos al sistema para que ejecute nuestro hijo.c nótese que los 
		//programas ya han sido previamente compilados con el make
		execlp("./hijo","hijo",(char*)NULL);
		//Solo ejecuta el error si no pudo encontrar el archivo hijo
		perror("ERROR: hijo.c no se ha ejecutado\n");
		exit(EXIT_FAILURE);
	}else{
		/*Creamos la variable waitStatus para poder tener conocimiento
		 del estado de hijo.c, porque deseamos que hijo.c termine su
		 ejecución correctamente ya que es un requisito que no termine
		 padre.c antes que hijo.c
		*/		
		int waitStatus;
		waitpid(-1, &waitStatus, 0);
		//Como se mencionó anteriormente necesitamos saber si hijo.c
		//ha terminado correctamente para esto usamos WIFEXITED 
		//que nos retorna true si ha pasado lo mencionado anteriormente
		if(WIFEXITED(waitStatus)){
			exit(EXIT_SUCCESS);
		}
	}
	
	return 0;
}

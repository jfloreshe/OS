/**
 * @author Jefferson Flores Herrera 
			Vanessa Mayra Macedo Huaman
 */

#include <stdio.h>   
#include <signal.h>  
#include <stdlib.h>  
#include <unistd.h>  
#include <sys/wait.h> 
#include <string.h>

//Definimos las señales que recibiremos, SIGKILL y SIGSTOP no se pueden redefinir en un handler
//es por eso que usamos solo 12 señales
#define TOTAL_SIGNALS 12
int signalsToReceive[TOTAL_SIGNALS] = {SIGHUP, SIGINT, SIGQUIT, SIGILL, SIGABRT, SIGFPE, SIGSEGV, SIGPIPE,
				 SIGALRM, SIGTERM, SIGCHLD, SIGTSTP};

void handler(int , siginfo_t *, void *); //Manejará como se comportará cada señal
void installSignalsCatcher(struct sigaction *);//Esta función instalará todas las señales que hemos redefinido las cuales se 
												//encuentran en nuestro array signalsToReceive

int main(){	

	struct sigaction act;
	memset(&act,0,sizeof(act));
	act.sa_sigaction = &handler;
	act.sa_flags = SA_SIGINFO;
	installSignalsCatcher(&act);
	//La lógica detrás de esto es que se auto pare, de esta manera hijo.c puede capturar que ha parado en el waitpid
	//y seguir la lógica explicada en hijo.c, una vez que se le haga un continue sigue ejecutando ya que estamos en un bucle infinito.
	while(1){
		kill(getpid(),SIGSTOP);
	}
	return 0;
}

void handler(int sig, siginfo_t *siginfo, void *context){
	//Lo principal de este handler es que para todos muestra la señal recibida, el codigo de la señal si tubiese alguno como en SIGCHLD
	//para saber si ha parado o ha sido asesinado, si_errno nos mostrara el codigo de un error, si es que ha ocurrido uno, si_pid 
	//nos mostrara el pid del proceso que ha enviado la señal.
	//La lógica tras el exit de SIGTSTP es que ya debe haber terminado de enviar todas las señales
	//recordar que si una señal no era enviada se volvia a enviar hasta que esta halla sido enviada correctamente
	//entonces siguiendo esta lógica una vez halla llegado a SIGTSTP hijo.c debe haber enviado todas las señales a nieto.c
	
	printf("Signal number: %d Signal code: %d errno value: %d Sending process ID: %d\n",
			siginfo -> si_signo,
			siginfo -> si_code,
			siginfo -> si_errno,
			siginfo -> si_pid);		
	switch(sig){
		case SIGHUP:
			break;
		case SIGINT:
			break;
		case SIGQUIT:
			break;
		case SIGILL:
			break;
		case SIGABRT:
			break;
		case SIGFPE:
			break;
		case SIGSEGV:
			break;
		case SIGPIPE:
			break;
		case SIGALRM:
			break;
		case SIGTERM:
			break;
		case SIGCHLD:
			break;
		case SIGTSTP:
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

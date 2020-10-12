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
#include <setjmp.h>

//TOTAL_SIGNALS es la cantidad de señales que deseamos enviar
#define TOTAL_SIGNALS 14
//Creamos un jmp_buf para usarlo cuando nuestr proceso nieto.c ha sido matado
jmp_buf env;
//La variable i nos ayudara como un auxiliar para saber en que señal estamos
int i = 0;

//la declaracion de estos prototipos se encuentran en la última parte del file
void sendSignals(int);
void handlerSIGCHLD(int, siginfo_t *, void *);

//Señales que enviaremos
int signalsToSend[TOTAL_SIGNALS] = {SIGHUP, SIGINT, SIGQUIT, SIGILL, SIGABRT, SIGFPE, SIGKILL, SIGSEGV, SIGPIPE,
				 SIGALRM, SIGTERM, SIGCHLD, SIGSTOP, SIGTSTP};

int main(){
	//Creamos este sigaction para poder manejar la señal SIGCHILD que nos permite
	//realizar acciones dependiendo de algún evento en uno de nuestros hijos
	struct sigaction act;
	memset(&act, 0, sizeof(act));
	act.sa_sigaction = &handlerSIGCHLD;
	act.sa_flags = SA_SIGINFO;
	//Inicializamos el catcher de señal para nuestro SIGCHILD
	sigaction(SIGCHLD, &act, NULL);
	int status;

	//CHECKPOINT usado en caso que nieto.c sea matado
	setjmp(env);

	pid_t w,pid = fork();
	if(pid < 0){
		perror("ERROR; no se pudo crear al nieto desde hijo.c\n");	
		exit(EXIT_FAILURE);
	}else if(pid == 0){
		/*En el proceso hijo de hijo.c haremos que se ejecute nieto.c
		*/
		printf("creating nieto\n");
		execlp("./nieto","nieto",(char*)NULL);
		perror("ERROR: nieto.c no se ha ejecutado\n");
		exit(EXIT_FAILURE);
	}else{
		//Como necesitamos que nuestro programa termine siempre y cuando 
		//todas las señales soportadas sean enviadas haremos uso de un bucle
		//Este bucle terminara cuando nuestro proceso nieto.c halla 
		//salido con un exit o un return WIFEXITED retorna true si el proceso ha terminado
		//con un exit o un  return
		do{
			//Esperamos que nuestro hijo especifico le hallan mandado una señal de parar o continuar
			//o halla terminado
			w = waitpid(pid, &status, WUNTRACED | WCONTINUED);
			//w será -1 cuando pid no exista
			if(w == -1){
				continue;
				exit(EXIT_FAILURE);
			}
			//Si el proceso ha sido parado empezamos a enviar señales
			//WIFSTOPPED solo puede ser usado si WUNTRACED ha sido especificado
			else{
				if(WIFSTOPPED(status)){
					sendSignals(pid);
				}
			}
		}while(!WIFEXITED(status));
	}
	
	return 0;
}

void sendSignals(int pidReceiver){
	//Esta función enviará las señales como se mencionó anteriormente i guarda en la
	//señal que nos encontramos en nuestro array de señales a enviar
	//Siempre enviamos una señal de continuar ya que estamos usando señal de parar
	//en nuestra lógica para poder enviar señales al proceso nieto.c
	kill(pidReceiver,SIGCONT);
	//Una vez que se envía la señal de continuar nieto.c puede procesar esta 
	//es ahi que enviamos la nueva señal dependiendo donde se encuentre en nuestro array 
	int signalSentStatus = kill(pidReceiver,signalsToSend[i]);
	//como SIGKILL no se puede modificar aumentamos el i para poder usar la siguiente señal
	//una vez el proceso halla sido matado, si no aumentamos este i seguira matando a los
	//siguiente nietos creados
	if(signalsToSend[i] == SIGKILL)
		i++;
	//Con signalSentStatus sabemos si la señal ha sido enviado al pid que deseabamos
	//kill retorna 0 si es asi, -1 si no ha enviado ninguna señal
	if(signalSentStatus == 0)//succes
		i++;
	
}

//Esta función nos permite manejar el catcher de la señal SIGCHLD
//En nuestra lógica estamos usando este catcher para cuando muera nuestro nieto.c
//poder regresar a un checkpoint previamente mencionado y volver a crear un nuevo hijo
void handlerSIGCHLD(int sig, siginfo_t *siginfo, void *context){
	if(sig == SIGCHLD){
		//si_code nos permite saber distintas cosas que han pasado con nuestros hijos
		//en este caso CLD_KILLED nos informa si un hijo ha sido matado por una señal
		//nótese que asesinado es distinto que el proceso termine con exit o return
		if(siginfo -> si_code == CLD_KILLED){
			printf("Mi hijo ha sido asesinado crare uno nuevo y seguire enviando senales\n");
			//REgresamos al checkpoint 
			longjmp(env,100);
		}
	}
}

#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <signal.h> 
#include <string.h>
#include <setjmp.h> // for long jump

jmp_buf env; // for saving longjmp environment
int count = 0;

void handler(int sig, siginfo_t *siginfo, void *context)
{
    printf("handler: sig=%d from PID=%d UID=%d count=%d\n",
           sig, siginfo->si_pid, siginfo->si_uid, ++count);
    if (count >= 4) // let it occur up to 4 times
        longjmp(env, 1234);
}

void BAD()
{
    int *ip = 0;
    printf("in BAD(): try to dereference NULL pointer\n");
    *ip = 123; // dereference a NULL pointer
    printf("should not see this line\n");
}

int main(int argc, char *argv[])
{
    int r;
    struct sigaction act;
    memset(&act, 0, sizeof(act));
    act.sa_sigaction = &handler;
    act.sa_flags = SA_SIGINFO;
    sigaction(SIGSEGV, &act, NULL); // install SIGSEGV catcher 
    
    if ((r = setjmp(env)) == 0) // call setjmp(env)
        BAD();                          // call BAD()
    else 
        printf("proc %d survived SEGMENTATION FAULT: r=%d\n", getpid(), r);
    
    printf("proc %d looping\n", getpid());
    while (1)
        ;
    
    return 0;
}

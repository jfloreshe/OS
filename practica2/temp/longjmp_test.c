#include <stdio.h>
#include <setjmp.h>
jmp_buf env; // for saving longjmp environment

void A();
void B();
void C();
void D();

int main()
{
    int r, a = 100;
    printf("call setjmp to save environment\n");
    if ((r = setjmp(env)) == 0)
    {
        A();
        printf("normal return\n");
    }
    else{
        printf("back to main() via long jump, r=%d a=%d\n", r, a);
    }
}

void A()
{
    printf("enter A()\n");
    B();
    printf("exit A()\n");
}

void B()
{
    printf("enter B()\n");
    C();
    printf("exit B()\n");
}

void C()
{
    printf("enter C()\n");
    D();
    printf("exit C()\n");
}

void D()
{
    printf("enter D()\n");
    printf("long jump? (y|n) ");
    if (getchar() =='y')
        longjmp(env, 111);
    printf("exit D()\n");
}

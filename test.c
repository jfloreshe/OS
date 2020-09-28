#include <stdio.h>
#include <time.h>

int main(){
	time_t t = time(0);
	tm* struct now = localtime(&t);
	printf("%d",now->tm_mday);
}

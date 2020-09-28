#include <stdio.h>
#include <time.h>
#include <sys/time.h>

int main(){
	struct timeval current_time;
	time_t t;
	int milisecs;
	struct tm *info;
	gettimeofday(&current_time, NULL);
	t = current_time.tv_sec;
	info = localtime(&t);
	milisecs = current_time.tv_usec / 1000;
	printf("%d::%d::%d.%d", info->tm_hour, info->tm_min, info->tm_sec, milisecs);
	return 0;
}

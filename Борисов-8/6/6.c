#define _POSIX_C_SOURCE 199309L
#include <time.h>
#include <sys/times.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
int counter = 0;
struct timespec start, finish, proc;
clock_gettime(CLOCK_REALTIME, &start);
while (1)
{
counter++;
clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &proc);
if (proc.tv_sec == 2)
break;
}
clock_gettime(CLOCK_REALTIME, &finish);
printf("Value of Counter after 2 sec: %d\n", counter);
printf("Loop REALTIME: %ldsec %ldnsec\n", finish.tv_sec - start.tv_sec,
finish.tv_nsec - start.tv_nsec);
exit(0);
}

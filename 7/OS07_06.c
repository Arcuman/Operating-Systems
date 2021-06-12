#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mx;

void* A(void* arg)
{
	pid_t pid = getpid();
	for(int i = 0; i < 90; i++)
	{
		if (i == 29 || i == 60) pthread_mutex_lock(&mx);
		if (i == 59 || i == 61) pthread_mutex_unlock(&mx);
		usleep(100000);
		printf("%d A %d\n", pid, i);
	}
	pthread_exit("A thread");
}

void* B(void* arg)
{
	pid_t pid = getpid();
	for(int i = 0; i < 90; i++)
	{
		if (i == 30 || i == 60) pthread_mutex_lock(&mx);
		if (i == 59 || i == 61) pthread_mutex_unlock(&mx);
		usleep(100000);
		printf("%d B %d\n", pid, i);
	}
	pthread_exit("A thread");
}

int main()
{
	pthread_mutex_init(&mx, NULL);
	pthread_t th1, th2;
	void *r_th1, *r_th2;
	pid_t pid = getpid();
	
	int res1 = pthread_create(&th1, NULL, A, NULL);
	int res2 = pthread_create(&th2, NULL, B, NULL);
	
	for(int i = 0; i < 90; i++)
	{
		if (i == 31 || i == 61) pthread_mutex_lock(&mx);
		if (i == 59) pthread_mutex_unlock(&mx);
		usleep(100000);
		printf("%d main %d\n", pid, i);
	}
	
	int status1 = pthread_join(th1, (void**)&r_th1);
	int status2 = pthread_join(th2, (void**)&r_th2);
	pthread_mutex_destroy(&mx);
	exit(0);
}

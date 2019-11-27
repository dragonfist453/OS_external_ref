#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#define size 4
sem_t empty, full,mutex;
int buf[size];
int i=0;
void* producer()
{
	int food;
	while(1)
	{
		sem_wait(&full);
		sem_wait(&mutex);
		sleep(1);
		srandom(random());
		food = random()%100;
		sem_getvalue(&empty,&i);
		buf[i]=food;
		printf("%d was produced\n",food);
		sem_post(&mutex);	
		sem_post(&empty);	
	}
	pthread_exit(0);
}
void* consumer()
{
	int food;
	while(1)
	{
		sem_wait(&empty);
		sem_wait(&mutex);
		sleep(2);
		sem_getvalue(&empty,&i);
		food = buf[i];
		printf("%d was consumed\n",food);
		sem_post(&mutex);
		sem_post(&full);
	}
	pthread_exit(0);
}
int main(int argc, char *argv[])
{
	sem_init(&empty,0,0);
	sem_init(&mutex,0,1);
	sem_init(&full,0,size-1);
	if(argc!=3)
	{
		fprintf(stderr,"Usage: %s <number of producers> <number of consumers>\n",argv[0]);
		return 0;
	}
	int i;	
	pthread_t prod[atoi(argv[1])],cons[atoi(argv[2])];	
	for(i=0;i<atoi(argv[1]);i++)
		pthread_create(&prod[i],NULL,&producer,NULL);
	for(i=0;i<atoi(argv[2]);i++)	
		pthread_create(&cons[i],NULL,&consumer,NULL);
	for(i=0;i<atoi(argv[1]);i++)
		pthread_join(prod[i],NULL);
	for(i=0;i<atoi(argv[2]);i++)		
		pthread_join(cons[i],NULL);
	return 0;
}	 			

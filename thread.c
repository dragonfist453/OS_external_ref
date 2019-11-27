#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
long unsigned int prod = 1;
void* odd_multiplier(void *param)
{
	int n = atoi(param);
	int i;
	for(i=1;i<=n;i+=2)
		prod*=i;
	pthread_exit(0);	
}	
void* even_multiplier(void *param)
{
	int n = atoi(param);
	int i;
	for(i=2;i<=n;i+=2)
		prod*=i;
	pthread_exit(0);	
}
int main(int argc, char *argv[])
{
	pthread_t odd,even;
	if(argc!=2)
	{
		fprintf(stderr, "Usage: %s <number of which factorial is to be found>\n",argv[0]);
		return 0;
	}
	if(atoi(argv[1])<0)
	{
		fprintf(stderr, "Usage: %s <positive number>\n",argv[0]);
		return 0;
	}
	pthread_create(&odd,NULL,odd_multiplier,argv[1]);
	pthread_create(&even,NULL,even_multiplier,argv[1]);
	pthread_join(odd,NULL);
	pthread_join(even,NULL);
	printf("Factorial of %d is %ld\n",atoi(argv[1]),prod);
	return 0;
}			

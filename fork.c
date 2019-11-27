#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(int argc, char *argv[])
{
	pid_t pid = fork();
	if(pid == 0)
	{
		printf("PID of child = %d\n\n",getpid());
		execlp("./prog1","prog1",argv[1],NULL);
	}
	else
	{
		wait(0);
		printf("PID of parent = %d\n\n",getpid());
		execlp("./prog2","prog2",argv[2],argv[3],NULL);
	}
	return 0;
}			

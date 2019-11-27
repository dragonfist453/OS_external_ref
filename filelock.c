#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main( int argc , char * argv[])
{
	int fd1;
	struct flock fvar;
	fvar.l_type = F_WRLCK;
	fvar.l_whence = SEEK_SET;
	fvar.l_start = 0;
	fvar.l_len = 100;
	fd1 = open( argv[1], O_WRONLY);
	if( fd1 == -1 )
	{
		perror("\nError in opening\n");
		exit(0);
	}
	if( fcntl(fd1, F_SETLK , &fvar )==0)
	{
		printf("\nLocking done \n");
		sleep(1);
	}
	else
	{
		fcntl( fd1, F_GETLK , &fvar );
		printf("ID of the locking process is : %d \n",fvar.l_pid);
		return -1;
	}
	printf("Press enter to unlock \n");
	getchar();
	fvar.l_type = F_UNLCK;
	fvar.l_whence = SEEK_SET;
	fvar.l_start = 0;
	fvar.l_len = 100;
	if( fcntl(fd1, F_UNLCK , &fvar )==-1)
	{
		printf("\nError in unlock \n");
		exit(0);
	}
	printf("Unlocking ...\n");
	close(fd1);
	return 0;	
}

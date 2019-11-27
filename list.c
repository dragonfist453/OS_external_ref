#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>
int main(int argc, char *argv[1])
{
	char str[50],buf[512];
	DIR *d;
	char permissions[3] = "rwx";
	if(argc==1)
	{
		d = opendir("./");
		sprintf(str,"./");
	}
	else if(argc>2)
	{
		fprintf(stderr, "Usage: %s <dir>\n",argv[0]);
		return 0;
	}
	else 
	{
		d = opendir(argv[1]);
		sprintf(str,"%s",argv[1]);
	}
	struct stat stats;
	struct dirent *file;
	while((file=readdir(d))!=NULL)
	{
		
		if(strcmp(file->d_name,".") == 0 || strcmp(file->d_name,"..") == 0)
			continue;
		sprintf(buf,"%s%s",str,file->d_name);
		stat(buf,&stats);
		switch(stats.st_mode & S_IFMT)
		{
			case S_IFDIR: printf("d"); break;
			case S_IFBLK: printf("b"); break;
			case S_IFCHR: printf("c"); break;
			default: printf("-"); break;
		}
		int i;
		for(i=8;i>=0;i--)
		{
			printf("%c",((1<<i) & stats.st_mode)?permissions[(8-i)%3]:'-');	
		}
		printf("%2ld %s %s ",stats.st_nlink,getpwuid(stats.st_uid)->pw_name,getgrgid(stats.st_gid)->gr_name);
		printf("%5ld ",stats.st_size);
		char *time = ctime(&stats.st_atime);
		char *a_time = malloc(sizeof(char));
		for(i=4;i<(strlen(time)-5);i++)
		{
			*a_time = time[i];
			printf("%c",*a_time);
			a_time++;
		}		
		printf(" %s\n",file->d_name);
	}
	return 0;
}			

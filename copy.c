#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if(argc!=3)
    {
        fprintf(stderr, "Usage: ./copy <file1> <file2>\n");
        return 0;
    }
    int fd1 = open(argv[1],O_RDONLY);
    int fd2 = open(argv[2],O_WRONLY);
    char buf[100];  
    while(read(fd1,buf,100)!=0)
    {
        write(fd2,buf,strlen(buf));
    }
    close(fd1);
    close(fd2);    
    return 0;
}    

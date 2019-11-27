#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
    if(argc!=2)
    {
        fprintf(stderr, "Usage: ./remove <filename>\n");
        return 0;
    }
    unlink(argv[1]);
    return 0;        
}

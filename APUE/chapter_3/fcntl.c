#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc,char *argv[])
{
    int accmode,val;
    if(argc != 2)
    {
        printf("usage: ./a.out <descriptor#>\n");
        return 0;
    }
/*
    int fd = open(argv[1], O_RDONLY);
    if( (val = fcntl(fd, F_GETFL, 0)) < 0)
        printf("fcntl error for fd %s\n", argv[1]);
*/
  if( (val = fcntl(atoi(argv[1]), F_GETFL, 0)) < 0)
      printf("fcntl error for fd %d\n", atoi(argv[1]));
    accmode = val & O_ACCMODE;
    if(accmode == O_RDONLY) printf("read only\n");
    else if(accmode == O_WRONLY) printf("write only\n");
    else if(accmode == O_RDWR) printf("read write\n");
    else printf("unknown access mode\n");

    if(val & O_APPEND) printf(",append");
    if(val & O_NONBLOCK) printf(",nonblocking");
    #if !defined(_POSIX_SOURCE) && defined(O_SYNC)
    if(val & O_SYNC) printf(",synchronous writes");
    #endif
    putchar('\n');
    return 0;
}

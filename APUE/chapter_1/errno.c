#include <stdio.h>
#include <string.h>
#include <errno.h>

// extern int errno;

int main(int args, char *argv[])
{
	fprintf( stderr, "EACCES:%s\n", strerror(EACCES) );	//char * strerror(int num)
	errno = ENOENT;
	perror( argv[0] );	// void perror(const char msf)
	return 0;		// argv[0] == a.out
}

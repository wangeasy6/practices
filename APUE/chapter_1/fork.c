#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define MAXLINE 128

int main(int args, char * argv)
{
	char buf[MAXLINE];
	pid_t pid;
	int status;

	printf("This program like a shell ,input a execute file name,then Load them. Use exit to break\n");
	printf("Current Work Directory:%s\n%%", getcwd( buf, sizeof(buf) ) );
	while( fgets( buf, MAXLINE, stdin ) != NULL)
	{
		if ( NULL != strstr( buf, "exit") )
			break;
		buf[strlen(buf) -1] = 0;
		if ( (pid = fork()) < 0 )
			printf("fork error\n");
		else if ( pid == 0)				// child process
		{
			execlp( buf, buf, (char *) 0 );
			perror("couldn't execute");
			exit(127);
		}
		
		/* parent */
		if ( ( pid == waitpid( pid, &status, 0 )) < 0)
			perror("waitpid error");
		else
			printf("process go over,exit %d", status);
		printf("\n%%");
	}
	return 0;
}

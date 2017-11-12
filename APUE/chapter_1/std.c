#include <stdio.h>
#include <unistd.h>
#define BUFFSIZE 8192

int main(int args, char *argv)
{
	int n ;
	char buf[BUFFSIZE];

	if( args < 2)
	{
		printf("Function:流从 标准输入 到 标准输出,可使用 \">\"、\"<\" 重定向输入输出\n");
	}
	while( ( n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0)
		if( write (STDOUT_FILENO, buf, n) != n)
			printf("write error\n");
	if( n < 0 )
		printf("read error\n");
	return 0;
}

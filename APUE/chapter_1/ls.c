/*
*	程序功能：用于列出目录中的所有文件
*		输入：可用路径
*		输出：路径下的所有文件
*/
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>

int main(int argc,char *argv[])
{
	DIR *dp;
	struct dirent *dirp;
	if ( argc != 2)
	{
		printf("need one argument (the directory name)\r\n");
		return 0;
	}
	if ( (dp = opendir(argv[1])) == NULL)
	{
		printf("cat't open %s",argv[1]);
		return 0;
	}
	while( ( dirp = readdir(dp) ) != NULL)
	{
		printf("%s ",dirp->d_name);
	}
	printf("\r\n");
	closedir(dp);
	return 0;
}

/*
* @func umask，用于设置文件权限掩码，配合 open、mkdir、creat 等函数使用
* @explain  默认umask值为：S_IWGRP | S_IWOTH
*/
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>

int main()
{
      umask(0);
      if (creat("foo1", S_IRUSR| S_IWUSR| S_IRGRP| S_IWGRP| S_IROTH| S_IWOTH) < 0)
            printf("creat error for foo\n");
      umask(S_IRGRP| S_IWGRP| S_IROTH| S_IWOTH);
      if(creat("foo2",S_IRUSR| S_IWUSR| S_IRGRP| S_IWGRP| S_IROTH| S_IWOTH) < 0)
            printf("creat error bar\n");
      return 0;
}

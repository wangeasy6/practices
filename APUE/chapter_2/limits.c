#include <stdio.h>
#include <limits.h>

int main()
{
  /********************* 表2.2 <limits.h>中的整型值大小 ********************/
    printf("\n%s\n", "表2.2 <limits.h>中的整型值大小");
    printf("char的位,CHAR_BIT, %d\n", CHAR_BIT);
    printf("char的最大值,CHAR_MAX, %d\n", CHAR_MAX);
    printf("char的最小值,CHAR_MIN, %d\n", CHAR_MIN);
    printf("带符号char的最大值,SCHAR_MAX, %d\n", SCHAR_MAX);
    printf("带符号char的最小值,SCHAR_MIN, %d\n", SCHAR_MIN);
    printf("不带符号char的最大值,UCHAR_MAX, %d\n", UCHAR_MAX);
    printf("int最小值,INT_MIN, %d\n", INT_MIN);
    printf("int最大值,INT_MAX, %d\n", INT_MAX);
    printf("不带符号的int的最大值,UINT_MAX, %d\n", UINT_MAX);
    printf("short最小值,SHRT_MIN, %d\n", SHRT_MIN);
    printf("short最大值SHRT_MAX, %d\n", SHRT_MAX);
    printf("不带符号的short的最大值,USHRT_MAX, %d\n", USHRT_MAX);
    printf("long最小值,LONG_MIN, %ld\n", LONG_MIN);
    printf("long最大值,LONG_MAX, %ld\n", LONG_MAX);
    printf("不带符号的long的最大值,ULONG_MAX, %lu\n", ULONG_MAX);
    printf("一多字节字符常数中的最大字节数,MB_LEN_MAX, %d\n", MB_LEN_MAX);

  /********************* 表2.3 <limits.h>中的POSIX.1不变最小值********************/
    printf("\n%s\n", "表2.3 <limits.h>中的POSIX.1不变最小值");
    printf("exec函数的参数长度,_POSIX_ARG_MAX, %d\n", _POSIX_ARG_MAX);
    printf("每个实际用户ID的子进程数,_POSIX_CHILD_MAX, %d\n", _POSIX_CHILD_MAX);
    printf("至一个文件的连接数,_POSIX_LINK_MAX, %d\n", _POSIX_LINK_MAX);
    printf("终端规范输入队列的字节数,_POSIX_MAX_CANON, %d\n", _POSIX_MAX_CANON);
    printf("终端输入队列的可用空间,_POSIX_MAX_INPUT, %d\n", _POSIX_MAX_INPUT);
    printf("文件名中的字节数,_POSIX_NAME_MAX, %d\n", _POSIX_NAME_MAX);
    printf("每个进程同时的添加组ID数,_POSIX_NGROUPS_MAX, %d\n", _POSIX_NGROUPS_MAX);
    printf("每个进程的打开文件数,_POSIX_OPEN_MAX, %d\n", _POSIX_OPEN_MAX);
    printf("路径名中的字节数,_POSIX_PATH_MAX, %d\n", _POSIX_PATH_MAX);
    printf("能原子地写到一管道的字节数,_POSIX_PIPE_BUF, %d\n", _POSIX_PIPE_BUF);
    printf("能存在ssize_t对象中的值,_POSIX_SSIZE_MAX, %d\n", _POSIX_SSIZE_MAX);
    printf("一个进程能一次打开的标准I/O流数,_POSIX_STREAM_MAX, %d\n", _POSIX_STREAM_MAX);
    printf("时区名字节数,_POSIX_TZNAME_MAX, %d\n", _POSIX_TZNAME_MAX);

    return 0;
}

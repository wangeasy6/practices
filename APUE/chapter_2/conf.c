#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("exec函数的参数最大长度, %ld\n", sysconf(_SC_ARG_MAX));
    printf("每个实际用户ID的最大进程数, %ld\n", sysconf(_SC_CHILD_MAX));
    printf("每秒时钟滴答数, %ld\n", sysconf(_SC_CLK_TCK));
    printf("每个进程的最大同时添加组ID数, %ld\n", sysconf(_SC_NGROUPS_MAX));
    printf("每个进程最大打开文件数, %ld\n", sysconf(_SC_OPEN_MAX));
    printf("口令中的最大有效字符数, %ld\n", sysconf(_SC_PASS_MAX));
    printf("在任一时刻每个进程的最大标准I/O流数, %ld\n", sysconf(_SC_STREAM_MAX));
    printf("时区名中的最大字节数, %ld\n", sysconf(_SC_TZNAME_MAX));
    printf("指明实现是否支持作业控制, %ld\n", sysconf(_SC_JOB_CONTROL));
    printf("指明实现是否支持保存的设置-用户-ID和保存的设置-组-ID, %ld\n", sysconf(_SC_SAVED_IDS));
    printf("指明POSIX.1版本, %ld\n", sysconf(_SC_VERSION));
    printf("指明XPG版本（非POSIX.1）, %ld\n", sysconf(_SC_XOPEN_VERSION));
    return 0;
}

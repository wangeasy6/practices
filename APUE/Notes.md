# APUE笔记

### Notes
* 查看最大进程数 cat /proc/sys/kernel/pid_max 此值可修改
* 不带缓冲cp（read，write），是IO效率最高的取值：_G_BUFSIZ（struct stat.st_blksize） = 8192（实际代表了块长）
* od -c 以字符方式打印文件内容

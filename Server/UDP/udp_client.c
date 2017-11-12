#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <strings.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include <pwd.h>

#ifndef BUF_SIZE
#define BUF_SIZE 128
#endif

int split_buf(char filename[16][128],char *buf,int nchar);
int get_file(int sockfd,char *buf);
char *get_uname();

int main(int argc,char **argv)
{
    int port = 9999;
    int sockfd;
    char buf[BUF_SIZE] = "0";
    struct sockaddr_in servaddr;
    if(argc != 2) 										//判断传入值
    {
        printf("Usage : %s <ip>\n",argv[0]);			//使用提示
        exit(-1);
    }

    if(((sockfd = socket(AF_INET,SOCK_DGRAM,0)) == -1)) 		//创建socket
    {
        perror("socket");
        exit(-1);
    }

    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);		//将16位主机字符顺序转化成网络字符顺序
    servaddr.sin_addr.s_addr = inet_addr(argv[1]);

    printf("there\n");
    while(1)
    {

        printf("send message:");
        fflush(stdout);
        fgets(buf,BUF_SIZE,stdin);
        //收发数据，由于处理文件名在本地
        if(!strncmp(buf,"get",3))
        {
            get_file(sockfd,buf);
            continue;
        }
        // if(!strncmp(buf,"post",4)){
        //post_file(connfd,buf);
        // continue;
        // }

        if(-1 == sendto(sockfd,buf,sizeof(buf),0,(struct sockaddr *)&servaddr,sizeof(servaddr)))
        {
            perror("fail to send");
            exit(-1);
        }

        //quit功能,在quit之前发送给服务器关闭服务器
        if(!strcmp(buf,"quit\n"))
            break;

        bzero(buf,sizeof(buf));
        if(recvfrom(sockfd,buf,sizeof(buf),0,NULL,NULL) == -1)
        {
            perror("recvfrom");
            exit(-1);
        }
        if(!strcmp(buf,"quit\n"))
            break;
        printf("recevied a message from %s: %s \n",get_uname(),buf);
    }

    close(sockfd);
    exit(0);
}
char *get_uname()
{
    struct passwd *uname = getpwuid(getuid());
    return uname->pw_name;
}

int split_buf(char filename[16][128],char *buf,int nchar)
{
    char *p = buf;
    int n,j;

    for(n = -1,j = 0; *(p+nchar) != '\n'; p++)
    {
        if(n==16)
        {
            printf("超过16个文件名之后的文件默认处理为缺省\n");
            break;
        }
        if(*(p+nchar) == ' ' && *(p+nchar+1) != ' ')
        {
            n++;
            j=0;
            continue;
        }
        filename[n][j] = *(p+nchar);
        j++;
    }

    return 0;
}

int get_file(int sockfd,char *buf)
{
    char filename[16][128] = {0};
    split_buf(filename,buf,3);			//"get"是3字节，所以后面的参数为3
    int n = 0;
    char namebuf[128] = {0};
    while(strlen(filename[n]))
    {
        bzero(namebuf,sizeof(namebuf));
        strcat(namebuf,"get ");
        strcat(namebuf,filename[n]);
        if(-1 == send(sockfd,namebuf,sizeof(namebuf),0))
        {
            perror("fail to send");
            return -1;
        }
        n++;
    }
    // char buf[128] = {0};
    // if(recv(sockfd,buf,sizeof(buf),0) == -1)
    // {
    // perror("recv");
    // exit(-1);
    // }
    // *FILE fd = open(filename,"w");
    return 0;
}
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

#define BUF_SIZE 1024

int main(int argc,char **argv)
{
    if(argc < 3)                   //判断传入值
    {
        printf("Usage : %s <ip> <port>\n",argv[0]); //使用提示
        exit(-1);
    }
    
    int port = atoi(argv[2]);
    int sockfd;
    char buf[BUF_SIZE] = "0";
    struct sockaddr_in servaddr;

    if((sockfd = socket(AF_INET,SOCK_DGRAM,0)) == -1)     //创建socket
    {
        perror("socket");
        exit(-1);
    }

    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    servaddr.sin_addr.s_addr = inet_addr(argv[1]);

    while(1)
    {

        printf("send a message:");
        fflush(stdout);
        bzero(buf,sizeof(buf));
        fgets(buf,BUF_SIZE,stdin);
        
        if(-1 == sendto(sockfd,buf,sizeof(buf),0,(struct sockaddr *)&servaddr,sizeof(servaddr)))
        {
            perror("send failed");
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
        printf("recv a message:%s\n",buf);
        if(!strcmp(buf,"quit\n"))
            break;
    }

    close(sockfd);
    exit(0);
}
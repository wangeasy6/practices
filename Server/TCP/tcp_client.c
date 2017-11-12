#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <strings.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>

#define BUF_SIZE 128

void main(int argc,char **argv)
{
    int sockfd;
    char buf[BUF_SIZE] = "0";
    struct sockaddr_in servaddr;

    if(argc != 3)
    {
        printf("Usage : %s <ip> <port>",argv[0]);
        exit(-1);
    }

    if((sockfd = socket(AF_INET,SOCK_STREAM,0)) == -1)
    {
        perror("socket");
        exit(-1);
    }

    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(atoi(argv[2]));        //将16位主机字符顺序转化成网络字符顺序
    servaddr.sin_addr.s_addr = inet_addr(argv[1]);

    if(connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr)) == -1)
    {
        perror("connect");
        exit(-1);
    }

    while(1)
    {
        printf("send message to:");
        fflush(stdout);
        fgets(buf,BUF_SIZE,stdin);

        if(!strncmp(buf,"quit",4))
            break;

        if(-1 == send(sockfd,buf,sizeof(buf),0))
        {
            perror("fail to send");
            exit(-1);
        }

        bzero(buf,sizeof(buf));
        if(recv(sockfd,buf,sizeof(buf),0) == -1)
        {
            perror("recv");
            exit(-1);
        }
        printf("recv from server : %s \n",buf);
    }

    close(sockfd);
    exit(0);
}
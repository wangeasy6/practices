#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <strings.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/un.h>

#define BUF_SIZE 128

void main(int argc,char **argv)
{
    int listenfd,connfd;
    struct sockaddr_in servaddr,cliaddr;
    socklen_t peerlen;
    char buf[BUF_SIZE];

    if(argc != 3)
    {
        printf("Usage : %s <ip> <port>",argv[0]);
        exit(-1);
    }

    if((listenfd = socket(AF_INET,SOCK_STREAM,0)) == -1)
    {
        perror("socket");
        exit(-1);
    }

    printf("listenfd = %d\n",listenfd);

    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(atoi(argv[2]));        //将16位主机字符顺序转化成网络字符顺序
    servaddr.sin_addr.s_addr = inet_addr(argv[1]);

    // printf("%d\n%d\n%d\n",servaddr.sin_family,servaddr.sin_port,servaddr.sin_addr.s_addr);

    if((bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr)))<0)
    {
        perror("bind");
        exit(-1);
    }

    printf("bind seccess!\n");

    if(listen(listenfd,10) == -1)
    {
        perror("listen");
        exit(-1);
    }
    printf("listening....\n");

    peerlen = sizeof(cliaddr);
    if((connfd = accept(listenfd,(struct sockaddr *)&cliaddr,&peerlen))<0)
    {
        perror("accept");
        exit(-1);
    }
    while(1)
    {
        memset(buf,0,sizeof(buf));
        if(recv(connfd,buf,BUF_SIZE,0)==-1)
        {
            perror("recv");
            exit(-1);
        }

        if(!strncmp(buf,"quit",4))
            break;

        printf("received a message :%s",buf);
        strcpy(buf,"copy that");
        send(connfd,buf,sizeof(buf),0);
    }
    close(listenfd);
    exit(0);
}
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
#include <pwd.h>

#define BUF_SIZE 1024
char *get_ip();

int main(int argc,char **argv)
{
    if(argc < 2)
    {
        printf("Usage : %s <port>\n",argv[0]);
        exit(-1);
    }

    int port = atoi(argv[1]);
    int sockfd;
    struct sockaddr_in servaddr,cliaddr;
    socklen_t peerlen;
    char buf[BUF_SIZE] = {0};

    if(((sockfd = socket(AF_INET,SOCK_DGRAM,0)) == -1))
    {
        perror("socket");
        exit(-1);
    }
    printf("sockfd = %d\n",sockfd);

    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    servaddr.sin_addr.s_addr = INADDR_ANY; //inet_addr(get_ip());
    //printf("IP: %s\n",get_ip());
    
    while((bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr)))<0)
    {
        port--;
        servaddr.sin_port = htons(port);
        if(port == 9899)
        {
	        perror("bind");
	        exit(-1);
        }
    }
    printf("bind %d\n",port);

    peerlen = sizeof(cliaddr);

    //无listen
    //无accept

    //会话
    while(1)
    {
        memset(buf,0,sizeof(buf));
        //接收信息
        if(recvfrom(sockfd,buf,BUF_SIZE,0,(struct sockaddr *)&cliaddr,&peerlen)==-1)
        {
            perror("recvfrom");
            exit(-1);
        }
        //判断进入server功能
        if(!strcmp(buf,"quit\n"))
            break;

        printf("recv a message :%s",buf);

        //发送信息
        memset(buf,0,sizeof(buf));
        printf("send a message:");
        fgets(buf,BUF_SIZE,stdin);
        putchar('\n');
        sendto(sockfd,buf,sizeof(buf),0,(struct sockaddr *)&cliaddr,peerlen);
        
        if(!strcmp(buf,"quit\n"))
            break;
    }

    close(sockfd);
    exit(0);
}

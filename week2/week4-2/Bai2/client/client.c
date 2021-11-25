#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<arpa/inet.h>

#define MAXLINE 4096
#define SERV_PORT 3000

int main(int argc, char **argv){
    int sockfd;
    struct sockaddr_in servaddr;
    char sendline[MAXLINE], recvline[MAXLINE];

    if(argc != 3){
        perror("Usage: TCPClient < IP address of the server");
        exit(1);
    }

    memset(&servaddr,0,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(argv[1]);
    servaddr.sin_port = htons(SERV_PORT);

    if((sockfd = socket(AF_INET,SOCK_STREAM,0)) < 0){
        perror("Proplem in creating the socket");
        exit(2);
    }
    
    if(connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr))<0){
        perror("Proplem in comming to the server");
        exit(3);
    }
    FILE *f;
    while(fgets(sendline, MAXLINE, stdin) != NULL){
        send(sockfd,sendline,strlen(sendline),0);
        if(recv(sockfd,recvline,MAXLINE,0) == 0){
            perror("The server terminated permaturely");
            exit(4);
        }
        char link[100] = "file_send/";
        strcat(link,sendline);
        f = fopen(link,"r");
        if(f == NULL){
            printf("File not found\n");
            fclose(f);
            continue;
        }else{
            printf("%s", "String received: ");
            fputs(recvline,stdout);
            fclose(f);
        }    
    }
    exit(0);
}
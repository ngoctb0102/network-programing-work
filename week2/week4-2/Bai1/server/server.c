#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>

#define MAXLINE 4096
#define SERV_PORT 3000
#define LISTENQ 8

int main(int agrc, char **argv){
    int listenfd, connfd, n;
    pid_t childpid;
    socklen_t clilen;
    char buf[MAXLINE];
    struct sockaddr_in cliaddr,servaddr;
    listenfd = socket(AF_INET,SOCK_STREAM, 0);

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);

    bind(listenfd, (struct sockaddr *)&servaddr,sizeof(servaddr));
    listen(listenfd,LISTENQ);
    clilen = sizeof(cliaddr);
    connfd = accept(listenfd,(struct sockaddr *)&cliaddr,&clilen);
    for(;;){
        // clilen = sizeof(cliaddr);
        // connfd = accept(listenfd,(struct sockaddr *)&cliaddr,&clilen);
        printf("%s\n","Received request");
        while((n = recv(connfd,buf,MAXLINE,0)) > 0){
            printf("%s", "String received from and sent to client: ");
            puts(buf);
            char word[100];
            int a = 0;
            // printf("%d\n",strlen(mesg));
            for(int i = 0;i <= strlen(buf);i++){
            if('a' <= buf[i] && buf[i] <= 'z' ){
                word[a] = buf[i];
                a++;
            }else if('A' <= buf[i] && buf[i] <= 'Z'){
                word[a] = buf[i];
                a++;
            }
            }
            word[a] = '\n';
            a++;
            for(int i =0;i<= strlen(buf);i++){
            if('0' <= buf[i] && buf[i] <= '9'){
                word[a] = buf[i];
                a++;
            }
            }
            if(a == strlen(buf)){
                send(connfd, word, n+3, 0); 
            }else{
                send(connfd, "Error", n+3,0); 
            }
    
            // send(connfd,buf,n,0);
        }
        if(n<0){
            perror("Read error");
            exit(1);
        }
        close(connfd);
    }
    close(listenfd);
}
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
        FILE *f;
        // clilen = sizeof(cliaddr);
        // connfd = accept(listenfd,(struct sockaddr *)&cliaddr,&clilen);
        printf("%s\n","Received request");
        while((n = recv(connfd,buf,MAXLINE,0)) > 0){
            printf("%s", "String received from and sent to client: ");
            puts(buf);
            char link[100] = "file_recv/";
            strcat(link,buf);
            f = fopen(link,"r");
            if(f != NULL){
                send(connfd,"Error: File is existent on server",100,0);
            }else{
                fclose(f);
                f = fopen(link,"w");
                fclose(f);
                send(connfd,"Successfull transferring",100,0);
            }
        }
        if(n<0){
            perror("Read error");
            exit(1);
        }
        close(connfd);
    }
    close(listenfd);
}
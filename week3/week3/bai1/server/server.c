#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#define SERV_PORT 1255
#define MAXLINE 255
char*getword(char* in);
int main()
{
  int sockfd, n;
  socklen_t len;
  char mesg[MAXLINE]; 
  struct sockaddr_in servaddr, cliaddr;
 
  sockfd = socket(AF_INET, SOCK_DGRAM, 0); 
  bzero(&servaddr, sizeof(servaddr)); 
  servaddr.sin_family = AF_INET; 
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
  servaddr.sin_port = htons(SERV_PORT); 
  if (bind(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr))>=0)
  {
    printf("Server is running at port %d", SERV_PORT);
  }
  else{
    perror("bind failed");
    return 0;
  }

  for ( ; ; ) { 
    len = sizeof(cliaddr); 
    printf("Receiving data ...");
    n = recvfrom(sockfd, mesg, MAXLINE, 0, (struct sockaddr *) &cliaddr, &len); 
    printf(mesg);
    printf("Sending data ..." );
    char word[100];
    int a = 0;
    // printf("%d\n",strlen(mesg));
    for(int i = 0;i <= strlen(mesg);i++){
      if('a' <= mesg[i] && mesg[i] <= 'z' ){
        word[a] = mesg[i];
        a++;
      }else if('A' <= mesg[i] && mesg[i] <= 'Z'){
        word[a] = mesg[i];
        a++;
      }
    }
    word[a] = '\n';
    a++;
    for(int i =0;i<= strlen(mesg);i++){
      if('0' <= mesg[i] && mesg[i] <= '9'){
        word[a] = mesg[i];
        a++;
      }
    }
    if(a == strlen(mesg)){
      sendto(sockfd, word, n, 0, (struct sockaddr *) &cliaddr, len); 
    }else{
      sendto(sockfd, "Error", n, 0, (struct sockaddr *) &cliaddr, len); 
    }
    
    // sendto(sockfd, num, n, 0, (struct sockaddr *) &cliaddr, len);
  }
  close(sockfd);
  return 0; 
}


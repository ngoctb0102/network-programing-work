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
  struct hostent *he;
  struct in_addr **addr_list;
  struct in_addr addr;
  struct sockaddr_in address;
  int sock = 0, valread;
  struct sockaddr_in serv_addr;
  if((sock = socket(AF_INET, SOCK_STREAM, 0))<0){
	return -1;
  }
  memset(&serv_addr, '0', sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(8080);

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
    mesg[n] = "\0";
    if(mesg[strlen(mesg) - 1] == "\n") mesg[strlen(mesg) - 1] = "\0";
    printf(mesg);
    printf("\nlen = %ld", strlen(mesg));
    printf("Sending data ..." );
    char word[1000] = "";
    if(inet_pton(AF_INET,mesg,&serv_addr.sin_addr) <= 0){
		// printf("Invalid address\n");
        sendto(sockfd, "Invalid address", 1000, 0, (struct sockaddr *) &cliaddr, len);
	}else{
        if(!isdigit(mesg[0])){
            he = gethostbyname(mesg);
            if(he == NULL){
                // printf("Not found information \n");
                sendto(sockfd, "Not found information ", 1000, 0, (struct sockaddr *) &cliaddr, len);
            }else{
                // printf("Official IP: %s\n", inet_ntoa(*(struct in_addr*)he->h_addr));
                strcat(word,"Official IP: ");
                strcat(word, inet_ntoa(*(struct in_addr*)he->h_addr));
                // printf("Alias IP:\n");
                strcat(word,"Alias IP:\n");
                addr_list = (struct in_addr **)he->h_addr_list;
                for(int i = 0; addr_list[i] != NULL; i++) {
                    strcat(word,inet_ntoa(*addr_list[i]));
                    strcat(word,"\n");
                    // printf("%s\n",inet_ntoa(*addr_list[i]));
                }
                sendto(sockfd, word, 1000, 0, (struct sockaddr *) &cliaddr, len);
            }   
	    }else{
            inet_aton(mesg,&addr);
            he = gethostbyaddr(&addr,sizeof(addr),AF_INET);
            if(he == NULL){
                // printf("Not found information\n");
                // return 0;
                sendto(sockfd, "Not found information ", 1000, 0, (struct sockaddr *) &cliaddr, len);
            }else{
                // printf("Official name: %s\n",he->h_name);
                strcat(word,"Official name: ");
                strcat(word,he->h_name);
                addr_list = (struct in_addr **)he->h_aliases;
                // printf("Alias name: \n");
                strcat(word,"Alias name: \n");
                // for(int i = 0; addr_list[i] != NULL; i++) {
                // 	printf("%s\n",*addr_list[i]);
                // }
                addr_list = (struct in_addr **)he->h_addr_list;
                for(int i = 0; addr_list[i] != NULL; i++) {
                    inet_aton(inet_ntoa(*addr_list[i]),&addr);
                    he = gethostbyaddr(&addr,sizeof(addr),AF_INET);
                    if(he == NULL){
                        continue;
                    }else{
                        // printf("%s\n",he->h_name);
                        strcat(word,he->h_name);
                        strcat(word,"\n");
                    }
                    //printf("%s\n",inet_ntoa(*addr_list[i]));
                }
                sendto(sockfd, word, 1000, 0, (struct sockaddr *) &cliaddr, len);
            }
        }
    }
    // sendto(sockfd, num, n, 0, (struct sockaddr *) &cliaddr, len);
  }
  close(sockfd);
  return 0; 
}


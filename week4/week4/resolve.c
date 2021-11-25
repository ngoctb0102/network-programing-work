#include<stdio.h> //printf
#include<string.h> //memset
#include<stdlib.h> //for exit(0);
#include<sys/socket.h>
#include<errno.h> //For errno - the error number
#include<netdb.h>	//hostent
#include<arpa/inet.h>
#include<ctype.h>

int hostname_to_ip(char *  hostname);
int ip_to_hostname(char * ip);

int main(int argc , char *argv[])
{
	if(argc <2)
	{
		printf("Please provide a hostname to resolve");
		exit(1);
	}
	
	char *arg = argv[1];
	
	struct hostent *he;
    struct in_addr **addr_list, **addr_host_list;
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
	if(inet_pton(AF_INET,argv[1],&serv_addr.sin_addr) <= 0){
		printf("Invalid address\n");
		return -1;
	}
	if(!isdigit(arg[0])){
		he = gethostbyname(arg);
		if(he == NULL){
			printf("Not found information \n");
			return 0;
		}else{
			printf("Official IP: %s\n", inet_ntoa(*(struct in_addr*)he->h_addr));
			printf("Alias IP:\n");
			addr_list = (struct in_addr **)he->h_addr_list;
			for(int i = 0; addr_list[i] != NULL; i++) {
				printf("%s\n",inet_ntoa(*addr_list[i]));
			}
		}   
	}else{
		inet_aton(arg,&addr);
		he = gethostbyaddr(&addr,sizeof(addr),AF_INET);
		if(he == NULL){
			printf("Not found information\n");
			return 0;
		}else{
			printf("Official name: %s\n",he->h_name);
			addr_list = (struct in_addr **)he->h_aliases;
			printf("Alias name: \n");
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
					printf("%s\n",he->h_name);
				}
				//printf("%s\n",inet_ntoa(*addr_list[i]));
			}
		}
	}
	return 0;
}

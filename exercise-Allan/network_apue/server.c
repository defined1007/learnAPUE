#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

#define ERR_EXIT(msg) do{perror(msg);exit(1);}while(0)

int main(){
	struct sockaddr_in servaddr;
	int sockfd, ret;

	puts("1. create sockaddr");
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(8080);
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	puts("2. create socket");
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0) ERR_EXIT("socket");

	puts("3. bind sockaddr");
	ret = bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
	if(ret<0) ERR_EXIT("bind");

	puts("4. listen");
	ret = listen(sockfd, 5);
	if(ret<0) ERR_EXIT("listen");

	while(1){
		pause();
	}
	return 0;
}

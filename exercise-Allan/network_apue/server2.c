#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

#define ERR_EXIT(msg) do{perror(msg);exit(1);}while(0)

int main(){
	struct sockaddr_in servaddr, cliaddr;
	int sockfd, clientfd, ret;
	socklen_t cliaddrlen;

	puts("1. create sockaddr");
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(8080);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	puts("2. create socket");
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0) ERR_EXIT("socket");

	puts("3. bind sockaddr");
	ret = bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
	if(ret<0) ERR_EXIT("bind");

	puts("4. listen");
	ret = listen(sockfd, 5);
	if(ret<0) ERR_EXIT("listen");

	puts("5. accept connect");
	cliaddrlen = sizeof(cliaddr);
	clientfd = accept(sockfd, (struct sockaddr*)&cliaddr, &cliaddrlen);
	if(clientfd < 0) ERR_EXIT("accept");
	printf("client fd: %d\n", clientfd);
	printf("sockaddr: %s:%d\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));

	puts("6. getsockname");
	cliaddrlen = sizeof(cliaddr);
	ret = getsockname(clientfd, (struct sockaddr*)&cliaddr, &cliaddrlen);
	if(ret<0) ERR_EXIT("getsockaddr");
	printf("sockaddr: %s:%d\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));

	write(clientfd, "Hello world!\n", 13);

	close(clientfd);
	close(sockfd);
	return 0;
}

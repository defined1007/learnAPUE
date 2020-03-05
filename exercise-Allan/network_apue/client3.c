#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>

#define ERR_EXIT(msg) do{perror(msg);exit(1);}while(0)

int main(){
	int sockfd, ret, n;
	char buf[64];
	struct sockaddr_in servaddr;
	struct sockaddr_in cliaddr;
	socklen_t cliaddrlen;

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(8080);

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd<0) ERR_EXIT("socket");

	ret = connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
	if(ret<0) ERR_EXIT("connect");

	cliaddrlen = sizeof(cliaddr);
	ret = getsockname(sockfd, (struct sockaddr*)&cliaddr, &cliaddrlen);
	if(ret<0) ERR_EXIT("getsockaddr");

	printf("clientfd: %d\n", sockfd);
	printf("cliaddr: %s:%d\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));
	
//	n = read(sockfd, buf, 64);
//	write(STDOUT_FILENO, buf, n);

	while(1){
		scanf("%s", buf);
		if(buf[0] == 'q') break;
		write(sockfd, buf, strlen(buf));
		n = read(sockfd, buf, 63);
		buf[n] = 0;
		puts(buf);
	}
	close(sockfd);
	return 0;
}

#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main(){
	int ret;
	struct sockaddr_in addr;
	struct sockaddr_in test_addr;
	socklen_t test_addrlen;
	
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8080);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
//	addr.sin_addr.s_addr = htonl(INADDR_ANY);	
	
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0) perror("socket");
	ret = bind(sockfd, (struct sockaddr*)&addr, sizeof(addr));
	if(ret<0) perror("bind");

	test_addrlen = sizeof(test_addr);
	ret = getsockname(sockfd, (struct sockaddr*)&test_addr, &test_addrlen);
	if(ret<0) perror("getsockname");

	printf("ip: %s, port: %d\n", inet_ntoa(test_addr.sin_addr), ntohs(test_addr.sin_port));

//	while(1){
//		printf(".");
//		sleep(1);
//	}
	close(sockfd);
	return 0;
}

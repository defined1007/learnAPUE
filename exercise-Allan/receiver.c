#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<signal.h>
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

void handler(int sig){
	char buf[64];
	int i;
	int fd = open("tmp", O_RDONLY);
	if(fd < 0){
		perror("open");
		return;
	}
	
	int n=0;
	if((n=read(fd, buf, 64))<0){
		perror("read");
		close(fd);
		return;
	}
	close(fd);
	unlink("tmp");
	for(i = 0; i<n; ++i) putchar(toupper(buf[i]));
	if(*buf == 'q') exit(0);
}

int main(){
	printf("I'm %d\n",getpid());
	struct sigaction act;
	act.sa_handler = handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	if(sigaction(SIGUSR1, &act, NULL) < 0){
		perror("sigaction");
		return 1;
	}
	while(1) pause();
	return 0;
}

#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>

int main(){
	char buf[64];
	int n = 0;
	int fd = open("hello", O_WRONLY);
	if(fd < 0){
		perror("open fifo");
		return -1;
	}
	puts("has opened fifo");

	while((n=read(STDIN_FILENO, buf, 64)) > 0){
		write(fd, buf, n);
		if(buf[0] == 'q') break;
	}

	close(fd);
	return 0;
}

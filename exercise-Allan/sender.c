#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<signal.h>
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char* argv[]){
	if(argc < 2){
		printf("usage: %s <pid>", argv[0]);
		return 1;
	}
	
	pid_t pid = atoi(argv[1]);
	char buf[64] = {0};
	int n = 0;
	while(1){
		if((n = read(STDIN_FILENO, buf, 64)) > 0){
			int fd = open("tmp", O_WRONLY | O_CREAT | O_EXCL, 0664);
			if(fd < 0){
				perror("open");
				continue;
			}
			write(fd, buf, n);
			close(fd);
			if(kill(pid, SIGUSR1) < 0) perror("kill");
			if(*buf == 'q') return 0;
		}
	}
	return 0;
}


#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

// 父进程写，子进程读

void child(int* fd){
	close(fd[1]); //子进程，关闭写端
	char buf[64];
	int n=0,i;

	while(1){
		n = read(fd[0], buf, 64);
		for(i=0;i<n;++i) putchar(toupper(buf[i]));
		if(*buf == 'q'){
			close(fd[0]);
			exit(0);
		}
		if(n==0) 
		{
			puts("no data to read");
			sleep(1);
		}
	}
	exit(0);
}

int main(){
	int fd[2];
	int n=0;
	char buf[64] = {0};
	if(pipe(fd)<0){
		perror("pipe");
		return -1;
	}
	
	pid_t pid = fork();
	if(pid == 0) child(fd);

	close(fd[0]); //父进程，关闭读端
	while(1){
		n = read(STDIN_FILENO, buf, 64);
		write(fd[1], buf, n);
		if(*buf == 'q'){
			close(fd[1]);
			exit(0);
		}
	}
	return 0;
}

#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>

int main()
{
	int fd = open("test.txt", O_WRONLY|O_CREAT, 0664);
	if(fd==-1) return 1;
	printf("I'm father\n");
	printf("before fork\n");
	
	pid_t pid = fork();
	if(pid>0){
		sleep(3);
		printf("I'm father; I'm writing test.txt...\n");
		write(fd, "hello", 5);
		close(fd);
	}
	else if(pid==0){
		printf("I'm child; I'm writing test.txt...\n");
		write(fd, "world", 5);
		sleep(5);
		write(fd, "lalala", 6);
		close(fd);
	}
	else{
		perror("fork");
		return 1;
	}
	return 0;
}

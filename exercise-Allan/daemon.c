#include<unistd.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>

int main(){
	printf("pid: %d, ppid: %d, sid: %d\n", getpid(), getppid(), getsid(getpid()));

	daemon(0,0);
	
	int fd;
	char buf[256];
	
	while(1){
		printf("pid: %d, ppid: %d, sid: %d\n",getpid(), getppid(),getsid(getpid()));
		fd = open("/home/ming/learnAPUE/exercise-Allan/test.log", O_WRONLY | O_APPEND | O_CREAT);
		if(fd){
			sprintf(buf, "pid: %d, ppid: %d, sid: %d\n", getpid(), getppid(), getsid(getpid()));
			write(fd, buf, strlen(buf));
		}
		sleep(3);
	}
	return 0;
}

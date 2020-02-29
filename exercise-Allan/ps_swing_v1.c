#include<unistd.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>

int main(){
	int pid, i;
	int group1, group2;

	setpgid(getpid(), getpid());
	group1 = getpgid(getpid());

	for(i=1;i<=3;++i){
		pid = fork();
		if(pid == 0){
			if(i == 1){
				setpgid(getpid(), group1);
			}
			else if(i == 2){
				setpgid(getpid(), getpid());
				group2 = getpid();
			}
			else if(i == 3){
				setpgid(getpid(), group2);
			}
			break;
		}
		else if(pid < 0){
			perror("fork");
			return -1;
		}
	}

	printf("进程 %d, pid: %d -> ppid: %d, pgid: [%d], (%s)\n", i%4, getpid(), getppid(), getpgid(getpid()), strerror(errno));
	while(1) sleep(1);

	return 0;
}

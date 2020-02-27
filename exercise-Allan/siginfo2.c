#include<unistd.h>
#include<signal.h>
#include<stdlib.h>
#include<stdio.h>

int main(int argc, char* argv[]){
	if(argc < 2) printf("usage: %s <pid>\n", argv[0]);
	pid_t pid = atoi(argv[1]);

	union sigval val;
	while(1){
		scanf("%d",&val.sival_int);
		if(sigqueue(pid, SIGQUIT, val) < 0){
			perror("sigqueue");
		}
	}
	return 0;
}

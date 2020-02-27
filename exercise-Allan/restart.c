#include<unistd.h>
#include<signal.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>

void handler(int sig){
	switch(sig){
	case SIGUSR1:
		printf("hello SIGUSR1\n"); break;
	case SIGALRM:
		printf("hello SIGALRM\n"); break;
	}
}

int main(int argc, char* argv[]){
	char buf[16] = {0};
	int n=0;
	printf("I'm %d\n", getpid());
	
	struct sigaction act;
	act.sa_handler = handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	
	if(argc >= 2 && strcmp(argv[1], "-r")==0){
		act.sa_flags |= SA_RESTART;
	}

	if(sigaction(SIGUSR1, &act, NULL) < 0){
		perror("signal SIGUSR1");
	}

	if(sigaction(SIGALRM, &act, NULL) < 0){
		perror("signal SIGALRM");
	}
	
	while(1){
		if((n=read(STDIN_FILENO, buf, 15)) < 0){
			if(errno == EINTR) printf("Interrupted by signal\n");
		}
		else{
			buf[n] = 0;
			printf("%s",buf);
		}
	}
	return 0;
}

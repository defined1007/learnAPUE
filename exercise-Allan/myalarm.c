#include<unistd.h>
#include<signal.h>
#include<stdio.h>

void handler(int sig){
	unsigned int remain = 0;
	if (sig == SIGALRM) printf("Bomb!!!!!!\n");
	remain = alarm(5);
}

int main(){
	if (SIG_ERR == signal(SIGALRM, handler)) perror("signal SIGALARM");
	
	unsigned int remain = 0;
	remain = alarm(5);
	while(1){
		write(STDOUT_FILENO, ".", 1);
		sleep(1);
	}
	return 0;
}

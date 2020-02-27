#include<unistd.h>
#include<signal.h>
#include<stdio.h>
#include<stdlib.h>

void printsigset(const sigset_t* set){
	int i;
	for(i=1;i<=64;++i)
	{
		if(i==33) putchar(' ');
		if(sigismember(set, i) == 1) putchar('1');
		else putchar('0');
	}
	puts("");
}

void handler(int sig){
	if(sig == SIGINT) printf("hello SIGINT\n");
	if(sig == SIGQUIT) printf("hello SIGQUIT\n");
}

int main(){
	printf("I'm %d\n",getpid());
	
	sigset_t st, oldst;
	sigemptyset(&st);
	sigaddset(&st, SIGINT);
	sigaddset(&st, SIGTSTP);
	sigprocmask(SIG_BLOCK, &st, &oldst);
	printf("new set:");
	printsigset(&st);
	printf("old set:");
	printsigset(&oldst);

	if(SIG_ERR == signal(SIGINT, handler)){
		perror("signal SIGINT");
		return 1;
	}
	
	if(SIG_ERR == signal(SIGQUIT, handler)){
		perror("signal SIGQUIT");
		return 1;	
	}
	
	puts("");

	int n=0;

	while(1){
		sigpending(&st);
		printsigset(&st);
		puts("");
		sleep(1);
		if(n==10){
			sigset_t tmp;
			sigemptyset(&tmp);
			sigaddset(&tmp, SIGINT);
			sigprocmask(SIG_UNBLOCK, &tmp, NULL);
		}
		++n;
	}
	return 0;
}

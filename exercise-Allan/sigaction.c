#include<unistd.h>
#include<signal.h>
#include<stdio.h>

void printsigset(const sigset_t* set){
	for(int i=1; i<=64; ++i)
	{
		if(i==33) putchar(' ');
		if(sigismember(set, i)) putchar('1');
		else putchar('0');
	}
	puts("");
}

void handler(int sig){
	if (sig == SIGTSTP) printf("hello SIGTSTP\n");
	if (sig == SIGINT) printf("hello SIGINT\n"); 
	sleep(5);
	sigset_t st;
	sigpending(&st);
	printsigset(&st);
}

int main(){
	printf("I'm %d\n",getpid());
	struct sigaction act, oldact;
	act.sa_handler = handler;
	
	sigemptyset(&act.sa_mask);
	sigaddset(&act.sa_mask, SIGINT);
	act.sa_flags = 0;

	sigaction(SIGTSTP, &act, &oldact);
	sigaction(SIGINT, &act, &oldact);

	while(1)
	{
		write(STDOUT_FILENO, ".", 1);
		pause();
	}
	return 0;
}

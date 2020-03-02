#include<unistd.h>
#include<stdio.h>
#include<signal.h>
#include<pthread.h>

void printsigset(const sigset_t *set){
	int i;
	for(i=1; i<=64; ++i){
		if(i==33) putchar(' ');
		if(sigismember(set, i) == 1) putchar('1');
		else putchar('0');
	}
	puts("");
}

void* fun1(void* arg){
	sigset_t mask, st;
	sigemptyset(&mask);
	sigaddset(&mask, SIGINT);
	pthread_sigmask(SIG_BLOCK, &mask, NULL);

	while(1){
		printf("I'm fun1:\t");
		sigpending(&st);
		printsigset(&st);
		sleep(3);
	}
}

void* fun2(void* arg){
	sigset_t st;
	
	while(1){
		printf("I'm fun2:\t");
		sigpending(&st);
		printsigset(&st);
		sleep(3);
	}
}

int main(){
	sigset_t mask, st;
	sigemptyset(&mask);
	sigaddset(&mask, SIGQUIT);
	pthread_sigmask(SIG_BLOCK, &mask, NULL);

	pthread_t tid1, tid2;
	pthread_create(&tid1, NULL, fun1, NULL);
	pthread_create(&tid2, NULL, fun2, NULL);
	
	sleep(2);
	pthread_kill(tid1, SIGINT);
	while(1){
		printf("I'm main:\t");
		sigpending(&st);
		printsigset(&st);
		sleep(3);
	}
	return 0;
}

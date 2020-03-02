#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<signal.h>
#include<pthread.h>

#define PPERR(err, msg) do{errno = err; perror(msg);exit(-1);}while(0)

struct ticket{
	int remain;
	pthread_mutex_t lock;
};

struct ticket t;

void printtype(pthread_mutexattr_t* attr){
	int err, type;
	char* s = "???";
	err = pthread_mutexattr_gettype(attr, &type);
	if(err!=0) PPERR(err, "pthread_mutexattr_gettype");

	if(type == PTHREAD_MUTEX_NORMAL){
		s = "PTHREAD_MUTEX_NORMAL";
		printf("MUTEX TYPE = %s\n",s);
	}
	if(type == PTHREAD_MUTEX_ERRORCHECK){
		s = "PTHREAD_MUTEX_ERROCHECK";
		printf("MUTEX TYPE = %s\n",s);
	}
	if(type == PTHREAD_MUTEX_RECURSIVE){
		s = "PTHREAD_MUTEX_RECURSIVE";
		printf("MUTEX TYPE = %s\n",s);
	}
	if(type == PTHREAD_MUTEX_DEFAULT){
		s = "PTHREAD_MUTEX_DEFAULT";
		printf("MUTEX TYPE = %s\n",s);
	}
}

void setrecursive(pthread_mutexattr_t* attr){
	int err, type;
	type = PTHREAD_MUTEX_RECURSIVE;
	err = pthread_mutexattr_settype(attr, type);
	if(err!=0) PPERR(err, "pthread_mutexattr_settype");
}

void handler(int sig){
	if(sig == SIGUSR1) puts("receive SIGUSR1");
	else if(sig == SIGINT) puts("receive SIGINT");
	pthread_mutex_lock(&t.lock);
	printf("%s enter handler\n", sig == SIGUSR1 ? "SIGUSR1":"SIGINT");
	t.remain++;
	sleep(3);
	printf("%s exit handler\n", sig == SIGUSR1 ? "SIGUSR1" : "SIGINT");
	pthread_mutex_unlock(&t.lock);
}

int main(int argc, char* argv[]){
	int recursive = 0;
	if(argc >= 2) recursive = 1;
	
	t.remain = 3;

	pthread_mutexattr_t attr;
	pthread_mutexattr_init(&attr);
	printtype(&attr);
	if(recursive == 1){
		puts("modify type --------------------->");
		setrecursive(&attr);
		printtype(&attr);
	}
	pthread_mutex_init(&t.lock, &attr);
	pthread_mutexattr_destroy(&attr);

	signal(SIGUSR1, handler);
	signal(SIGINT, handler);

	puts("send SIGUSR1");
	kill(getpid(), SIGUSR1);

	pthread_mutex_destroy(&t.lock);

	printf("remain = %d\n", t.remain);

	return 0;
}

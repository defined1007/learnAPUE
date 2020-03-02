#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<errno.h>

#define PERR(err,msg) do{errno=err;perror(msg);exit(-1);}while(0)

int total = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void prepare(){
	int err;
	puts("preparing locks...");
	err = pthread_mutex_lock(&lock);
	if(err!=0) PERR(err, "prepare lock failed");
}

void parent(){
	int err;
	puts("parent unlocking locks...");
	err = pthread_mutex_unlock(&lock);
	if(err!=0) PERR(err, "parent unlock failed");
}

void child(){
	int err;
	puts("child unlocking locks...");
	err = pthread_mutex_unlock(&lock);
	if(err!=0) PERR(err, "child unlock failed");
}

void* fun(void* arg){
	while(1){
		pthread_mutex_lock(&lock);
		total++;
		puts("fun: total++");
		sleep(5);
		pthread_mutex_unlock(&lock);
		sleep(1);
	}
	return NULL;
}

int main(){
	int err;
	pid_t pid;
	pthread_t tid;
	pthread_create(&tid, NULL, fun, NULL);
	err = pthread_atfork(prepare, parent, child);
	if(err!=0) PERR(err, "atfork");

	sleep(1);
	puts("parent about to fork...");
	pid = fork();
	if(pid<0) PERR(errno, "fork");
	else if(pid==0){
		int status;
		while(1){
			pthread_mutex_lock(&lock);
			total++;
			puts("child: total++");
			sleep(2);
			pthread_mutex_unlock(&lock);
			sleep(1);
		}
		exit(0);
	}

	pthread_join(tid,NULL);
}

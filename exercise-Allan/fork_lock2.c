#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<errno.h>

#define PERR(err,msg) do{errno=err;perror(msg);exit(-1);}while(0)

int total = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void* fun(void* arg){
	while(1){
		pthread_mutex_lock(&lock);
		total++;
		puts("fun: total++");
		sleep(3);
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
	sleep(1);
	
	puts("parent about to fork ...");

	pthread_mutex_lock(&lock);	
	pid = fork();
	pthread_mutex_unlock(&lock);

	if(pid<0) PERR(errno, "fork");
	else if(pid==0){
		int status;
		while(1){
			puts("child require lock...");
			pthread_mutex_lock(&lock);
			total++;
			puts("child: total++");
			sleep(2);
			pthread_mutex_unlock(&lock);
			sleep(1);
		}
		exit(0);
	}
//	exit(0);
	pthread_join(tid,NULL);
//	return 0;
}


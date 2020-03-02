#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<errno.h>

#define PERR(err, msg) do{errno = err; perror(msg); exit(-1);}while(0)

void* fun(void* arg){
	while(1){
		printf("I'm %d, my father is %d\n",getpid(),getppid());
		sleep(3);
	}
	return NULL;
}

int main(){
	int err;
	pid_t pid;
	pthread_t tid;
	pthread_create(&tid, NULL, fun, NULL);
	
	puts("parent about to fork ...");
	pid = fork();
	if(pid<0) PERR(errno, "fork");
	else if(pid==0){
		int status;
		err = pthread_join(tid, (void*)&status);
		if(err!=0) PERR(err, "pthread_join");
		while(1){
			puts(".");
			sleep(2);
		}
		exit(0);
	}
	pthread_join(tid, NULL);
	return 0;
}

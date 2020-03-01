#include<unistd.h>
#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define ERR(name, err) do{printf("%s:%s\n", #name, strerror(err)); exit(-1);}while(0);

void* th_fn1(void* arg){
	puts("thread 1 returning");
	return (void*)10;
}

void* th_fn2(void* arg){
	puts("thread 2 exiting");
	pthread_exit((void*)20);
	puts("thread 2 exited");
}

int main(){
	pthread_t tid1, tid2;
	int err;
	void* ret;
	
	err = pthread_create(&tid1, NULL, th_fn1, NULL);
	if(err!=0) ERR(pthread_create2, err);

	err = pthread_create(&tid2, NULL, th_fn2, NULL);
	if(err!=0) ERR(pthread_create2, err);

	sleep(2);

	err = pthread_join(tid1, &ret);
	if(err!=0) ERR(pthread_join1, err);
	printf("thread 1 exit code %d\n", (int)ret);

	err = pthread_join(tid2, &ret);
	if(err!=0) ERR(pthread_join2, err);
	printf("thread 2 exit code %d\n", (int)ret);

	return 0;
}


#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include<pthread.h>

int mydata;

void* fun1(void* arg){
	errno = 5;
	mydata = 5;
	sleep(1);
	printf("fun1: errno = %d, mydata = %d\n", errno, mydata);
	return NULL;
}

void* fun2(void* arg){
	errno = 10;
	mydata = 10;
	sleep(1);
	printf("fun2: errno = %d, mydata = %d\n", errno, mydata);
	return NULL;
}

int main(){
	pthread_t tid1, tid2;
	pthread_create(&tid1, NULL, fun1, NULL);
	pthread_create(&tid2, NULL, fun2, NULL);
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	return 0;
}


#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<pthread.h>

#define myerrno (*_myerrno())

pthread_key_t key;
pthread_once_t init_done = PTHREAD_ONCE_INIT;

void thread_init(){
	puts("I'm thread init");
	pthread_key_create(&key, free);
}

int* _myerrno(){
	int* p;
	pthread_once(&init_done, thread_init);
	p = (int*)pthread_getspecific(key);
	if(p==NULL){
		p = (int*)malloc(sizeof(int));
		pthread_setspecific(key, (void*)p);
	}
	return p;
}

void* fun1(void* arg){
	errno = 5;
	myerrno = 5;
	sleep(1);
	printf("fun1: errno = %d, myerrno = %d\n",errno,myerrno);
	return NULL;
}

void* fun2(void* arg){
	errno = 10;
	myerrno = 10;
	sleep(1);
	printf("fun2: errno = %d, myerrno = %d\n",errno,myerrno);
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


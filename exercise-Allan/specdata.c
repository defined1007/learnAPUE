#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>

pthread_key_t key;

void destructor(void* arg){
	printf("destructor: hello %d\n", (int)arg);
}

void* fun1(void* arg){
	int data = 5;
	pthread_setspecific(key, (void*)data);
	int x = (int)pthread_getspecific(key);
	printf("fun1: x = %d\n", x);
}

void* fun2(void* arg){
	int data = 10;
	pthread_setspecific(key, (void*)data);
	int x = (int)pthread_getspecific(key);
	printf("fun2: x = %d\n", x);
}

int main(){
	pthread_t tid1, tid2;
	pthread_key_create(&key, destructor);

	pthread_create(&tid1, NULL, fun1, NULL);
	pthread_create(&tid2, NULL, fun2, NULL);
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	return 0;
}

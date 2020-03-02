#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

pthread_once_t init_done = PTHREAD_ONCE_INIT;

void thread_init(){
	puts("I'm thread init");
}

void* fun(void* arg){
	pthread_once(&init_done, thread_init);
	printf("Hello, I'm %d\n", (int)arg);
	return NULL;
}

int main(){
	pthread_t tid[5];
	for(int i = 0; i<5; ++i){
		pthread_create(&tid[i], NULL, fun, (void*)i);
	}
	for(int i = 0; i<5; ++i){
		pthread_join(tid[i],NULL);
	}
	return 0;
}

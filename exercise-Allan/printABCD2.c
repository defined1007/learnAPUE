#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

int num = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t conda = PTHREAD_COND_INITIALIZER;
pthread_cond_t condb = PTHREAD_COND_INITIALIZER;
pthread_cond_t condc = PTHREAD_COND_INITIALIZER;
pthread_cond_t condd = PTHREAD_COND_INITIALIZER;

void* printA(void* arg){
	while(1){
		pthread_mutex_lock(&lock);
		while(num != 0) pthread_cond_wait(&condd, &lock);
		printf("A\n");
		num = (num+1)%4;
		usleep(1000*1000);
		pthread_mutex_unlock(&lock);
		pthread_cond_signal(&conda);
	}
}

void* printB(void* arg){
	while(1){
		pthread_mutex_lock(&lock);
		while(num!=1) pthread_cond_wait(&conda, &lock);
		printf("B\n");
		num = (num+1)%4;
		usleep(1000*1000);
		pthread_mutex_unlock(&lock);
		pthread_cond_signal(&condb);
	}
}

void* printC(void* arg){
	while(1){
		pthread_mutex_lock(&lock);
		while(num!=2) pthread_cond_wait(&condb, &lock);
		printf("C\n");
		num = (num+1)%4;
		usleep(1000*1000);
		pthread_mutex_unlock(&lock);
		pthread_cond_signal(&condc);
	}
}

void* printD(void* arg){
	while(1){
		pthread_mutex_lock(&lock);
		while(num!=3) pthread_cond_wait(&condc, &lock);
		printf("D\n");
		num = (num+1)%4;
		usleep(1000*1000);
		pthread_mutex_unlock(&lock);
		pthread_cond_signal(&condd);
	}
}

int main(){
	pthread_t tid1, tid2, tid3, tid4;
	pthread_create(&tid1, NULL, printA, NULL);
	pthread_create(&tid2, NULL, printB, NULL);
	pthread_create(&tid3, NULL, printC, NULL);
	pthread_create(&tid4, NULL, printD, NULL);

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	pthread_join(tid3, NULL);
	pthread_join(tid4, NULL);

	return 0;
}

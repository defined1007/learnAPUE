#include<unistd.h>
#include<stdio.h>
#include<pthread.h>

int tickets = 3;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void* allen(void* arg){
	int flag = 1;
	while(flag){
		pthread_mutex_lock(&lock);
		int t = tickets;
		usleep(1000*20);
		if(t>0){
			printf("allen buy a ticket\n");
			--t;
			usleep(1000*20);
			tickets = t;
		}
		else flag = 0;
		pthread_mutex_unlock(&lock);
		usleep(1000*20);
	}
	return NULL;
}

void* luffy(void* arg){
	int flag = 1;
	while(flag){
		pthread_mutex_lock(&lock);
		int t = tickets;
		if(t>0){
			printf("luffy buy a ticket\n");
			--t;
			usleep(1000*20);
			tickets = t;
		}
		else flag = 0;
		pthread_mutex_unlock(&lock);
		usleep(1000*20);
	}
	return NULL;
}

int main(){
	pthread_t tid1, tid2;
	pthread_create(&tid1, NULL, allen, NULL);
	pthread_create(&tid2, NULL, luffy, NULL);
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	return 0;
}

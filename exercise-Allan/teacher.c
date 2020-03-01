#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>

int finished = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void* do_homework(void* arg){
	sleep(5);
	pthread_mutex_lock(&lock);
	finished = 1;
	pthread_mutex_unlock(&lock);
}

void* check_homework(void* arg){
	sleep(1);
	pthread_mutex_lock(&lock);
	printf("老师：作业写完了吗？\n");
	while(finished == 0){
		printf("学生：没写完呢！\n");
		pthread_mutex_unlock(&lock);
		printf("老师：好的，你接着写吧！\n");
	//	sleep(1);
		printf("-----------------------------\n");
		sleep(1);
		pthread_mutex_lock(&lock);
		printf("老师：作业写完了吗？\n");	
	}
	printf("学生：写完啦！\n");
	pthread_mutex_unlock(&lock);
	printf("老师开始检查----------------\n");
}

int main(){
	pthread_t tid1, tid2;
	pthread_create(&tid1, NULL, do_homework, NULL);
	pthread_create(&tid2, NULL, check_homework, NULL);
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	return 0;
}


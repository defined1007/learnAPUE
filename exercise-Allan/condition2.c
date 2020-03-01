#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

int finished = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void* do_homework(void* arg){
	sleep(5);
	pthread_mutex_lock(&lock);
	finished = 1;
	pthread_mutex_unlock(&lock);
	pthread_cond_broadcast(&cond);
	printf("发送条件信号------------\n");
}

void* check_homework(void* arg){
	sleep(1);
	pthread_mutex_lock(&lock);
	printf("老师1：作业写完了吗？\n");
	while(finished == 0){
		printf("学生：没写完呢！\n");
		printf("老师1：好的，你接着写吧！\n");
		printf("---------------------------\n");
		pthread_cond_wait(&cond, &lock);
		if(finished == 0) pthread_exit(0);
		printf("老师1：作业写完了吗？\n");
	}
	printf("学生：我写完啦！\n");
//	pthread_mutex_unlock(&lock);
	printf("老师1开始检查-------------\n");
	finished--;
	pthread_mutex_unlock(&lock);
}

void* check_homework2(void* arg){
	sleep(1);
	pthread_mutex_lock(&lock);
	printf("老师2：作业写完了吗？\n");
	while(finished == 0){
		printf("学生：没写完呢！\n");
		printf("老师2：好的，你接着写吧！\n");
		printf("--------------------------\n");
		pthread_cond_wait(&cond, &lock);
		if(finished == 0) pthread_exit(0);
		printf("老师2：作业写完了吗？\n");
	}
	printf("学生：我写完啦！\n");
	printf("老师2开始检查------------\n");
	finished--;
	pthread_mutex_unlock(&lock);
}

int main(){
	pthread_t tid1, tid2, tid3;
	pthread_create(&tid1, NULL, do_homework, NULL);
	pthread_create(&tid2, NULL, check_homework, NULL);
	pthread_create(&tid3, NULL, check_homework2, NULL);
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	pthread_join(tid3, NULL);
	return 0;
}

#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

struct Test{
	int t;
	pthread_mutex_t mutex;
	pthread_cond_t cond;
}test = {0, PTHREAD_MUTEX_INITIALIZER, PTHREAD_COND_INITIALIZER};

void* print(void* arg){
	int num = *(int*)arg;
	while(1)
	{
		pthread_mutex_lock(&test.mutex);
	
		while(num!=test.t) pthread_cond_wait(&test.cond, &test.mutex);
	
		if(num==0) printf("A\n");
		else if(num==1) printf("B\n");
		else if(num==2) printf("C\n");
		else if(num==3) printf("D\n");
	
		test.t = (test.t + 1)%4;
		pthread_mutex_unlock(&test.mutex);
		pthread_cond_broadcast(&test.cond);
	}
}

int main(){
	pthread_t tid[4];
//	int* arg = (int*)malloc(sizeof(int));
	for(int i=0; i<=3; ++i){
		int* arg = (int*)malloc(sizeof(int));
		*arg = i;
		pthread_create(&tid[i], NULL, print, (void*)arg);
//		free(arg);
	}
	
	for(int i=0;i<=3;++i){
		pthread_join(tid[i],NULL);
	}

//	free(arg);
	return 0;
}

#include<stdio.h>
#include<pthread.h>
#include<time.h>

void* fun(void* arg){
	int i,j,start;
	start = time(0);
	for(i=0;i<1000;++i){
		for(j = 0; j<1000000; ++j);
	}
	printf("finished, consume %ld s\n", time(0) - start);
	printf("cannot be canceled\n");
	return NULL;
}

int main(){
	pthread_t tid;
	pthread_create(&tid, NULL, fun, NULL);
	pthread_cancel(tid);
	puts("cancel thread");
	pthread_join(tid,NULL);
	return 0;
}

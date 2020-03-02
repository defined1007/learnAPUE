#include<stdio.h>
#include<pthread.h>
#include<time.h>
#include<unistd.h>
#include<stdlib.h>

void* fun(void* arg){
	int i,j,start,oldtype;
	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS,&oldtype);
	start = time(0);
	for(i=0;i<1000000000;++i){}
	printf("finished, consume %ld s\n", time(0)-start);
	printf("cannot be canceled\n");
	return NULL;
}

int main(){
	pthread_t tid;
	pthread_create(&tid, NULL, fun, NULL);
	sleep(1);
	pthread_cancel(tid);
	puts("cancel thread");
	pthread_join(tid, NULL);
	return 0;
}

#include<unistd.h>
#include<pthread.h>
#include<stdio.h>
#include<string.h>

/*
 * 注意编译的时候要链接pthread库
 * gcc hellothread.c -o hellothread -lpthread
 */

void* th_fn(void* arg){
	char* name = (char*)arg;
	int i;

	for(i=1;i<=10;++i){
		printf("%s : %d\n", name, i);
		if(strcmp("Allen", name) == 0) usleep(1000*150);
		else usleep(1000*5);
	}
	return NULL;
}

int main(){
	int err;
	pthread_t allen, luffy;
	char* name1 = "Allen";
	char* name2 = "Luffy";

	err = pthread_create(&allen, NULL, th_fn, (void*)name1);
	if(err!=0){
		perror("pthread_create");
		return -1;
	}

	err = pthread_create(&luffy, NULL, th_fn, (void*)name2);
	if(err!=0){
		perror("pthread_craete");
		return -1;
	}

	sleep(1);

	printf("Allen id: %lx\n", allen);
	printf("Luffy id: %lx\n", luffy);

	return 0;
}

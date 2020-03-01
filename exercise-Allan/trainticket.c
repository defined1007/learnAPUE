#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>

struct Ticket{
	int remain;
	pthread_rwlock_t rwlock;
	pthread_mutex_t mlock;
}ticket;

//通过命令行参数来控制使用哪一种锁
//0：不加锁，1：加读写锁，2：加互斥锁
int lock = 0;
void* query(void* arg){
	int name = (int)arg;
	sleep(rand()%5+1);
	if(lock == 1){
		pthread_rwlock_rdlock(&ticket.rwlock);
	}
	else if(lock == 2){
		pthread_mutex_lock(&ticket.mlock);
	}

	int remain = ticket.remain;
	sleep(1);
	printf("%03d query: %d\n", name, remain);
	
	if(lock == 1) pthread_rwlock_unlock(&ticket.rwlock);
	else if(lock == 2) pthread_mutex_unlock(&ticket.mlock);
	
//	sleep(rand()%5+2);

	return NULL;
}

void* buy(void* arg){
	int name = (int)arg;
	
	if(lock == 1) pthread_rwlock_wrlock(&ticket.rwlock);
	else if(lock == 2) pthread_mutex_lock(&ticket.mlock);

	int remain = ticket.remain;
	remain -= 10;
	sleep(1);
	ticket.remain = remain;
	printf("%03d buy 10 tickets\n", name);

	if(lock == 1) pthread_rwlock_unlock(&ticket.rwlock);
	else if(lock == 2) pthread_mutex_unlock(&ticket.mlock);

	sleep(rand()%5+2);

	return NULL;
} 

int main(int argc, char* argv[]){
	lock = 0;
	if(argc>=2) lock = atoi(argv[1]);
	int names[100];
	pthread_t tid[100];

	int i;
	for(i=0;i<100;++i) names[i] = i;
	ticket.remain = 1000;

	printf("remain ticket = %d\n", ticket.remain);

	pthread_rwlock_init(&ticket.rwlock, NULL);
	pthread_mutex_init(&ticket.mlock, NULL);
	
	for(i=0;i<100;++i){
		if(i%10 == 0) pthread_create(&tid[i], NULL, buy, (void*)names[i]);
		else pthread_create(&tid[i], NULL, query, (void*)names[i]);
	}

	for(i=0;i<100;++i) pthread_join(tid[i], NULL);

	pthread_rwlock_destroy(&ticket.rwlock);
	pthread_mutex_destroy(&ticket.mlock);
	printf("remain ticket = %d\n", ticket.remain);

	return 0;
}

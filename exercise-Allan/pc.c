#include "semutil.h"
#include<string.h>
#include<sys/shm.h>

#define MUTEX 0
#define FULL 1
#define EMPTY 2

static void init(){
	int id = C(3);
	S(id, MUTEX, 1);
	S(id, FULL, 0);
	S(id, EMPTY, 5);
	int shmid = shmget(0x8888, 4, IPC_CREAT | IPC_EXCL | 0664);
	ASSERT(shmget, shmid);
	int* cake = shmat(shmid, NULL, 0);
	if(cake == (int*)-1) ASSERT(shmat, -1);
	*cake = 0;
	ASSERT(shmdt, shmdt(cake)); 
}

static int getsemid(){
	C(0);
}

static int getshmid(){
	int id = shmget(0x8888, 0, 0);
	ASSERT(shmget, id);
	return id;
}

static void release(int id){
	D(id);
	ASSERT(shmctl, shmctl(getshmid(), IPC_RMID, NULL));
}

static void producer(){
	int id = getsemid();
	int shmid = getshmid();
	int* cake = shmat(shmid, NULL, 0);
	while(1){
		P(id, EMPTY);
		P(id, MUTEX);
		printf("current cake = %d, ", *cake);
		(*cake)++;
		printf("produce a cake, ");
		printf("cake = %d\n", *cake);
		V(id,MUTEX);
		V(id, FULL);
		sleep(1);
	}
	shmdt(cake);
}

static void consumer(){
	int id = getsemid();
	int shmid = getshmid();
	int* cake = shmat(shmid, NULL, 0);
	int count = 10;
	while(count--){
		P(id,FULL);
		P(id,MUTEX);
		printf("current cake = %d, ", *cake);
		(*cake)--;
		printf("consume a cake, ");
		printf("cake = %d\n", *cake);
		V(id, MUTEX);
		V(id, EMPTY);
	}
	shmdt(cake);
}

int main(int argc, char* argv[]){
	if(argc < 2){
		printf("usage: %s <option -b -d -p -c>\n", argv[0]);
		return -1;
	}
	
	if(!strcmp("-b", argv[1])) init();
	else if(!strcmp("-d", argv[1])) release(getsemid());
	else if(!strcmp("-p", argv[1])) producer();
	else if(!strcmp("-c", argv[1])) consumer();
	return 0;
}


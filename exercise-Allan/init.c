#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<pthread.h>

#define PERR(msg) do{ perror(msg); exit(-1); }while(0)
#define PPERR(err, msg) do{ err = errno; perror(msg); exit(-1);} while(0)

struct ticket{
	int remain;
	pthread_mutex_t lock;
};

void printshared(pthread_mutexattr_t* attr){
	int err, shared;
	err = pthread_mutexattr_getpshared(attr, &shared);
	if(err!=0) PPERR(err, "pthraed_mutexattr_getshared");
	if(shared == PTHREAD_PROCESS_PRIVATE) 
		puts("shared = PTHREAD_PROCESS_PRIVATE");
	else if(shared == PTHREAD_PROCESS_SHARED)
		puts("shared = PTHREAD_PROCESS_SHARED");
	else
		puts("shared = ???");
}

void printrobust(pthread_mutexattr_t* attr){
	int err, robust;
	err = pthread_mutexattr_getrobust(attr, &robust);
	if(err!=0) PPERR(err, "pthrad_mutexattr_getrobust");
	if(robust == PTHREAD_MUTEX_STALLED)
		puts("robust = PTHREAD_MUTEX_STALLED");
	else if(robust == PTHREAD_MUTEX_ROBUST)
		puts("robust = PTHREAD_MUTEX_ROBUST");
	else
		puts("robust = ???");
}

int main(int argc, char* argv[]){
	int err, shared, robust = 0, flag = 1;
	if(argc >= 2) robust = 1;
	key_t key = 0x8888;
	
	int id = shmget(key, getpagesize(), IPC_CREAT | IPC_EXCL | 0666);
	if(id<0) PERR("shmget");

	struct ticket* t = (struct ticket*)shmat(id, NULL, 0);
	if((int)t == -1) PERR("shmat");

	t->remain = 5;

	pthread_mutexattr_t mutexattr;
	err = pthread_mutexattr_init(&mutexattr);
	if(err!=0) PPERR(err, "pthread_mutexattr_init");

	printshared(&mutexattr);
	printrobust(&mutexattr);

	shared = PTHREAD_PROCESS_SHARED;
	err = pthread_mutexattr_setpshared(&mutexattr, shared);
	if(err!=0) PPERR(err, "pthread_mutexattr_setpshared");

	if(robust){
		err = pthread_mutexattr_setrobust(&mutexattr, PTHREAD_MUTEX_ROBUST);
		if(err!=0) PPERR(err, "pthread_mutexattr_setpshared");
	}

	puts("modify attribute -----------------");
	printshared(&mutexattr);
	printshared(&mutexattr);
	
	pthread_mutex_init(&t->lock, &mutexattr);
	
	err = pthread_mutexattr_destroy(&mutexattr);
	if(err!=0) PPERR(err, "pthread_mutexattr_destroy");

	err = shmdt((void*)t);
	if(err!=0) PERR("shmdt");

	return 0;
}

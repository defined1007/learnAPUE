#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>

#define PERR(err,msg) do{errno = err; perror(msg); exit(-1);} while(0)

int lock(int fd){
	puts("locking...");
	struct flock flk;
	int err;
	flk.l_type = F_WRLCK;
	flk.l_start = SEEK_SET;
	flk.l_whence = 2;
	flk.l_len = 2;
	err = fcntl(fd, F_SETLKW, &flk);
	if(err<0) PERR(errno, "lock");
	puts("locked...");
	return err;
}

int unlock(int fd){
	puts("unlocking...");
	struct flock flk;
	int err;
	flk.l_type = F_UNLCK;
	flk.l_start = SEEK_SET;
	flk.l_whence = 2;
	flk.l_len = 2;
	err = fcntl(fd, F_SETLKW, &flk);
	if(err<0) PERR(errno, "unlock");
	puts("unlocked");
	return err;
}

int main(){
	printf("pid: %d\n",getpid());
	int fd = open("test.txt", O_WRONLY);
	lock(fd);
	sleep(10);
	puts("close fd2");
	int fd2 = dup(fd);
	close(fd2);
	sleep(10);
	unlock(fd);
	close(fd);
	return 0;
}

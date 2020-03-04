#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>

#define PERR(err, msg) do{errno = err; perror(msg);exit(-1);}while(0)

int lockend(int fd){
	puts("locking...");
	struct flock flk;
	int err;
	flk.l_type = F_WRLCK;
	flk.l_start = 0;
	flk.l_whence = SEEK_END;
	flk.l_len = 0;
	err = fcntl(fd, F_SETLKW, &flk);
	if(err<0) PERR(errno, "lock");
	puts("locked...");
	return err;
}

int unlocked(int fd){
	puts("unlocking...");
	struct flock flk;
	int err;
	flk.l_type = F_UNLCK;
	flk.l_start = 0;
	flk.l_whence = SEEK_END;
	flk.l_len = 0;
	err = fcntl(fd, F_SETLKW, &flk);
	if(err<0) PERR(errno, "unlock");
	puts("unlocked...");
	return err;
}

int main(){
	printf("pid: %d\n",getpid());
	int fd = open("test.txt", O_WRONLY | O_APPEND);
	lockend(fd);
	write(fd, "l", 1);
	sleep(5);
	unlocked(fd);
	sleep(30);
	close(fd);
	return 0;
}

#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>

#define PERR(err,msg) do{errno=err; perror(msg);exit(-1);}while(0)

int lock(int fd, int start, int len){
	puts("locking");
	struct flock flk;
	int err;
	flk.l_type = F_WRLCK;
	flk.l_whence = SEEK_SET;
	flk.l_start = start;
	flk.l_len = len;
	err = fcntl(fd, F_SETLKW, &flk);
	if(err<0) PERR(errno, "lock");
	puts("locked");
	return err;
}

int unlock(int fd, int start, int len){
	puts("unlocking...");
	struct flock flk;
	int err;
	flk.l_type = F_UNLCK;
	flk.l_whence = SEEK_SET;
	flk.l_start = start;
	flk.l_len = len;
	err = fcntl(fd, F_SETLKW, &flk);
	if(err<0) PERR(errno, "unlock");
	puts("unlocked...");
	return err;
}

int main(int argc, char* argv[]){
	if(argc<4){
		printf("Usage: %s <filename> <start> <len>\n", argv[0]);
		return -1;
	}
	char* filename = argv[1];
	int start = atoi(argv[2]);
	int len = atoi(argv[3]);
	printf("pid: %d\n", getpid());
	int fd = open(filename, O_WRONLY);
	lock(fd,start,len);
	sleep(10);
	unlock(fd, start, len);
	sleep(10);
	return 0;
}

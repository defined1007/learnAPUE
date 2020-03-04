#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<aio.h>
#include<strings.h>
#include<errno.h>

#define ERR_EXIT(msg) do{perror(msg); exit(1);} while(0)

int main(){
	int fd, ret;
	char buf[64];
	struct aiocb my_aiocb;
	
	bzero((char*)&my_aiocb, sizeof(struct aiocb));

	my_aiocb.aio_buf = buf;
	my_aiocb.aio_fildes = STDIN_FILENO;
	my_aiocb.aio_nbytes = 64;
	my_aiocb.aio_offset = 0;

	ret = aio_read(&my_aiocb);
	if(ret < 0) ERR_EXIT("aio_read");

	const struct aiocb* aio_list[5] = {NULL};
	aio_list[0] = &my_aiocb;
	
	ret = aio_suspend(aio_list, 5, NULL);
	if(ret<0) ERR_EXIT("aio_suspend");
	puts("aio_suspend return");

	while(aio_error(&my_aiocb) == EINPROGRESS){
		write(STDOUT_FILENO, ".", 1);
		sleep(1);
	}

	ret = aio_return(&my_aiocb);
	if(ret<0) ERR_EXIT("aio_return");	
	printf("content: %s, return: %d\n", buf, ret);
	return 0;
}

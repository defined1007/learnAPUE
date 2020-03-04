#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/epoll.h>
#include<errno.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<signal.h>

#define PERR(msg) do{perror(msg);exit(-1);} while(0)

void handler(int sig){
	if(sig == SIGINT) puts("hello SIGINT");
}

int process(char* prompt, int fd){
	int n;
	char buf[4];
	char line[64];
	n = read(fd, buf, 3);
	if(n<0) PERR("read");
	else if(n==0){
		sprintf(line, "%s closed\n", prompt);
		puts(line);
		return 0;
	}
	else if(n>0){
		buf[n] = 0;
		sprintf(line, "%s say: %s", prompt, buf);
		puts(line);
	}
	return n;
}

int main(int argc, char* argv[]){
	int i, n, res;
	char buf[64];
	int fds[3];
	int fd;

	if(SIG_ERR == signal(SIGINT, handler)) PERR("signal");

	fds[0] = STDIN_FILENO;
	fds[1] = open("aa.fifo", O_RDONLY);
	printf("open pipe: fd = %d\n", fds[1]);
	fds[2] = open("bb.fifo", O_RDONLY);
	printf("open pipe: fd = %d\n", fds[2]);

	struct epoll_event evts[4];

	int epfd = epoll_create(4);

	for(i=0;i<3;++i){
		struct epoll_event ev;
		ev.data.fd = fds[i];
		ev.events = EPOLLIN;
		if(argc>1) ev.events |= EPOLLET;
		if(epoll_ctl(epfd, EPOLL_CTL_ADD, fds[i], &ev) < 0) PERR("epoll_ctl");
	}
	
	while(1){
		res = epoll_wait(epfd, evts, 4, -1);
		printf("res = %d\n", res);

		if(res<0){
			if(errno == EINTR){
				perror("epoll_wait");
				continue;
			}
			PERR("epoll_wait");
		}
		else if(res==0){
			continue;
		}
		for(i=0;i<res;++i){
			fd = evts[i].data.fd;
			if(evts[i].events & EPOLLIN){
				sprintf(buf, "fd%d", fd);
				process(buf, fd);
			}
			if(evts[i].events & EPOLLERR){
				printf("fd%d Error\n", i);
				epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL);
			}
			if(evts[i].events & EPOLLHUP){
				printf("fd%d Hang Up\n", i);
				epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL);
			}
		}
	}
}

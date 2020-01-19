#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>

#define BUFFERSIZE 10
char MSG_TRY[] = "try again!\n";

int main()
{
	char buf[BUFFERSIZE] = {0};
	int len;
	int fd;
	
	//fd = open("/dev/tty", O_RDONLY | O_NONBLOCK);
	int flags = fcntl(STDIN_FILENO, F_GETFL);
	if(flags == -1)
	{
		perror("fcntl get");
		exit(1);
	}
	flags |= O_NONBLOCK;

	if(fcntl(STDIN_FILENO, F_SETFL, flags) == -1)
	{
		perror("fcntl set");
		exit(1);
	}
	while(1)
	{
		len = read(STDIN_FILENO, buf, BUFFERSIZE);
		if(len<0)
		{
			if(errno == EAGAIN)
			{
				write(STDOUT_FILENO, MSG_TRY, strlen(MSG_TRY));
				sleep(1);
			}
			else
			{
				perror("read");
				exit(1);
			}
		}
		else break;
	}
	write(STDOUT_FILENO, buf, len);
	return 0;
}

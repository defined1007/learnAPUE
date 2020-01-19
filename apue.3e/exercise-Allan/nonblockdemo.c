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
	
	fd = open("/dev/tty", O_RDONLY | O_NONBLOCK);

	while(1)
	{
		len = read(fd, buf, BUFFERSIZE);
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

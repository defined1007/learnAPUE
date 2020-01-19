#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>

#define BUFFERSIZE 10

int main()
{
	char buf[BUFFERSIZE] = {0};
	int len =0;

	while(1)
	{
		len = read(STDIN_FILENO, buf, BUFFERSIZE);
		write(STDOUT_FILENO, buf, len);
	}
	return 0;
}

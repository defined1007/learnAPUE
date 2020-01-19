#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>

#define BUFFERSIZE 64

int main()
{
	int src = open("test-lseek", O_RDONLY);
	if(src<0)
	{
		perror("open");
		return 1;
	}
	
	char buf[BUFFERSIZE] = {0};
	
	lseek(src, 6, SEEK_SET);
	read(src, buf, BUFFERSIZE);
	
	printf("%s\n", buf);
	return 0;
}

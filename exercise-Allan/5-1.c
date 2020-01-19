#include <unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>

#define BUFFERSIZE 4096

/* 只采用Linux系统接口，实现文件复制。 */

int main(int argc, char* argv[])
{
	char buf[BUFFERSIZE] = {0};
	int src = open(argv[1], O_RDONLY);
	int dest = open(argv[2], O_CREAT|O_WRONLY, 0777);
	
	int tmp = 0;
	while((tmp = read(src, buf, BUFFERSIZE)) > 0)
	{
		write(dest, buf, BUFFERSIZE);
	}

	close(src);
	close(dest);
	return 0;
}

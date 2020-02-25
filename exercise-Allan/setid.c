#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>

int main()
{
	int fd = open("test.txt", O_WRONLY | O_APPEND);
	if (fd == -1)
	{
		perror("open");
		return -1;
	}
	
	printf("uid: %d\n", getuid());
	printf("euid: %d\n", geteuid());

	close(fd);
	return 0;
}

#include<stdio.h>
#include<unistd.h>

int main()
{
	printf("hello signal! I'm %d\n", getpid());
	while(1){
		write(STDOUT_FILENO, ".", 1);
		sleep(10);
	}
	return 0;
}

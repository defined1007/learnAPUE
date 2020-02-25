#include<unistd.h>
#include<stdio.h>
#include<string.h>

int main()
{
	printf("before fork\n");

	pid_t pid, n=5;
	while(n--)
	{
		pid = fork();
		if(pid == 0) break;
		else if(pid < 0)
		{
			perror("fork");
			return 1;
		}
	}
	if(pid==0)
	{
		printf("hello, I'm child %d; my father is %d\n",getpid(), getppid());
		return 0;
	}
	while(1)
	{
		sleep(3);
		printf("hello, I'm father %d\n",getpid());
	}
	return 0;
}

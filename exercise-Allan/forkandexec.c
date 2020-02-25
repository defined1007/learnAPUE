#include<unistd.h>
#include<string.h>
#include<stdio.h>

int main()
{
	char* argv[] = {"ls", "-l", NULL};
	pid_t pid = fork();

	if(pid>0){
		printf("I'm father\n");
	}
	else if(pid==0)
	{
		printf("I'm child\n");
		if(execvp("ls",argv)==-1)
		{
			perror("exec");
			return 1;
		}
	}
	else
	{
		perror("fork");
		return 0;
	}
	return 0;
}

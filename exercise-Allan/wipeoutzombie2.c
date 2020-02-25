#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<sys/wait.h>
#include<sys/types.h>

int main(){
	printf("before fork\n");
	pid_t pid, n=5;
	while(n--)
	{
		pid = fork();
		if(!pid) break;
		else if(pid<0)
		{
			perror("fork");
			return 1;
		}
	}
	if(!pid)
	{
		sleep(4*n+1);
		printf("hello, I'm child [ %d ]; my father is [ %d ]\n\n", getpid(),getppid());
		if(4*n+1==5) *((int*)0) = 0;
		return 4*n+1;
	}
	int status = 0;
	while(1)
	{
		pid = waitpid(-1,&status,WUNTRACED | WCONTINUED);
		if(pid==-1)
		{
			perror("wait");
			sleep(5);
			printf("I'm father [ %d ]; I have wiped out all zombies\n\n",getpid());
			return 1;
		}
		else if(pid == 0)
		{
			printf("hello, I'm father; I'm waiting child\n\n");
		}
		else
		{
			if(WIFEXITED(status)){
				printf("child [ %d ] <exited> with code [ %d ]\n\n",pid,WEXITSTATUS(status));
			}
			else if (WIFSIGNALED(status)){
				printf("child [ %d ] <terminated> abnormally, signal [ %d ]\n\n",pid,WTERMSIG(status));
#ifdef WCOREDUMP				
				if(WCOREDUMP(status)){
					printf("<core file generated> in child [ %d ]\n\n",pid);
				}
#endif
			}
			else if (WIFSTOPPED(status)){
				printf("child [ %d ] <stopped>, signal [ %d ]\n\n",pid,WSTOPSIG(status));
			}
			else if(WIFCONTINUED(status)){
				printf("child [ %d ] <continued>\n\n",pid);
			}
		}
	}
	return 0;
}

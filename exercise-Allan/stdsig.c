#include<unistd.h>
#include<signal.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/wait.h>
#include<sys/types.h>

void waitchild(int sig){
	int status;
	pid_t pid;
	while((pid = waitpid(-1, &status, WUNTRACED | WCONTINUED)) > 0){
		if(WIFEXITED(status)) printf("child %d exited! return code = %d\n\n",pid, WEXITSTATUS(status));
		else if(WIFSIGNALED(status)) printf("child %d terminated by signal %d\n\n", pid, WTERMSIG(status));
		else if(WIFSTOPPED(status)) printf("child %d stopped by signal %d\n\n", pid, WSTOPSIG(status));
		else if(WIFCONTINUED(status)) printf("child %d continued\n\n", pid);
	}
//	sleep(1);
}

void child(int n)
{
	if(n==9) *((int*)0) = 0;
	exit(n+1);
}

int main()
{
	printf("I'm %d\n",getpid());
	if(SIG_ERR == signal(SIGCHLD, waitchild)) perror("signal SIGSTOP");
	
	int n = 10;
	pid_t pid;
	while(n--){
		pid = fork();
		if(pid == 0) child(n);
		else if(pid == -1) perror("fork");
	}
	while(1){
		write(STDOUT_FILENO, ".", 1);
		sleep(5);
	}
	return 0;
}

#include<unistd.h>
#include<stdio.h>
#include<string.h>

int main()
{
	char* argv[] = {"ls", "-l", NULL};
	if(execvp("ls", argv) == -1){
		perror("exec");
		return 1;
	}
	return 0;
}

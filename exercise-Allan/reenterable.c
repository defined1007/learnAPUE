#include<unistd.h>
#include<signal.h>
#include<sys/types.h>
#include<pwd.h>
#include<stdio.h>

void handler(int sig){
	getpwnam("root");
}

int main(){
	if(SIG_ERR == signal(SIGINT, handler)){
		perror("signal");
		return 1;
	}
	printf("I'm %d\n",getpid());
	struct passwd *pwd = getpwnam("ming");
	sleep(10);
	printf("ming's uid = %d\n",pwd->pw_uid);
	return 0;
}

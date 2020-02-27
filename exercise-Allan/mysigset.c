#include<unistd.h>
#include<signal.h>
#include<stdio.h>

void printsigset(const sigset_t* set){
	int i;
	for(i=1;i<=64;++i){
		if(i==33) putchar(' ');
		if(sigismember(set,i) == 1) putchar('1');
		else putchar('0');
	}
	puts("");
}

int main()
{
	sigset_t st;
	printf("1. create set\n");
	printsigset(&st);

	printf("\n2. vertify sigset_t is a 64-bit integer\n");
	unsigned int test[2] = {0xf0f0f0f0, 0xf0f0f0f0};
	printsigset(&st);

	printf("\n3. fill set\n");
	sigfillset(&st);
	printsigset(&st);

	printf("\n4. empty set\n");
	sigemptyset(&st);
	printsigset(&st);

	sigaddset(&st, SIGHUP);
	sigaddset(&st, SIGINT);
	sigaddset(&st, SIGKILL);
	sigaddset(&st, SIGSYS);
	sigaddset(&st, SIGRTMIN);
	sigaddset(&st, SIGRTMAX);
	printsigset(&st);

	printf("\n.6 delete SIGKILL from set\n");
	sigdelset(&st, SIGKILL);
	printsigset(&st);

	printf("\n");
	if(sigismember(&st, SIGKILL)){
		printf("SIGKILL is member\n");
	}
	if(sigismember(&st, SIGINT)){
		printf("SIGINT is member\n");
	}

	return 0;
}

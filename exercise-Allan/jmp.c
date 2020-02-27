#include<setjmp.h>
#include<stdio.h>

jmp_buf jmpbuf;

void dosomething(){
	int n=0;
	scanf("%d", &n);
	if(n==100) longjmp(jmpbuf,1);
	if(n==200) longjmp(jmpbuf,2);
}

int main(){
	int res = 0;
	if((res = setjmp(jmpbuf)) != 0){
		printf("hello! res = %d\n", res);
	}
	
	while(1){
		dosomething();
	}
	return 0;
}

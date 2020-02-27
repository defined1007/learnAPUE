#include<unistd.h>
#include<setjmp.h>
#include<stdio.h>

jmp_buf hello; //设置标号



void func2(){
	longjmp(hello,1);
}

void func1(){
	setjmp(hello);
	printf("hello world\n");
	sleep(2);
	func2();
}

int main(){
	func1();
	return 0;
}

#include<unistd.h>
#include<sys/select.h>
#include<stdio.h>
#include<stdlib.h>

void printset(const fd_set* st){
	int i;
	for(i=0; i<16; ++i){
		if(FD_ISSET(i, st)) putchar('1');
		else putchar('0');
	}
	puts("");
}

int main(){
	int i;
	fd_set st;
	puts("uninitial");

	puts("zeros");
	FD_ZERO(&st);
	printset(&st);

	puts("set odd");
	for(i=0; i<16; ++i){
		if(i%2){
			FD_SET(i,&st);
		}
	}
	printset(&st);

	puts("clear 3");
	FD_CLR(3, &st);
	printset(&st);
	
	puts("zeros");
	FD_ZERO(&st);
	printset(&st);

	return 0;
}

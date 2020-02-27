#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char* argv[]){
	if(argc < 3){
		printf("usage: %s <path> <id>\n", argv[0]);
		return -1;
	}
	int id = atoi(argv[2]);
	
	key_t key = ftok(argv[1], id);
	
	if(key == -1){
		perror("ftok");
		return -1;
	}
	
	printf("key = 0x%08x\n",key);
	return 0;
}

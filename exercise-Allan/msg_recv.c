#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>

#define ASSERT(prompt, res) if((res)<0){perror(#prompt); exit(-1);}

typedef struct{
	char name[20];
	int age;
}Person;

typedef struct{
	long type;
	Person person;
}Msg;

void printMsg(Msg* msg){
	printf("{ type = %ld, name = %s, age = %d }\n", msg->type, msg->person.name, msg->person.age);
}

int main(int argc, char* argv[]){
	if(argc<2){
		printf("usage: %s <type>\n",argv[0]);
		return -1;
	}
	
	long type = atol(argv[1]);
	
	int id = msgget(0x8888, 0);
	
	ASSERT(msgget, id);

	Msg msg;
	int res;

	while(1){
		res = msgrcv(id, &msg, sizeof(Person), type, IPC_NOWAIT);
		if(res<0){
			if(errno == ENOMSG){
				printf("No message!\n");
				break;
			}
			else ASSERT(msgrcv, res);
		}
		printMsg(&msg);
	}
	return 0;
}

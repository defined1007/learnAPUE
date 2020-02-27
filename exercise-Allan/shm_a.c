#include<unistd.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
#include<string.h>

int main(){
	//shmget函数通过事先约定的键值 0x8888 创建（IPC_CREAT）一个内核对象并返回其id。如果id 0x8888的内核对象存在，就失败（IPC_EXCL）	
	int id = shmget(0x8888, 4096, IPC_CREAT | IPC_EXCL | 0664);
	//如果失败就退出
	if(id<0){
		perror("shmget");
		return -1;
	}

	//打印获取到的内核对象id
	printf("id = %d\n", id);

	//使用函数shmat(share memory attach)将内核对象维护的内存挂接到指定线性地址（第二个参数）
	//如果第二个参数为0，系统帮你选择一个合适的线性地址。
	char* buf = shmat(id, NULL, 0);
	
	//如果挂接失败就推出
	if(buf == (char*)-1){
		perror("shmat");
		return -1;
	} 
	
	//将数据拷贝到共享内存
	strcpy(buf, "hello, share memory!\n");

	//使用shmdt（share memory detach）将挂接的内存卸载
	if(shmdt(buf) < 0){
		perror("shmdt");
		return -1;
	}
	return 0;
}

#include<sys/types.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
#include<unistd.h>
#define SIZE 27

int main(int argc, char *argv[]){
	int sharedMem_ID;
	key_t  mem_key;
	
	mem_key = ftok(".", 'a');
	if((sharedMem_ID = shmget(mem_key, SIZE, IPC_CREAT | 0666)) < 0){
		perror("Not able to get shared memory\n");
		exit(EXIT_FAILURE);
	}
	char *sharedMem_ptr;
	sharedMem_ptr = (char *)shmat(sharedMem_ID, NULL, 0);
	if(sharedMem_ptr ==  (char *)-1){
		perror("Couldn't attach the shared memory to server memory\n");
		exit(EXIT_FAILURE);
	}

	char *s;
	s = sharedMem_ptr;
	
	for(char c = 'a'; c <= 'z'; c++)
		*s++ = c;
	*s = NULL;

	while(*sharedMem_ptr != '*')
		usleep(1000);
	
	exit(EXIT_SUCCESS);
	
}

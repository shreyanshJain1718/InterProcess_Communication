#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
#include<stdlib.h>
#define SIZE 27
int main(int argc, char *argv[]){
	int shrdMem_ID;
	key_t mem_key;
	char *shrdMem_ptr;
	char *s;
	mem_key = ftok(".", 'a');
	shrdMem_ID = shmget(mem_key, SIZE, 0666);
	if(shrdMem_ID < 0){
		perror("Couldn't create shared memory\n");
		exit(EXIT_FAILURE);
	}
	shrdMem_ptr = (char *)shmat(shrdMem_ID, NULL, 0);
	if(shrdMem_ptr == (char *)-1){
		perror("Couldn't connect to the shared memory");
		exit(EXIT_FAILURE);
	}

	for(s = shrdMem_ptr; *s != NULL; s++)
		putchar(*s);
	putchar('\n');

	*shrdMem_ptr = '*';
	printf("\n It's done from client \n\n\n");
	exit(EXIT_FAILURE);
}

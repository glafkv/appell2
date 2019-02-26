#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
int main(int argc, char *argv[]){
	

	key_t key;
	key = ftok(".", 'x');
	printf("key in child %d\n", key);

	return 0;
}

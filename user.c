#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#define shared_key 54321

int shmid;
char *shmaddr;
int main(int argc, char *argv[]){
	
	char parameter1 [12]; //hold shmid for passing 
	char *array[3];
	char *ptr;
	int *p;
	int shared_memory[3]; //get the stuff from shared memory
	int increment, seconds, nanoseconds;

	shmid = atoi(argv[1]);
	shmaddr = (char *) shmat (shmid, 0, 0); //find shared memory
	
	//get info from shared memory
		ptr = shmaddr + sizeof (shared_memory);
		p = (int *)shmaddr;
		array[0]=ptr;
		ptr += *p++;
		array[1] = ptr;
		ptr += *p++;
		array[2]=ptr;
		ptr += *p++;
	
		increment = atoi(array[0]);
		seconds = atoi(array[1]);
		nanoseconds = atoi(array[2]);
		
		printf("Seconds: %i\n", seconds);
		printf("Nano: %i\n", nanoseconds);

	

return 0;
}

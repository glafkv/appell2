#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#define shared_key 54321
int main(int argc, char *argv[]){
	

	int shmid, n, times = 0;
	char * shmaddr, * ptr;
	char * shared_memory[3];
	int * p;
	int value, seconds, milliseconds;
	int array[2];
	char store[4];
	
	shmid = atoi(argv[1]);
	n = atoi(argv[2]);	
	shmaddr = (char *) shmat (shmid, 0, 0);
	
	printf("Working...\n");
	
	while(times < (n*1000000)){
		ptr = shmaddr + sizeof (int) * 2;
		p = (int *)shmaddr;
		shared_memory[0] = ptr;
		ptr += *p++;
		shared_memory[1] = ptr;
		
		seconds = atoi(shared_memory[0]);
		milliseconds = atoi(shared_memory[1]);
	
		if(milliseconds > 998){
			seconds += 1;
			milliseconds = 0;
		}
		else {
			milliseconds += 1;
		}
		ptr = shmaddr + sizeof (array);
	
		sprintf(store, "%d", seconds);	
		array[0] = sprintf(ptr, store) + 1;
		ptr += array[0];
		
		sprintf(store, "%d", milliseconds);
		array[1] = sprintf(ptr, store) + 1;
		
		memcpy(shmaddr, &array, sizeof (array));
		
		times++;
	}
	shmdt(shmaddr);

}

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(){
	int shmId, i;
	key_t key;
	int *shmPtr;
	const int SIZE = 10;
	key = ftok("./", 100);
	if((shmId = shmget(key, SIZE*sizeof(int), 0666))<0){
		printf("shmget failed in client\n");
		exit(1);
	}
	if((shmPtr = (int *) shmat( shmId, NULL, 0)) == -1){
		printf("shmt failed in client\n");
		exit(2);
	}
	int NonZeros = 1;
	while(NonZeros != 0){
		NonZeros = 0;
		for(i = 0; i <SIZE; i++){
			if(shmPtr[i] != 0)
				NonZeros++;
		}
	}
	printf("client has detected that entire array is zeroed\n");
	shmPtr[0] = 1;
	shmPtr[1] = 1;
	for(i = 2; i < SIZE; i++)
		shmPtr[i] = shmPtr[i-1] + shmPtr[i-2];
	printf("Client has finished finding all numbers\n");
	shmdt(shmPtr);

	return 0;
}

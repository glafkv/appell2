#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <string.h>

#define SHSIZE 100
int main(int argc, char *argv[]){
	

	int shmid;
	key_t key;
	char *shm;
	char *s;
	key = 9876;
	shmid = shmget(key, SHSIZE, 0666);
	
	if(shmid < 0){
		perror("shmget");
		exit(1);
	}
	shm = shmat(shmid, NULL, 0);
	if(shm == (char *) -1){
		perror("shmat");
		exit(1);
	}
	for(s = shm; *s != 0; s++){
		printf("%c", *s);
	}
	printf("\n");
	*shm = '*';
	
	shmdt(shm);
	/*int shmId, i;
	key_t key;
	int *shmPtr;
	const int SIZE = 10;
	key = ftok("./user", 100);
	
	if((shmId = shmget(key, SIZE*sizeof(int), 0666))< 0){
		printf("shmget failed in client\n");
		exit(1);
	}
	if((shmPtr = (int *) shmat( shmId, NULL, 0)) == -1){
		printf("shmat failed in client\n");
		exit(2);
	}
	int NonZeros = 1;
	while (NonZeros != 0) {
		NonZeros = 0;
		for(i = 0; i < SIZE; i++){
			if(shmPtr[i] != 0){
				NonZeros++;
			}
		}
	}
	printf("Client has detected that entire array is zeroed\n");
	shmPtr[0]=1;
	shmPtr[1]=1;
	for(i = 2; i <SIZE; i++){
		shmPtr[i] = shmPtr[i-1] + shmPtr[i-2];
	}
	printf("client has finished finding all numbers\n");
	shmdt(shmPtr);*/

	return 0;
}

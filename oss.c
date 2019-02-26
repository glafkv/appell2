#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/ipc.h>
int main(int argc, char *argv[])
{

	int choice = 0;
	int shmid = 0;
	char * n = NULL;
	char * s = NULL;
	opterr = 0;

	int shmId, i;
	key_t key;
	int *shmPtr;
	const int SIZE = 10;
	key = ftok("./", 100);
	if((shmId = shmget(key, SIZE*sizeof(int), IPC_CREAT|0666))<0){
		printf("smget failed in server\n");
		exit(1);
	}
	if((shmPtr = (int *) shmat(shmId, NULL, 0)) == -1){
		printf("shmat failed in server\n");
		exit(2);
	}
	for(i = 0; i < SIZE; i++)
		shmPtr[i] = 0;
	
	printf("server has zeroed array\n");
	int totalZeros = SIZE;
	while(totalZeros == SIZE){
		totalZeros=0;
		for(i=0;i<SIZE; i++){
			if(shmPtr[i]==0)
				totalZeros++;
		}
	}
	printf("client has filled array with fibs\n");
	for(i=0; i<SIZE; i++)
		printf("%d", shmPtr[i]);
		
	shmdt(shmPtr);
	shmctl(shmId, IPC_RMID, NULL);
	

	/*while((choice = getopt(argc, argv, "hn:s:i:o:")) != -1){
		switch(choice){
			case 'h':
				printf("\tI'm here to help!\n");
				printf("************************\n");
				printf("-h brings up the help menu\n");
				printf("-n x : x is a number that will indicate the maximum total of child processes it will ever create. The default is 4.\n");
				printf("-s x : x will indicate how many children should be allowed to exist in the system at the same time. The default is 2.\n");
				printf("-i inputfile : indicate the name of your input file. The default is input.txt\n");
				printf("-o outputfile : indicate the name of your output file. The default is output.txt\n");
				exit(0);
			case 's':
				s = optarg;
				break;
			case 'n':
				n = optarg;
				break;
			case '?':
				fprintf(stderr, "Not an option.\n");
				return 1;
			default:
				abort();
		}
	}*/

	






return 0;
}

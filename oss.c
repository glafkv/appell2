#include <stdio.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <string.h>
#include <stdlib.h>

#define SHSIZE 100
int main(int argc, char *argv[])
{
	int shmid;
	key_t key;
	char *shm;
	char *s;
	key = 9876;
	shmid = shmget(key, SHSIZE, IPC_CREAT | 0666);
	
	if(shmid < 0){
		perror("shmget");
		exit(1);
	}
	shm = shmat(shmid, NULL, 0);
	if(shm == (char *) -1){
		perror("shmat");
		exit(1);
	}
	
	memcpy(shm, "Hello world", 11);
	
	s = shm;
	s += 11;
	*s = 0;
	while(*shm != '*'){
		sleep(1);	
	}
	shmdt(shm);
	shmctl(shmid, IPC_RMID, NULL);
	//int choice = 0;
	//char * n = NULL;
	//char * s = NULL;	
	
	
	


	
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

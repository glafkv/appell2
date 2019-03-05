#include <stdio.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>
#include <assert.h>
#include <signal.h>

#define SHSIZE 100

int shm_id;
void terminate(int sig){
	printf("Control C was pressed. Press Control C again to terminate\n");
	shmctl(shm_id, IPC_RMID, NULL);
	(void)signal(SIGNT, SIG_DFL);
}
int main(int argc, char *argv[])
{
	key_t key;
	char *shm;
	char *s;
	key = 9876;
	pid_t childpid = 0; 
	int i = 0, j = 0, shmid = 0, total = 0, done, n, s;
	opterr = 0;
	int arr[2];
	shmid = shmget(key, SHSIZE, IPC_CREAT | 0666);
	
	
	(void)signal(SIGNINT, terminate);
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
	int choice = 0;
	char * n = NULL;
	char * s = NULL;	
	
	
	

	if(argc < 4){
		fprintf(stderr, "Process %s requires additional arguments\n",argv[0]);
		return 1;
	}
	
	while((choice = getopt(argc, argv, "hn:s:i:o:")) != -1){
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
			case 'i':
				i = optarg;
				break;
			case 'o':
				o = optarg;
				break;
			case '?':
				if(optopt == 'n'){
					fprintf(stderr, "-n requires an accompanying number.\n");
				}
				if(optopt == 's'){
					fprintf(stderr,"-s requires an accompanying number.\n");
				} else{
					fprintf(stderr, "Unknown option\n");
				}
				return 1;
			default:
				abort();
		}
	}

	if(strcmp(argv[3],"-n") == 0){
		n = atoi(argv[4]);	
		s = atoi(argv[2]);
	}
	else{
		n = atoi(argv[2]);
		s = atoi(argv[4]);
	}
	if(s > 20){
		printf("Too many children. Defaulting to 20.\n");
		s = 20;
	}






return 0;
}

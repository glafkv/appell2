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

int main(int argc, char *argv[])
{

	//Child pid
	pid_t childpid = 0; 
	//variables
	int i = 0;
	opterr = 0;
	int arr[2];
	char *infile;
	char *outfile;
	//default values for the files.
	infile = "input.txt";
	outfile = "output.txt";
	//Opens the files
	FILE *infptr = fopen(infile, "r");
	FILE *outfptr = fopen(outfile, "a");
	//For case statement
	int choice = 0;
	char * nval = NULL;
	char * sval = NULL;	
	//variables to allocate shared memory.
	int shmid;
	key_t key;
	char *shm;
	char *s;
	
	
	
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
				sval = optarg;
				
			case 'n':
				nval = optarg;
				break;
			case 'i':
				infile = optarg;
				break;
			case 'o':
				outfile = optarg;
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
	if(argc < 4){
		fprintf(stderr, "%s requires additional arguments\n", argv[0]);
		return 1;
	}
	if(strcmp(argv[3], "-s" == 0)){
		n = atoi(argv[2]);
		s = atoi(argv[4]);	
	}
	else {
		n = atoi(argv[4]);
		s = atoi(argv[2]);
	}
	if(s > 20){
		printf("Too many children. Now it's 20.");
		s = 20;
	}
		
	key = 9876;
	shmid = shmget(key, SHSIZE, IPC_CREAT | 0666);
	if(shmid < 0){
		perror("shmget: ");
		exit(1);
	}
	shm = shmat(shmid, NULL, 0);
	if(shm == (char *) -1){
		perror("shmat: ");
		exit(1);
	}
	




fclose(infptr);
fclose(outfptr);

return 0;
}

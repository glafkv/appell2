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

#define shared_key 98765

int shmid;
char *shmaddr;
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
	//if(argc < 4){
	//	fprintf(stderr, "%s requires additional arguments\n", argv[0]);
	//	return 1;
	//}

		
	char parameter1 [12];
	char *ptr;
	int array[3];
	

	//create shared memory
	if((shmid = shmget(shared_key, 1024, IPC_CREAT | IPC_EXCL | 0666)) < 0){
		perror("shmget: ");
		exit(1);
	}
	//sprintf(parameter1, "%d", shmid);

	//char parameter2 [n]; 
	//sprintf(parameter2, "%d", n);
	//Initialize and write to shared memory.
	shmaddr = (char *) shmat (shmid, 0, 0); //get shared address
	ptr = shmaddr + sizeof (array); //point to shared memory beginning
	
	array[0] = sprintf(ptr, "20000") + 1; //store 0 to array[0]
	ptr += array[0]; //move pointer to next array element
	
	array[1] = sprintf(ptr, "0") + 1; //store num to array[1]
	ptr += array[1]; //move pointer to next array element
	
	array[2] = sprintf(ptr, "64987") + 1;

	
	memcpy(shmaddr, &array, sizeof (array)); //stores the array in shared memore

	sprintf(parameter1, "%d", shmid); //store shmid in param1 to pass through execlp

	if(fork() == 0){
		execlp("./user", "./user", parameter1, (char *)NULL);
		fprintf(stderr, "Failed to exec to user\n");
	}
	

	shmdt(shmaddr);
	shmctl(shmid, IPC_RMID, NULL);
fclose(infptr);
fclose(outfptr);

return 0;
}

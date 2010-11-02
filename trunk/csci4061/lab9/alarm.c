#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

int ALARMcount;

void AlarmSignalHandler(int sig) {
	
	//if another alarm occurs while in signal handler, ignore it
	
 
	//increment alarm counter


       	
	//print "Woke up for the # time" if count<=3
	if(ALARMcount <= 3){
	
		printf("woke up for the %d time\n",ALARMcount);
	}
	else {
		exit(0);
        }
	
	//reinstall the signal handler

	
}

int main(int argc, char*argv[]){
	
	int i;
	//initialize counter
	ALARMcount = 0;

	//install signal handler for SIGALRM

 
	//call alarm(3) and pause() 3 times




	return 0;
} 

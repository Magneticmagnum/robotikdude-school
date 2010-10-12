#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int
main(int argc, char *argv[])
{
	if (argc != 3) {
		printf("Usage: %s <OldFile> <NewFile>\n", argv[0]);
		exit(1);
	}
	//create a new hard link
	if(link(argv[1],argv[2])==-1)
	{
		perror("Link error:");
		exit(1);
	}
	return 0;
}

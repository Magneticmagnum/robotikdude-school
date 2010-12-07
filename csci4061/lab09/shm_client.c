#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define SHMSZ     100
extern int errno;

main()
{
  int shmid;
  key_t key;
  char *shm;

  //shared memory key
  key = 5678;

  //Locate the segment.
  shmid = shmget(key, SHMSZ, 0644 | IPC_CREAT);
  if (shmid == -1) {
    printf("Unable to get shared memory space. ERRNO CODE: %i\n", errno);
    exit(1);
  }

  //Attach the segment to our data space.
  shm = shmat(shmid, (void*) 0, 0);
  if (shm == (void*) -1) {
    printf("Unable to attach shared memory space. ERRNO CODE: %i\n", errno);
    exit(1);
  }

  //Read what the server put in the memory and print it out
  printf("Server wrote: %s\n", shm);

  //change the first character to tell server to finish
  *shm = '*';

  return 0;
}


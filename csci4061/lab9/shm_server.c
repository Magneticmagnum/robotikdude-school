#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define SHMSZ     100
extern int errno;

main()
{
  char c;
  int shmid;
  key_t key;
  char *shm;

  //key of the shared memory
  key = 5678;

  //Create the segment.
  shmid = shmget(key, SHMSZ, 0644 | IPC_CREAT);
  if (shmid == -1) {
    printf("Unable to get shared memory space. ERRNO CODE: %i\n", errno);
    exit(1);
  }

  //attach the shared memory
  shm = shmat(shmid, (void*) 0, 0);
  if (shm == (void*) -1) {
    printf("Unable to attach shared memory space. ERRNO CODE: %i\n", errno);
    exit(1);
  }

  //write something into the shared memory, you can use strcpy
  strcpy(shm, "Hello client, say \"Hello, World!\" for me.");


  //waiting for the content to be read
  printf("Waiting for the client to read...\n");
  while (*shm != '*')
    sleep(1);

  return 0;
}


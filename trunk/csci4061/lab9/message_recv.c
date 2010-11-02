#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct my_msgbuf
{
  long mtype;
  char mtext[200];
};

int main(void)
{
  struct my_msgbuf buf;
  int msqid;
  key_t key;

  key = 1234;

  //connect to the queue
  msqid = msgget(key, 0666 | IPC_CREAT);
  if (msqid == -1) {
    perror("Unable to create message queue");
    exit(1);
  }

  printf("Waiting to receive messages...\n");

  //read message from the queue
  //print them out
  while (-1 != msgrcv(msqid, &buf, sizeof(struct my_msgbuf), 1, 0)) {
    printf("%s", buf.mtext);
  }

  return 0;
}

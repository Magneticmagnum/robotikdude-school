#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
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
  //get the message queue
  msqid = msgget(key, 0666 | IPC_CREAT);
  if (msqid == -1) {
    perror("Unable to create message queue");
    exit(1);
  }

  //read from stdin, write into message queue
  printf("Enter lines of text, ^D to quit:\n");
  buf.mtype = 1;

  //get message from terminal line by line
  //write them into message queue
  while (fgets(buf.mtext, 200, stdin) != NULL) {
    int r = msgsnd(msqid, &buf, sizeof(struct my_msgbuf), 0);
    if (r == -1) {
      perror("Error sending message.");
      exit(1);
    }
  }

  //remove the message queue
  if (msgctl(msqid, IPC_RMID, NULL) == -1) {
    perror("msgctl");
    exit(1);
  }

  return 0;
}

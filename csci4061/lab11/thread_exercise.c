#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int myturn = 0;
char *files[] = {"thread_exercise.c", "thread_exercise.c"};
int i_am_done[2];

void* writefile(void* arg)
{
  char buf[1024];
  int id = (int) arg;
  i_am_done[id] = 0;
  FILE * f = fopen(files[id], "r");

  //read file interleavely
  while (i_am_done[id] == 0) {
    while (myturn != id)
      ; // WAIT
    if (fgets(buf, 1023, f) != NULL) {
      printf("Thread %i: %s", id, buf);
    }
    else {
      i_am_done[id] = 1;
    }
    if (i_am_done[((myturn + 1) % 2)] == 0) {
      myturn = ((myturn + 1) % 2);
    }
  }
  fclose(f);
  return NULL;
}

int main(int argc, char **argv)
{

  pthread_t th1, th2;

  /* Create thread */
  pthread_create(&th1, NULL, writefile, (void*) 0);
  pthread_create(&th2, NULL, writefile, (void*) 1);

  /* Join threads */
  pthread_join(th1, NULL);
  pthread_join(th2, NULL);

  return 0;

}


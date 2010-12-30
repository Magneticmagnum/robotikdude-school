#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define RINGSIZE 10

//the two threads
void* producer(void* arg);
void* consumer(void* arg);

static pthread_mutex_t ring_access = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t buffer_full = PTHREAD_COND_INITIALIZER;
static pthread_cond_t buffer_empty = PTHREAD_COND_INITIALIZER;

static int buffer[RINGSIZE];
static int in = 0;
static int out = 0;
static int count = 0;

int main(int argc, char **argv)
{
  pthread_t cons;
  pthread_t prod;

  // create two threads -- producer and consumer
  printf("creating threads.\n");
  pthread_create(&cons, NULL, consumer, NULL);
  pthread_create(&prod, NULL, producer, NULL);

  //joins the two threads 
  printf("joining threads.\n");
  pthread_join(cons, NULL);
  pthread_join(prod, NULL);

  return 0;
}

/**
 Inserts a number into the buffer
 */
void* producer(void* arg)
{
  printf("PRODUCER: starting\n");
  while (1) {
    pthread_mutex_lock(&ring_access);
    printf("PRODUCER: lock\n");
    while (count >= RINGSIZE) { // full
      printf("PRODUCER: ring full\n");
      pthread_cond_wait(&buffer_full, &ring_access);
    }

    buffer[in % RINGSIZE] = rand() / (RAND_MAX / 10);
    printf("in : %i\n", buffer[in % RINGSIZE]);
    in++;
    count++;
    sleep(1);

    pthread_cond_signal(&buffer_empty);
    printf("PRODUCER: unlock\n");
    pthread_mutex_unlock(&ring_access);
  }
}

/**
 Extracts a number from the buffer
 */
void *consumer(void *arg)
{
  //  while (1) {
  //    pthread_mutex_lock(&ring_access);
  //    while (count == 0) {// empty
  //      pthread_cond_wait(&buffer_empty, &ring_access);
  //    }
  //
  //    printf("out : %i\n", buffer[out % RINGSIZE]);
  //    out++;
  //    count--;
  //  sleep(1);
  //
  //    pthread_cond_signal(&buffer_full);
  //    pthread_mutex_unlock(&ring_access);
  //  }
}


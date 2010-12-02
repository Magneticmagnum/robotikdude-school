/**
 * csci4061 F2010 Assignment 4
 * section: one_digit_number
 * login: itlabs_login_name(login used to submit)
 * date: mm/dd/yy
 * names: Brian Norma,
 * ID: 4332223,
 */

#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

// The maximum number of dispatch threads will be 100
#define MAX_DISPATCH   100
// The maximum number of worker threads will be 100
#define MAX_WORKER     100
// The maximum number of prefetcher threads will be 100
#define MAX_PREFETCHER 100
// The maximum size of the cache will be 100 entries
#define MAX_CACHE_SIZE 100
// The maximum length of the request queue will be 100 requests
#define MAX_QUEUE_LEN  100

#define CONTENT_TYPE_HTML    "text/html"
#define CONTENT_TYPE_DEFAULT "text/plain"
#define CONTENT_TYPE_JPG     "images/jpeg"
#define CONTENT_TYPE_GIF     "images/gif"

#define BUFFER_SIZE 1024

typedef struct
{
  int fd;
  char* filename;
} queue_t;

typedef struct
{
  char* request;
  char* result;
} cache_t;

static int mode;

static pthread_mutex_t queue_access = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t queue_full = PTHREAD_COND_INITIALIZER;
static pthread_cond_t queue_empty = PTHREAD_COND_INITIALIZER;
static queue_t queue[MAX_QUEUE_LEN];
static int queue_len;
static int queue_in;
static int queue_out;

static pthread_mutex_t queue_pre_access = PTHREAD_MUTEX_INITIALIZER;
//static pthread_cond_t queue_pre_full = PTHREAD_COND_INITIALIZER;
static pthread_cond_t queue_pre_empty = PTHREAD_COND_INITIALIZER;
static queue_t queue_pre[MAX_QUEUE_LEN];
static int queue_pre_in;
static int queue_pre_out;

static pthread_mutex_t cache_access = PTHREAD_MUTEX_INITIALIZER;
//static pthread_cond_t cache_full = PTHREAD_COND_INITIALIZER;
//static pthread_cond_t cache_empty = PTHREAD_COND_INITIALIZER;
static cache_t cache[MAX_CACHE_SIZE];
static int cache_size;
static int cache_in;
static int cache_out;

// dispatch thread
void* dispatch(void* arg)
{
  while (1) {

    char* file;
    int r;
    int fd = accept_connection();

    if (fd < 0) {
      pthread_exit(NULL);
    }

    file = (char*) malloc(sizeof(char) * BUFFER_SIZE);
    r = get_request(fd, file);
    if (r == 0) {
      pthread_mutex_lock(&queue_access);

      while (queue_in - queue_out >= queue_len) { // queue full
        pthread_cond_wait(&queue_full, &queue_access);
      }
      queue[queue_in % queue_len].fd = fd;
      queue[queue_in % queue_len].filename = file;
      queue_in++;
      pthread_cond_broadcast(&queue_empty); // queue no longer empty

      pthread_mutex_unlock(&queue_access);
    }
    else {
      free(file);
    }
  }
}

// worker thread
void* worker(void* arg)
{
  int threadID = (int)arg;

  while (1) {
    pthread_mutex_lock(&queue_access);

    while (queue_in - queue_out <= 0) { // queue empty
      pthread_cond_wait(&queue_empty, &queue_access);
    }

    queue_t element = queue[queue_out % queue_len];

    if (mode == 2) { // SFF

    }
    else { // CRF and FCFS
      int contains = 0;
      if (mode == 1) { // CRF
        int i;
        int j;
        pthread_mutex_lock(&cache_access);
        // if a match is found, switch that element with the current element
        for (i = queue_out - 1; i >= queue_in && !contains; i--) {
          for (j = cache_out - 1; j >= cache_in && !contains; j--) {
            if (strcmp(queue[i].filename, cache[i].result) == 0) {
              queue_t new_element = queue[i];
              queue[i] = element;
              element = new_element;
              contains = 1;
            }
          }
        }
        pthread_mutex_unlock(&cache_access);
      }
      else {
        int i;
        pthread_mutex_lock(&cache_access);
        for (i = cache_out - 1; i >= cache_in && !contains; i--) {
          if (strcmp(element.filename, cache[i].result) == 0) {
            contains = 1;
          }
        }
        pthread_mutex_unlock(&cache_access);
      }

      // FCFS
      int r;
      // r = return_result(queue[queue_in].fd, char *content_type, char *buf, int numbytes);
      r = return_result(element.fd, NULL, element.filename, BUFFER_SIZE);

      if (queue_pre_in - queue_pre_out < queue_len) {
        queue_pre[queue_pre_in] = element;
        queue_pre_in++;
        pthread_cond_broadcast(&queue_pre_empty); // prefetcher queue no longer empty
      }
      else {
        free(element.filename);
      }
      queue_out++;

      pthread_cond_broadcast(&queue_full); // queue no longer full
    }

    pthread_mutex_unlock(&queue_access);
  }
}

// prefetcher thread
void* prefetcher(void* arg)
{
  while (1) {
    pthread_mutex_lock(&queue_pre_access);

    while (queue_pre_in - queue_pre_out <= 0) { // prefetcher queue is empty
      pthread_cond_wait(&queue_pre_empty, &queue_pre_access);
    }

    queue_t element = queue_pre[queue_pre_out % queue_len];

    char* guess;
    int r;

    r = nextguess(element.filename, guess);

    if (r != 0) {
      pthread_mutex_lock(&cache_access);
      int contains = 0;
      int i;
      for (i = 0; i < cache_size && !contains; i++) {
        if (strcmp(guess, cache[i].result) == 0) {
          contains = 1;
        }
      }
      if (!contains) {
        cache[cache_in % cache_size].request = element.filename;
        cache[cache_in % cache_size].result = guess;
        cache_in++;
      }
      pthread_mutex_unlock(&cache_access);
    }
    queue_pre_out++;

    pthread_mutex_unlock(&queue_pre_access);
  }
}

// web_server_http port path num_dispatch num_workers num_prefetch qlen mode cache_entries
int main(int argc, char** argv)
{
  void usage(char* prog);

  if (argc != 9) {
    usage(argv[0]);
    exit(1);
  }

  int port = atoi(argv[1]);
  if (port < 1025 || port > 65535) {
    printf("USAGE: port must be between 1025 and 65535.");
    usage(argv[0]);
    exit(1);
  }

  char* path = argv[2];
  int nDispatch = atoi(argv[3]);
  int nWorker = atoi(argv[4]);
  int nPrefetch = atoi(argv[5]);
  int queueLength = atoi(argv[6]);
  int opMode = atoi(argv[7]);
  int cacheSize = atoi(argv[8]);

  pthread_t dispathThreads[MAX_DISPATCH];
  pthread_t workerThreads[MAX_WORKER];
  pthread_t prefetchThreads[MAX_PREFETCHER];

  init(port);
  queue_len = queueLength;
  cache_size = cacheSize;
  mode = opMode;

  int i;
  for (i = 0; i < nDispatch; i++) {
    pthread_create(&dispathThreads[i], NULL, dispatch, NULL);
  }

  for (i = 0; i < nWorker; i++) {
    pthread_create(&workerThreads[i], NULL, worker, (void*) (i + 1));
  }

  for (i = 0; i < nPrefetch; i++) {
    pthread_create(&prefetchThreads[i], NULL, prefetcher, NULL);
  }

  for (i = 0; i < nDispatch; i++) {
    pthread_join(dispathThreads[i], NULL);
  }

  for (i = 0; i < nWorker; i++) {
    pthread_join(workerThreads[i], NULL);
  }

  for (i = 0; i < nPrefetch; i++) {
    pthread_join(prefetchThreads[i], NULL);
  }

}

void usage(char* prog)
{
  printf("USAGE: %s <port> <path> <num_dispatch> <num_workers> <num_prefetch>"
    " <qlen> <mode> <cache_entries>\n", prog);
}

/* csci4061 F2010 Assignment 4
 * section: one_digit_number
 * login: norma272
 * date: 11/26/10
 * names: Brian Norman, Chaichana Noree, Joshua Houlton
 * ID:    4332223     , 4295362        , 3688485
 */

#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/stat.h>
#include <signal.h>

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
  int fd; // file descriptor
  char filename[2 * BUFFER_SIZE]; // file name
  int size; // file size
} queue_t;

typedef struct
{
  char request[2 * BUFFER_SIZE]; // file name
  char* result; // file contents
  int size; // file size
} cache_t;

static int mode;
static FILE* log;

static pthread_mutex_t queue_access = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t queue_full = PTHREAD_COND_INITIALIZER;
static pthread_cond_t queue_empty = PTHREAD_COND_INITIALIZER;
static queue_t queue[MAX_QUEUE_LEN];
static int queue_len;
static int queue_in = 0;
static int queue_out = 0;

static pthread_mutex_t queue_pre_access = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t queue_pre_empty = PTHREAD_COND_INITIALIZER;
static queue_t queue_pre[MAX_QUEUE_LEN];
static int queue_pre_in = 0;
static int queue_pre_out = 0;

static pthread_mutex_t cache_access = PTHREAD_MUTEX_INITIALIZER;
static cache_t cache[MAX_CACHE_SIZE];
static int cache_size;
static int cache_in = 0;
static int cache_out = 0;

// ****************************************************************************
// DISPATCH THREAD
// ****************************************************************************
void* dispatch(void* arg)
{
  int threadID = (int) arg;
  char file[2 * BUFFER_SIZE];
  int fd;
  int r;

  while (1) {

    //    printf("Dispatch %i: attempting to accept connection...\n", threadID);
    fd = accept_connection();
    if (fd < 0) {
      printf("Dispatch %i: connection not accepted , exiting.\n", threadID);
      pthread_exit(NULL);
    }
    //    printf("Dispatch %i: connection accepted, fd: %i\n", threadID, fd);

    // append the absolute path before the relative file
    getcwd(file, 2 * BUFFER_SIZE);
    r = get_request(fd, file + strlen(file));
    if (r == 0) {
      //      printf("Dispatch %i: valid request, file: %s\n", threadID, file);

      pthread_mutex_lock(&queue_access);
      //      printf("Dispatch %i: locking queue.\n", threadID);

      while (queue_in - queue_out >= queue_len) { // queue full
        //        printf("Dispatch %i: queue is full.\n", threadID);
        pthread_cond_wait(&queue_full, &queue_access);
      }

      struct stat buffer;
      int status = stat(file, &buffer);
      long long size = buffer.st_size;
      //      printf("Worker %i: getting stat on %s, status: %i, size: %lld.\n",
      //             threadID, element.filename, status, size);

      queue[queue_in % queue_len].fd = fd;
      strcpy(queue[queue_in % queue_len].filename, file);
      queue[queue_in % queue_len].size = size;
      queue_in++;
      //      printf("Dispatch %i: request has been added to the queue.\n", threadID);
      pthread_cond_broadcast(&queue_empty); // queue no longer empty

      //      printf("Dispatch %i: unlocking queue.\n", threadID);
      pthread_mutex_unlock(&queue_access);
    }
    else {
      printf("Dispatch %i: invalid request.\n", threadID);
    }
  }
}

// ****************************************************************************
// WORKER THREAD
// ****************************************************************************
void* worker(void* arg)
{
  int threadID = (int) arg;
  int requestNum = 0;

  while (1) {
    pthread_mutex_lock(&queue_access);
    //    printf("Worker %i: locking queue\n", threadID);

    while (queue_in - queue_out <= 0) { // queue empty
      //      printf("Worker %i: queue is empty.\n", threadID);
      pthread_cond_wait(&queue_empty, &queue_access);
    }

    queue_t element = queue[queue_out % queue_len];
    requestNum++;
    char* bufferCache;
    //    printf("Worker %i: removing request from the queue, fd: %i,"
    //      " filename %s.\n", threadID, element.fd, element.filename);

    int contains = 0;
    if (mode == 2) { // SFF
      //      printf("Worker %i: mode is SSF.\n", threadID);
      // switch the smallest file with the current file
      int i;
      int minIndex = queue_out;
      for (i = queue_in - 1; i > queue_out && !contains; i--) {
        if (queue[i % queue_len].size < queue[minIndex % queue_len].size) {
          minIndex = i;
        }
      }
      queue_t new_element = queue[i % queue_len];
      queue[i % queue_len] = element;
      element = new_element;
    }
    if (mode == 1) { // CRF
      //        printf("Worker %i: mode is CRF.\n", threadID);
      int i;
      int j;
      pthread_mutex_lock(&cache_access);
      //        printf("Worker %i: locking cache\n", threadID);
      // if a match is found, switch that element with the current element
      for (i = queue_in - 1; i >= queue_out && !contains; i--) {
        for (j = cache_in - 1; j >= cache_out && !contains; j--) {
          if (strcmp(queue[i % queue_len].filename,
                     cache[j % cache_size].request) == 0) {
            //            printf("Worker %i: cache contians file, previous: %s.\n", threadID,
            //                   element.filename);
            queue_t new_element = queue[i % queue_len];
            queue[i % queue_len] = element;
            element = new_element;
            contains = 1;
            bufferCache = cache[j % cache_size].result;
            //            printf("Worker %i: cache contians file, new: %s.\n", threadID,
            //                   element.filename);
          }
        }
      }
      //        printf("Worker %i: unlocking cache\n", threadID);
      pthread_mutex_unlock(&cache_access);
    }
    else { // FCFS and SFF
      //        printf("Worker %i: mode is FCFS.\n", threadID);
      int i;
      pthread_mutex_lock(&cache_access);
      //        printf("Worker %i: locking cache\n", threadID);
      for (i = cache_in - 1; i >= cache_out && !contains; i--) {
        if (strcmp(element.filename, cache[i % cache_size].request) == 0) {
          contains = 1;
          bufferCache = cache[i % cache_size].result;
          //          printf("Worker %i: cache contians file: %s.\n", threadID,
          //                 element.filename);
        }
      }
      //        printf("Worker %i: unlocking cache\n", threadID);
      pthread_mutex_unlock(&cache_access);
    }

    // get the content type of the file
    char* contentType;
    char* tempString = (char*) malloc(sizeof(char) * strlen(element.filename));
    strcpy(tempString, element.filename);

    // get last string before .
    char* tokken = strtok(tempString, ".");
    char* lastTokken = NULL;
    while (tokken != NULL) {
      lastTokken = tokken;
      tokken = strtok(NULL, ".");
    }

    if (strcmp(lastTokken, "html") == 0) {
      contentType = CONTENT_TYPE_HTML;
    }
    else if (strcmp(lastTokken, "gif") == 0) {
      contentType = CONTENT_TYPE_GIF;
    }
    else if (strcmp(lastTokken, "jpeg") == 0 || strcmp(lastTokken, "jpg") == 0) {
      contentType = CONTENT_TYPE_JPG;
    }
    else {
      contentType = CONTENT_TYPE_DEFAULT;
    }
    free(tempString);

    //    printf("Worker %i: content type: %s\n", threadID, contentType);

    if (contains) {
      int r = return_result(element.fd, contentType, bufferCache, element.size);
      fprintf(log, "[%i][%i][%i][HIT][%s][%i]\n", threadID, requestNum,
              element.fd, element.filename, element.size);
      printf("[%i][%i][%i][HIT][%s][%i]\n", threadID, requestNum, element.fd,
             element.filename, element.size);
      //      printf("Worker %i: loaded from cache and passed to client, r: %i.\n",
      //             threadID, r);
    }
    else {
      FILE* file = fopen(element.filename, "r");
      if (file != NULL) {
        bufferCache = (char*) malloc(sizeof(char) * element.size);
        fread(bufferCache, sizeof(char), element.size, file);
        //        printf("Worker %i: copying file into buffer.\n", threadID);

        int r = return_result(element.fd, contentType, bufferCache,
                              element.size);
        fprintf(log, "[%i][%i][%i][MISS][%s][%i]\n", threadID, requestNum,
                element.fd, element.filename, element.size);
        printf("[%i][%i][%i][MISS][%s][%i]\n", threadID, requestNum,
               element.fd, element.filename, element.size);
        //        printf("Worker %i: loaded from file and passed to client, r: %i\n",
        //               threadID, r);

        // store in cache
        //      printf("Worker %i: storing web page in the cache.\n", threadID);
        pthread_mutex_lock(&cache_access);
        //        printf("Worker %i: locking cache\n", threadID);
        if (cache_in >= cache_size) {
          //        printf("Worker %i: freeing previous memory in cache\n", threadID);
          free(cache[cache_in % cache_size].result);
        }
        strcpy(cache[cache_in % cache_size].request, element.filename);
        cache[cache_in % cache_size].result = bufferCache;
        cache[cache_in % cache_size].size = element.size;
        cache_in++;
        if (cache_in - cache_out >= cache_size) {
          cache_out++;
        }
        //        printf("Worker %i: unlocking cache\n", threadID);
        pthread_mutex_unlock(&cache_access);
      }
      else {
        char error[BUFFER_SIZE];
        int r = return_error(element.fd, error);
        fprintf(log, "[%i][%i][%i][MISS][%s][%s]\n", threadID, requestNum,
                element.fd, element.filename, error);
        printf("[%i][%i][%i][MISS][%s][%s]\n", threadID, requestNum,
               element.fd, element.filename, error);
        //        printf("Worker %i: error opening, file: %s, r: %i\n", threadID,
        //               element.filename, r);
      }
    }

    queue_out++;

    pthread_mutex_lock(&queue_pre_access);
    //      printf("Worker %i: locking prefetcher queue\n", threadID);
    if (queue_pre_in - queue_pre_out < queue_len) {
      //        printf("Worker %i: adding element to the prefetcher queue.\n", threadID);
      queue_pre[queue_pre_in % MAX_QUEUE_LEN].fd = element.fd;
      strcpy(queue_pre[queue_pre_in % MAX_QUEUE_LEN].filename, element.filename);
      queue_pre[queue_pre_in % MAX_QUEUE_LEN].size = element.size;
      queue_pre_in++;
      pthread_cond_broadcast(&queue_pre_empty); // prefetcher queue no longer empty
    }
    else {
      //        printf("Worker %i: prefetcher thread is full.\n", threadID);
    }
    //      printf("Worker %i: unlocking prefetcher queue\n", threadID);
    pthread_mutex_unlock(&queue_pre_access);

    pthread_cond_broadcast(&queue_full); // queue no longer full

    //    printf("Worker %i: unlocking queue\n", threadID);
    pthread_mutex_unlock(&queue_access);
  }
}

// ****************************************************************************
// PREFETCHER THREAD
// ****************************************************************************
void* prefetcher(void* arg)
{
  int threadID = (int) arg;

  while (1) {
    pthread_mutex_lock(&queue_pre_access);
    //    printf("Prefetcher %i: locking prefetcher queue\n", threadID);

    while (queue_pre_in - queue_pre_out <= 0) { // prefetcher queue is empty
      //      printf("Prefetcher %i: prefetcher queue is empty\n", threadID);
      pthread_cond_wait(&queue_pre_empty, &queue_pre_access);
    }

    queue_t element = queue_pre[queue_pre_out % queue_len];

    char guess[2 * BUFFER_SIZE];
    int r;

    getcwd(guess, 2 * BUFFER_SIZE);
    r = nextguess(element.filename, guess + strlen(guess));

    if (r != 0) {
      pthread_mutex_lock(&cache_access);
      //      printf("Prefetcher %i: locking cache\n", threadID);
      int contains = 0;
      int i;
      for (i = cache_in - 1; i >= cache_out && !contains; i--) {
        if (strcmp(guess, cache[i % cache_size].request) == 0) {
          contains = 1;
        }
      }
      if (!contains) {
        if (cache_in >= cache_size) {
          //          printf("Prefetcher %i: freeing previous memory in cache\n", threadID);
          free(cache[cache_in % cache_size].result);
        }

        FILE* file = fopen(element.filename, "r");
        if (file != NULL) {
          char* bufferCache = (char*) malloc(sizeof(char) * element.size);
          fread(bufferCache, sizeof(char), element.size, file);
          //          printf("Prefetcher %i: copying file into buffer.\n", threadID);

          strcpy(cache[cache_in % cache_size].request, element.filename);
          cache[cache_in % cache_size].result = bufferCache;
          cache[cache_in % cache_size].size = element.size;
          cache_in++;
          if (cache_in - cache_out >= cache_size) {
            cache_out++;
          }
        }
        else {
          printf("Prefetcher %i: error opening, file: %s, r: %i\n", threadID,
                 element.filename, r);
        }
      }
      else {
        //        printf("Prefetcher %i: cache already contians file: %s.\n", threadID,
        //               element.filename);
      }
      //      printf("Prefetcher %i: unlocking cache\n", threadID);
      pthread_mutex_unlock(&cache_access);
    }
    queue_pre_out++;

    //    printf("Prefetcher %i: unlocking prefetcher queue\n", threadID);
    pthread_mutex_unlock(&queue_pre_access);
  }
}

void catchClose()
{
  //  printf("Main: Closing log file.\n");
  fclose(log);
  exit(0);
}

// ****************************************************************************
// MAIN THREAD
// ****************************************************************************
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
    printf("USAGE: <port> must be between 1025 and 65535.");
    usage(argv[0]);
    exit(1);
  }

  char* path = argv[2];
  // check directory path

  int nDispatch = atoi(argv[3]);
  if (nDispatch <= 0 || nDispatch > MAX_DISPATCH) {
    printf("USAGE: <num_dispatch> must be between 1 and %i.", MAX_DISPATCH);
    usage(argv[0]);
    exit(1);
  }

  int nWorker = atoi(argv[4]);
  if (nWorker <= 0 || nWorker > MAX_WORKER) {
    printf("USAGE: <num_worker> must be between 1 and %i.", MAX_WORKER);
    usage(argv[0]);
    exit(1);
  }

  int nPrefetch = atoi(argv[5]);
  if (nPrefetch <= 0 || nPrefetch > MAX_PREFETCHER) {
    printf("USAGE: <num_prefetch> must be between 1 and %i.", MAX_PREFETCHER);
    usage(argv[0]);
    exit(1);
  }

  int queueLength = atoi(argv[6]);
  if (queueLength <= 0 || queueLength > MAX_QUEUE_LEN) {
    printf("USAGE: <qlen> must be between 1 and %i.", MAX_QUEUE_LEN);
    usage(argv[0]);
    exit(1);
  }

  int opMode = atoi(argv[7]);
  if (opMode < 0 || opMode > 3) {
    printf("USAGE: <mode> must be 0 (FCFS), 1 (CRF), or 3 (SFF).");
    usage(argv[0]);
    exit(1);
  }

  int cacheSize = atoi(argv[8]);
  if (cacheSize <= 0 || cacheSize > MAX_CACHE_SIZE) {
    printf("USAGE: <cache_entries> must be between 1 and %i.", MAX_CACHE_SIZE);
    usage(argv[0]);
    exit(1);
  }

  log = fopen("web_server.log", "w");
  if (log == NULL) {
    printf("ERROR: unable to open log file web_server.log.\n");
    exit(1);
  }
  //  printf("Main: Opening log file.\n");
  struct sigaction action;
  action.sa_handler = catchClose;
  sigaction(SIGINT, &action, NULL);

  pthread_t dispathThreads[MAX_DISPATCH];
  pthread_t workerThreads[MAX_WORKER];
  pthread_t prefetchThreads[MAX_PREFETCHER];

  chdir(path);

  init(port);

  queue_len = queueLength;
  cache_size = cacheSize;
  mode = opMode;

  int i;
  //  printf("Creating dispatch threads...\n");
  for (i = 0; i < nDispatch; i++) {
    pthread_create(&dispathThreads[i], NULL, dispatch, (void*) (i + 1));
    //    printf("Dispatch thread number %i created.\n", i + 1);
  }

  //  printf("Creating worker threads...\n");
  for (i = 0; i < nWorker; i++) {
    pthread_create(&workerThreads[i], NULL, worker, (void*) (i + 1));
    //    printf("Worker thread number %i created.\n", i + 1);
  }

  //  printf("Creating prefetch threads...\n");
  for (i = 0; i < nPrefetch; i++) {
    pthread_create(&prefetchThreads[i], NULL, prefetcher, (void*) (i + 1));
    //    printf("Dispatch thread number %i created.\n", i + 1);
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

  return 0;
}

void usage(char* prog)
{
  printf("USAGE: %s <port> <path> <num_dispatch> <num_workers> <num_prefetch>"
    " <qlen> <mode> <cache_entries>\n", prog);
}

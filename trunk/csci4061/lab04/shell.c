#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include "makeargv.h"

#define MAX_INPUT 1024

void printPrompt()
{
  printf("> ");
}

int main(int argc, char **argv)
{

  char input[MAX_INPUT];
  char** argv_new;
  int argc_new;

  while (1) {
    printPrompt();

    fgets(input, MAX_INPUT - 1, stdin);

    int i = 0;
    while (i < MAX_INPUT && input[i] != '\n')
      i++;
    if (i != MAX_INPUT) {
      input[i] = '\0';
    }
    else {
      printf("ERROR - Input overflow. Could not read all of the command.");
    }

    argc_new = makeargv(input, " ", &argv_new);

    if (argc_new > 0) {
      if (strcmp(argv_new[0], "exit") == 0) {
        return 0;
      }
      else {
        int status = 0;

        pid_t pid = fork();
        if (pid == 0) {
          // child
          char* last = argv_new[argc_new - 1];
          int i;
          for (i = 0; last[i] != '\0'; i++) {
            if (last[i] == '&') {
              last[i] = '\0';
              i--;
            }
          }

          execvp(argv_new[0], argv_new);
          printf("ERROR - Unable to run the following command: %s\n",
                 argv_new[0]);
          freemakeargv(argv_new);
          return 0;
        }
        else {
          // parent
          if (strchr(argv_new[argc_new - 1], '&') == NULL) {
            wait(&status);
          }
          freemakeargv(argv_new);
        }
      }
    }
  }
}

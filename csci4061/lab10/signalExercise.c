#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

//signal IO handler
void catchIO()
{
  printf("Child caught SIGIO\n");
  //open file and print out the contents
}

int main()
{
  pid_t pid = fork();
  if (pid == 0) { //child
    //define sigaction and signal handler
    struct sigaction action;
    action.sa_handler = catchIO;
    sigaction(SIGIO, &action, NULL);

    //wait for SIGIO
    pause();

  }
  else if (pid > 0) { //parent
    //open up a file and write something to it
    FILE* file = fopen("temp.txt", "w");
    fprintf(file, "This is the parent writing to the file");

    //send SIGIO signal to child
    kill(pid, SIGIO);

  }
  else {//error
    perror("fork");
  }
}


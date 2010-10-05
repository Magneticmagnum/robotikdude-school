#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>

#define BUFFER_SIZE 256

int main(int argc, char ** argv)
{
  if (argc != 4) {
    printf("usage: filemerge inputFile1 inputFile2 mergedFile\n");
    exit(1);
  }

  FILE* f1;
  FILE* f2;
  FILE* f3;
  char* ln1;
  char* ln2;
  char buff1[BUFFER_SIZE];
  char buff2[BUFFER_SIZE];

  //open 3 files for read and write
  //add your code here

  f1 = fopen(argv[1], "r");
  f2 = fopen(argv[2], "r");
  f3 = fopen(argv[3], "w");

  //start to merge file, when both files have contents
  //add your code here

  int bothFiles = 1;
  if ((ln1 = fgets(buff1, BUFFER_SIZE - 1, f1)) == NULL) {
    bothFiles = 0;
  }
  if ((ln2 = fgets(buff2, BUFFER_SIZE - 1, f2)) == NULL) {
    bothFiles = 0;
  }
  while (bothFiles) {
    if (strcmp(ln1, ln2) > 0) {
      // buff2 smaller
      fputs(ln2, f3);
      if ((ln2 = fgets(buff2, BUFFER_SIZE - 1, f2)) == NULL) {
        bothFiles = 0;
      }
    }
    else {
      // buff1 smaller
      fputs(ln1, f3);
      if ((ln1 = fgets(buff1, BUFFER_SIZE - 1, f1)) == NULL) {
        bothFiles = 0;
      }
    }
  }

  //when only one file has contents left
  //add your code here

  if (ln2 == NULL) {
    fputs(ln1, f3);
    while ((ln1 = fgets(buff1, BUFFER_SIZE - 1, f1)) != NULL) {
      fputs(ln1, f3);
    }
  }
  else {
    fputs(ln2, f3);
    while ((ln2 = fgets(buff2, BUFFER_SIZE - 1, f2)) != NULL) {
      fputs(ln2, f3);
    }
  }


  //close all files
  //add your code here

  fclose(f1);
  fclose(f2);
  fclose(f3);

  return 0;
}

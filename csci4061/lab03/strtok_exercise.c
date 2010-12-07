#include <stdio.h>
#include <string.h>


int main(int argc, char **argv) {


   char input[1024];

   // read a line of standard input. use fgets() - use "man fgets" for reference
   // the "stream" to read from is standard input, 'stdin'
   // read 1023 characters into 'input'.

   fgets(input, 1023, stdin);

   // now use strtok() and some temporary pointers to print out each word
   // on a separate line. (use printf("%s\n",word_ptr); to print a word);

   char* string;

   printf("Input words are...\n");
   printf("%s", strtok(input, " "));
   while ((string = strtok(NULL, " ")) != NULL) {
     printf("\n%s", string);
   }

   return 0;
}

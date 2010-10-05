#include <stdio.h>
#include <string.h>
#include "makeargv.h"

int main(int argc, char **argv) {

   char input[1024];

   // use fgets to get the input again.

   fgets(input, 1023, stdin);

   // now use makeargv() to parse the strings for you instead of strtok()!
   // you need to define your own double-pointer and then pass the address-of it.(&)

   char** argv_new;
   int argc_new = makeargv(input, " ", &argv_new);

   // now iterate over the list of strings to print them out!

   int i;

   printf("Argument variables are...");
   for (i = 0; i < argc_new; i++) {
     printf("\n%s", argv_new[i]);
   }

   free(argv_new);

   return 0;
}

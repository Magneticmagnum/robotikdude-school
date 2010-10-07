#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/**
 * A simple program that reads the user's input and returns
 * the line count, word count and character count.
 */
int main()
{
   char ch;                 // The current character being read
   int in_word = 0;         // Flag: in word or not
   
   int line_count = 0;      // The current line count
   int word_count = 0;      // The current word count
   int char_count = 0;      // The current character count
   
   printf("Please enter some text. CTRL + Z, ENTER on a new line to exit.\n");
   
   while ((ch = getchar()) != EOF) {
      char_count++;
      
      if (!isspace(ch))
         in_word = 1;       // in a word
      else if (in_word) {   // (isspace(ch) && in_word)
         word_count++;      // just exited a word
         in_word = 0;
      }
      
      if (ch == '\n')
         line_count++;
   }

   printf("Character count: %i, Word count: %i, Line count: %i.\n", 
                     char_count, word_count, line_count);
  
   printf("Press ENTER to continue...");
   getchar();
   return EXIT_SUCCESS;
}

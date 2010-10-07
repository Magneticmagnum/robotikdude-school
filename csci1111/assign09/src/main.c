#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGTH 15 // CONST: maximum length of a string

/*
 * A simple program that removes a single user inputed character from
 * a inputed string.
 * RETURNS:
 *    int - EXIT_SUCCESS (0)
 */
int main()
{
   char * rmchr(char *, char);
   int prompt(char *, int, char *);

   char string[MAX_STRING_LENGTH + 1]; // Input: user defined string
   char character;                     // Input: user defined char to remove

   printf("Enter: CTRL + Z, ENTER to exit.\n");
   while (prompt(string, MAX_STRING_LENGTH, &character) == 2)
   {
      printf("Before: %s\n", string);
      rmchr(string, character);
      printf("After:  %s\n", string);
   }

   return EXIT_SUCCESS;
}

/*
 * Edits the passed string by revoming the passed character then
 * returns string. A new string will NOT be created but the original
 * string will be edited.
 * PARAMETERS:
 *    char * string    - string to be edited
 *    char   character - character to remove
 * RETURNS:
 *    char* - the string that was edited
 */
char * rmchr(char * string, char character)
{
   if (character != '\0')
   {
      char * endptr = string + strlen(string); // Pointer: end of the string
      char * destptr, * srcptr;              // Pointers: destination and source
      for (destptr = srcptr = string; srcptr <= endptr; destptr++, srcptr++)
      {
         while (*srcptr == character)
            srcptr++;
         *destptr = *srcptr;
      }
   }
   return string;
}

/*
 * Prompts the user for a string and single character. The string may
 * only be be as long as MAX_STRING_LENGTH. EOF will be returned if
 * the end of the file is reached.
 * PARAMETERS:
 *    char * const string     - address where inputed string will be stored
 *    int          max_length - max length of inputed string
 *    char *       character  - address where inputed character will be stored
 * RETURNS:
 *    int - number of currectly entered varibles or EOF
 */
int prompt(char * const string, int max_length, char * character)
{
   int inString(char * const, int);

   int error_check; // Flag: if there was an error reading the user's input
   
   printf("Please enter a string with a max of %i characters: ", max_length);
   error_check = inString(string, max_length);
   if (error_check != EOF)
   {
      printf("Please enter a character to remove from the above string: ");
      *character = getchar();

      if (*character != EOF)
      {
         error_check++;
         if (*character == '\n')
            printf("Warning! No characters entered!\n");
         else if (getchar() != '\n')
         {
            while (getchar() != '\n')
               ;
            printf("Warning! Only using one character: %c.\n", *character);
         }
      }
      else
         error_check = EOF;
   }
   return error_check;
}

/*
 * Inputs a string with the given maximum length.
 * PARAMETERS:
 *    char * const string     - address where inputed string will be stored
 *    int          max_length - max length of inputed string
 * RETURNS:
 *    int - 1 if successful in inputing string, EOF otherwise.
 */
int inString(char * const string, int max_length)
{
   char * strptr = string;                // Pointer: current position in string
   const char * const endptr = string + max_length; // Pointer: end of string
   char c;                    // Input: current character in user inputed string
   int char_count = 0;   // Counter: number of characters in user inputed string

   while ((c = getchar()) != '\n' && c != EOF)
   {
      if (strptr < endptr)
         *strptr++ = c;
      char_count++;
   }
   *strptr = '\0';

   if (char_count > max_length)
      printf("Warning! String to long, cropped to: %s.\n", string);
   return (c == EOF ? EOF : 1);
}

#include <stdio.h>
#include <stdlib.h>

/**
 * A simple program that prompts the user for a test score
 * on the range of 0 to 10, and then returns the coresponding 
 * grade. Continues to prompt the user until EOF is incountered.
 */
int main()
{
   void printGrade(char);
   char getGrade(int);
   
   int failCheck = 0;  // FLAG: if scanf was seccessful
   int score;          // User Input: the test score
   
   printf("Type CTRL + Z, ENTER to exit.\n");
   
   while ((printf("Please enter test score: "),
           failCheck = scanf("%i", &score)) != EOF)
   {
      if (failCheck == 0)             // Non-numerical input
      {
         printf("ERROR: Score not an number,"
                               " enter score on a range of 0 to 10.\n");
         while (getchar() != '\n')    // Flush user input
            ;
      }
      else if (score > 10)            // Test score to high
         printf("ERROR: Score to large, enter score on a range of 0 to 10.\n");
      else if (score < 0)             // Test score to low
         printf("ERROR: Score to small, enter score on a range of 0 to 10.\n");
      else                            // Test score just right...
         printGrade(getGrade(score));
   }
   
   return EXIT_SUCCESS;
}

/**
 * A simple function that prints the grade of a test score.
 */
void printGrade(char grade)
{
   printf("Grade of %c.\n", grade);
}

/**
 * A simple function that returns the grade of a test scare.
 */
char getGrade(int score)
{
   char grade;  // The grade that the test score will recive
   switch (score) {
      case 10 :
      case  9 :
         grade = 'A';
         break;
      case  8 :
         grade = 'B';
         break;
      case  7 :
         grade = 'C';
         break;
      case  6 :
         grade = 'D';
         break;
      default :
         grade = 'F';
   }
   return grade;
}

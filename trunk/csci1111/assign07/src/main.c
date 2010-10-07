#include <stdio.h>
#include <stdlib.h>

#define MAX_VALUES 10     // Const: The maximum amount of numbers in the array

/*
 * A simple program that prompts the user for a list of 
 * numbers, reprints the list, sorts them ascending based on
 * the order that the user entered them and then prints the
 * array a second time.
 * RETURNS:
 *   int - EXIT_SUCCESS (0)
 */
int main()
{
   int fill(int a[], int);
   void print(const int a[], int);
   void sortAscending(int a[], int);
   
   int array[MAX_VALUES]; // Input: The array that the user will fill
   int length;            // Input: The number of elements in the users array
   
   length = fill(array, MAX_VALUES);

   if (length > 0)
   {
      printf("Array before sorting...\n");
      print(array, length);

      sortAscending(array, length);

      printf("Array after sorting!\n");
      print(array, length);
   }
   else
   {
      printf("ERROR: No numbers were entered.\n");
   }

   printf("Press ENTER to continue...");
   getchar();
   return EXIT_SUCCESS;
}

/*
 * Fills the given array with inputed numbers from the user.
 * Will continue until EOF or the array is full and will 
 * return the number of correctly read numbers.
 * PARAMETERS:
 *   int array[]   - the array to be filled
 *   int maxLength - the maximum number of numbers to read
 * RETURNS:
 *   int - the number of numbers that were correctly read
 */
int fill(int array[], int maxLength)
{
   int value;             // Input: the current user inputed number
   int errorCheck;        // Flag: if reading of the number was successful
   int index = 0;         // Counter: current index in the array

   printf("Please enter numbers that you would like to fill the array with,\n");
   printf("each number on a new line.\n");
   printf("Enter CTRL + Z, ENTER, when you are finished.\n");
   
   while ((errorCheck = scanf("%i", &value)) != EOF && index < maxLength)
   {
      if (errorCheck == 0)
      {
         printf("ERROR: Input must be a number\n");
         while (getchar() != '\n')
            ;
      }
      else
         array[index++] = value;
   }
   
   if (errorCheck == 1)   // a value was read, but the array is full
   {
      printf("ERROR: Array is full, could not add input.\n");
      while (getchar() != '\n')
         ;
   }
   
   return index;
}

/*
 * Prints an array starting with the first element and 
 * continuing to the last element.
 * PARAMETERS:
 *   int array[] - the array the will be printed
 *   int length  - the length of the array
 */
void print(const int array[], int length)
{
   int i;
   for (i = 0; i < length; i++)
      printf("%i, ", array[i]);
   printf("\n");
}

/*
 * Sorts, ascending, the elements in an array.
 * PARAMETERS:
 *   int array[] - the array that will be sorted
 *   int length  - the length of the array
 */
void sortAscending(int array[], int length)
{
   void swap(int a[], int, int);

   int i;
   for (i = 0; i < (length - 1); i++)
   {
      int min = array[i];
      int minIndex = i;
      int j;
      for (j = i + 1; j < length; j++)
      {
         if (array[j] < min)
         {
            min = array[j];
            minIndex = j;
         }
      }
      swap(array, i, minIndex);
   }
}

/*
 * A simple function that swaps two elements in an array.
 * PARAMETERS:
 *   int array[] - the array in which the elements will be swapped
 *   int index1  - the index of the first element
 *   int index2  - the index of the second element
 */
void swap(int array[], int index1, int index2)
{
   int temp = array[index1];
   array[index1] = array[index2];
   array[index2] = temp;
}

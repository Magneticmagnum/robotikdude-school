#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH      10    // Const: the maximum length of an array
#define SENTINAL       -999   // Const: the sentinal value for entering an array
#define NO_DIFFERENCE  -1     // Const: returned if no defference between arrays

/**
 * A simple program that propmts the user for two lists, reprints the
 * two lists then prints the index at which these two arrays differ.
 * RETURNS:
 *   int - EXIT_SUCCESS (0)
 */
int main()
{
	int fill(int a[], int, int);
	void print(const int a[], int);
	int diff(const int a[], int, const int b[], int);

	int array1[MAX_LENGTH]; // Input: the first user entered array
	int length1; // Input: the length of the first user entered array

	int array2[MAX_LENGTH]; // Input: the second user entered array
	int length2; // Input: the length of the second user entered array

	int index_diff; // the index at which the two user entered arrays differ

	length1 = fill(array1, MAX_LENGTH, SENTINAL);
	length2 = fill(array2, MAX_LENGTH, SENTINAL);

	printf("User array number 1: ");
	print(array1, length1);
	printf("User array number 2: ");
	print(array2, length2);

	index_diff = diff(array1, length1, array2, length2);

	if (index_diff == NO_DIFFERENCE)
		printf("The two arrays do not differ.\n");
	else
		printf("The two arrays differ at index %i.\n", index_diff);

	printf("Press ENTER to continue...");
	getchar();

	return EXIT_SUCCESS;
}

/**
 * Returns the index at which two arrays differ. If the two arrays are
 * of not of uniform size and do not differ until the end of one array
 * is reached, then the index at which the shorter of two arrays would
 * be exited is returned.
 * PARAMETERS:
 *   const int array1[] - the first array
 *   int       length1  - the length of the first array
 *   const int array2[] - the first array
 *   int       length2  - the length of the first array
 * RETURNS:
 *   int - index at which two arrays differ
 */
int diff(const int array1[], int length1, const int array2[], int length2)
{
	const int * const endptr1 = array1 + length1; // Pointer: end of array 1
	const int * const endptr2 = array2 + length2; // Pointer: end of array 2
	const int * ptr1 = array1; // Pointer: current position in array 1
	const int * ptr2 = array2; // Pointer: current position in array 2

	while (ptr1 < endptr1 && ptr2 < endptr2 && *ptr1 == *ptr2)
	{
		ptr1++;
		ptr2++;
	}

	if (ptr1 == endptr1 && ptr2 == endptr2)
		return NO_DIFFERENCE;
	else
		return ptr1 - array1;
}

/**
 * Fills the given array with inputed numbers from the user. Will
 * continue until EOF, the given sentinal value or the array is full
 * and will return the number of correctly read numbers.
 * PARAMETERS:
 *   int array[]   - the array to be filled
 *   int maxLength - the maximum number of numbers to read
 * RETURNS:
 *   int - the number of numbers that were correctly read
 */
int fill(int array[], const int maxLength, const int sentinal)
{
	const int * const endptr = array + maxLength; // Pointer: end of the array
	int * ptr = array; // Pointer: the current position in the array
	int value; // Input: the current user entered number
	int errorCheck; // Flag: if reading of the number was successful

	printf("Please enter numbers that you would like to fill the array with.\n");
	printf("Enter %i, when you are finished.\n", sentinal);

	while ((errorCheck = scanf("%i", &value)) != EOF && ptr < endptr && value
			!= sentinal)
	{
		if (errorCheck == 0)
		{
			printf("ERROR: Input must be a number\n");
			while (getchar() != '\n')
				;
		}
		else
			*ptr++ = value;
	}

	if (errorCheck == 1)
	{ // a value was read...
		if (ptr == endptr && value != sentinal)
		{ // ...but the array is full
			printf("ERROR: Array is full, could not add input.\n");
			while (getchar() != '\n')
				;
		}
		else if (value == sentinal)
		{ // ...but it was the sentinal value
			while (getchar() != '\n')
				;
		}
	}

	return ptr - array;
}

/**
 * Prints an array starting with the first element and  continuing to
 * the last element.
 * PARAMETERS:
 *   const int array[] - the array the will be printed
 *   int       length  - the length of the array
 */
void print(const int array[], int length)
{
	const int * const endptr = array + length; // Pointer: the end of the array
	const int * ptr = array; // Pointer: current position in the array

	while (ptr < endptr)
	{
		printf("%i", *ptr++);
		if (ptr != endptr)
			printf(", ");
	}
	printf("\n");
}

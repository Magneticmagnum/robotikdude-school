#include <stdio.h>
#include <stdlib.h>

/**
 * A program that will prompt the user for two value of int
 * type and will calculate the sum of those two numbers and
 * all whole numbers between.
 */
int main()
{
    int calculateSum(int, int);
    void printSum(int, int, int);
    
    int start;     // The starting number.
    int end;       // The ending number.
    int sum;       // The resulting sum.
    
    printf("Enter two values to calculate the sum of those numbers\n"
           "and all the whole numbers between.\n");
    printf("The smaller number: ");
    scanf("%i/n", &start);
    printf("The larger number: ");
    scanf("%i/n", &end);
    
    while (start >= end) {
        // There was an error! User entered invalid numbers, must reenter.
        if (start > end)
            printf("ERROR! First value must be smaller then second.\n");
        else
            printf("ERROR! First value can not be equal to the second.\n");
        printf("The smaller number: ");
        scanf("%i/n", &start);
        printf("The larger number: ");
        scanf("%i/n", &end);
    }
    
    sum = calculateSum(start, end);
    printSum(start, end, sum);
    
    printf("Press Enter to continue...\n");
    getchar();
    return EXIT_SUCCESS;
}

/**
 * A simple function to calculate the sum of two numbers and
 * all whole numbers between.
 */
int calculateSum(int start, int end)
{
    int sum = 0;   // The sum of the calculation.
    
    // Starting at 'start', this for loop will add each whole
    // to 'sum' number until it reaches a number that is
    // greater then 'end'.
    for (; start <= end; start = start + 1)
        sum = sum + start;
    return sum;
}

/**
 * Another simple function to print two values and the sum
 * of those numbers and all whole numbers between them.
 */
void printSum(int start, int end, int sum)
{
     printf("The sum of all whole numbers between %i and %i"
                 " inclusively is %i.\n", start, end, sum);
}

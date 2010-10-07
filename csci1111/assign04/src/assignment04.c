#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
 * A simple function that will evaluate a quadratic polynomial
 * in the form: a*x^2 + b*x + c, and return the zeros (the
 * numbers that make a polynomial zero)
 */
int main()
{
    double discriminant(double, double, double);

    double  a;           // The 'a' part of the quadratic polynomial
    double  b;           // The 'b' part of the quadratic polynomial
    double  c;           // The 'c' part of the quadratic polynomial
    double  disc;        // The discriminant of the quadratic polynomial
    int     failCheck;   // Flag

    a = 0.0;
    b = 0.0;
    c = 0.0;

    failCheck = 0;
    printf("Please enter the 'a', 'b' and 'c' part a quadratic polynomeal.\n");
    printf("Enter 'a': ");
    failCheck += scanf("%lf", &a);
    while (getchar() != '\n') ;    // Flush input
    printf("Enter 'b': ");
    failCheck += scanf("%lf", &b);
    while (getchar() != '\n') ;    // Flush input
    printf("Enter 'c': ");
    failCheck += scanf("%lf", &c);
    while (getchar() != '\n') ;    // Flush input

    while (failCheck == 3)
    {

        disc = discriminant(a, b, c);

        if (a != 0.0)
        {
            if (disc < 0.0)
            {
                double roots_partA;   // The 'a' part of: a (+-) b*i
                double roots_partBi;  // The 'b' part of: a (+-) b*i

                roots_partA = (-b) / (2.0 * a);
                roots_partBi = abs(sqrt(abs(disc)) / (2.0 * a));

                if (a < 0.0)
                    printf("The roots are: %.1f - %.1fi and %.1f + %.1fi.\n",
                                roots_partA, roots_partBi,
                                roots_partA, roots_partBi);
                else
                    printf("The roots are: %.1f + %.1fi and %.1f - %.1fi.\n",
                                roots_partA, roots_partBi,
                                roots_partA, roots_partBi);
            }
            else
            {
                double root1;   // The first root
                double root2;   // The second root

                root1 = ((-b) + sqrt(disc)) / (2.0 * a);
                root2 = ((-b) - sqrt(disc)) / (2.0 * a);

                printf("The roots are: %.1f and %.1f.\n", root1, root2);
            }
        }
        else if (b != 0.0)   // a == 0.0
        {
            double root;
            root = (-c) / b;
            printf("The only root is: %.1f.\n", root);
        }
        else                 // a == b == 0.0
        {
            if (c != 0.0)
                printf("There are no solutions.\n");
            else             // a == b == c == 0.0
                printf("There are an infinite amount of roots.\n");
        }

        failCheck = 0;
        printf("Please enter the 'a', 'b' and 'c' part a"
                       " quadratic polynomeal.\n");
        printf("Enter 'a': ");
        failCheck += scanf("%lf", &a);
        while (getchar() != '\n') ;    // Flush input
        printf("Enter 'b': ");
        failCheck += scanf("%lf", &b);
        while (getchar() != '\n') ;    // Flush input
        printf("Enter 'c': ");
        failCheck += scanf("%lf", &c);
        while (getchar() != '\n') ;    // Flush input
    }

    if (failCheck != 3)
       printf("INPUT ERROR - program terminated...\n");
    printf("Press ENTER to continue...\n");
    getchar();
    return EXIT_SUCCESS;
}

/**
 * A simple function that returns the discriminant of the quadratic
 * function (b^2 - 4*a*c).
 */
double discriminant(double a, double b, double c)
{
    return ((b * b) - 4 * a * c);
}

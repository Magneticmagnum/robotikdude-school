/*
 * A simple program that prints out a list of employees. Although this list as
 * been harded into the program, it may be edited at anytime and the program
 * will print out all employees accordingly.
 */

#include <stdlib.h>
#include <stdio.h>

#define AREA_CODE_LENGTH   4    // Const: max length of the area code
#define LOCAL_CODE_LENGTH  4    // Const: max length of the local code
#define FINAL_CODE_LENGTH  5    // Const: max length of the final digits
#define MAX_NAME_LENGTH    40   // Const: max length of an employee's name

/*
 * A structure that contains a phone number in the form of strings to maintain
 * leading zeors.
 */
struct telephone
{
   char area[AREA_CODE_LENGTH]; // String: three digit area code
   char local[LOCAL_CODE_LENGTH]; // String: three didgit local code
   char final[FINAL_CODE_LENGTH]; // String: four digit final code
};

/*
 * A structure that contains information about an employee: ID number, 
 * Name (last, first), telephone number, and age.
 */
struct employee
{
   int id_number;                  // int: employee's ID number
   char name[MAX_NAME_LENGTH + 1]; // char: employee's name (last, first)
   struct telephone phone_number;  // Struct: employee's phone number
   int age;                        // int: employee's age
};

int main()
{
   void printEmployees(const struct employee*, int);
   void printEmployees2(const struct employee a[], int);

   const struct employee employees[] =
   {             // Const Struct: the list of employees
      { 314159, "Eirkson, Joy", { "763", "659", "8374" }, 34 },
      { 271828, "Davis, Joe",   { "612", "384", "9274" }, 22 },
      { 141421, "Lee, Albert",  { "612", "384", "4260" }, 18 },
      { 173205, "Morris, Dan",  { "763", "972", "0831" }, 24 }
   };

   printf("Printed with pointers:\n");
   printEmployees(employees, sizeof(employees) / sizeof(struct employee));
   printf("\n");
   printf("Printed with an array:\n");
   printEmployees2(employees, sizeof(employees) / sizeof(struct employee));

   printf("Press ENTER to continue...\n");
   getchar();

   return EXIT_SUCCESS;
}

/*
 * Prints an list of employees using pointers.
 * PARAMETERS:
 *    const struct employee * employees - pointer to the first employee 
 *    int                     length    - number of employees
 */
void printEmployees(const struct employee * empptr, int length)
{
   const struct employee * const endptr = empptr + length;//Pointer: end of list

   while (empptr < endptr)
   {
      printf("Employee:\n");
      printf("   Name:         %s\n", empptr->name);
      printf("   Phone Number: (%s) %s-%s\n", empptr->phone_number.area,
            empptr->phone_number.local, empptr->phone_number.final);
      empptr++;
   }
}

/*
 * Prints an array of employees using array subscript.
 * PARAMETERS:
 *    const struct employee employees[] - the array of employees
 *    int                   length      - length of the array of employees
 */
void printEmployees2(const struct employee employees[], int length)
{
   int i;
   for (i = 0; i < length; i++)
   {
      printf("Employee:\n");
      printf("   Name:         %s\n", employees[i].name);
      printf("   Phone Number: (%s) %s-%s\n", employees[i].phone_number.area,
            employees[i].phone_number.local, employees[i].phone_number.final);
   }
}

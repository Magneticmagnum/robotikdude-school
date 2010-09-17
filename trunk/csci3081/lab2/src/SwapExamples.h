#ifndef SWAPEXAMPLES_H
#define SWAPEXAMPLES_H

using namespace std;

/**
 * This class contains various utility methods for different types of swapping.
 *
 * When using this class, an instance of it should never be created. All the methods
 * contained can be used statically without an instance.
 *
 * @author Brian Norman
 * @author Benjamin Kett
 *
 * @date 20100917
 */
class SwapExamples {
public:

	/**
	 * Swaps the value of x and y.
	 */
	static void SwapA(int & x, int & y);

	/**
	 * Swaps the values that x and y point at. Does not change the location x
	 * and y point at.
	 */
	static void SwapB(int **x, int **y);

	/**
	 * Swaps the location that x and y point at.
	 */
	static void SwapC(int* &x, int* &y);

	/**
	 * Swaps the values x and y point at. Does not change the location x and y
	 * point at.
	 */
	static void SwapD(int *x, int *y);

};

#endif /*SWAPEXAMPLES_H*/

#include "SwapExamples.h"

void SwapExamples::SwapA(int &x, int &y) {
	int temp;
	temp = x;
	x = y;
	y = temp;
}

void SwapExamples::SwapB(int **x, int **y) {
	int temp;
	temp = **x;
	**x = **y;
	**y = temp;
}

void SwapExamples::SwapC(int * &x, int * &y) {
	int* temp;
	temp = x;
	x = y;
	y = temp;
}

void SwapExamples::SwapD(int*x, int*y) {
	int temp;
	temp = *x;
	*x = *y;
	*y = temp;
}

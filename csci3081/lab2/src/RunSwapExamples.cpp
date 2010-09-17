/* $Id: TestSwapExamples.h,v 1.1 2006/09/15 12:24:45 staats Exp $ */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "SwapExamples.h"

using namespace std;

int finalScore;

void pass(const string& str) {
	cout << "PASS! :" << str << endl;
	finalScore += 1;
}

void fail(const string& str) {
	cout << "FAIL! :" << str << endl;
}


//Test to see x and y swap - 1 pts
  void testSwapASwapping() {
    int x = 10;
		int y = -4;		
		SwapExamples::SwapA(x, y);
		string s = "Test Swap A with value: ";
		//Check to see values have changed
	if (x == -4 && y == 10) {
		pass(s);
	} else {
		fail(s);
	}
		
		
	}
	
	//Test to see x and y's locations don't change - 1 pts
	void testSwapALocation () {
		int x = 15;
		int y = 9;		
		int *xLocation = &x;
		int *yLocation = &y;
		
		SwapExamples::SwapA(x, y);
		string s = "Test Swap A with Location: ";	
	if (&x == xLocation && &y == yLocation) {
		pass(s);
	} else {
		fail(s);
	}
		
	}
	
	//Test to see x and y swap - 1 pts
	void testSwapCSwapping() {
		int *x = new int;
		int *y = new int;		
		*x = 12;
		*y = -5;
		
		SwapExamples::SwapC(x, y);
		string s = "Test Swap C with value: ";
		//Check to see values have changed
	if (*x == -5 && *y == 12) {
		pass(s);
	} else {
		fail(s);
	}		
		delete x;
		delete y;
	}
	
	//Test to see x and y's locations do change - 1 pts
	void testSwapCLocation () {
		int *x = new int;
		int *y = new int;		
		*x = 215;
		*y = 84;
		int *xLocation = x;
		int *yLocation = y;
		
		SwapExamples::SwapC(x, y);
		string s = "Test Swap C with Location: ";
	if (x == yLocation && y == xLocation) {
		pass(s);
	} else {
		fail(s);
	}
		
		delete x;
		delete y;
	}
	
	//Test to see x and y swap - 1 pts
	void testSwapBSwapping() {
		int **x = new int*;
		int **y = new int*;
		
		*x = new int;
		*y = new int;
		
		**x = 123;
		**y = -456;
				
		SwapExamples::SwapB(x, y);
		string s = "Test Swap B with value: ";
		//Check to see values have changed
		
	if (**x == -456 && **y == 123) {
		pass(s);
	} else {
		fail(s);
	}
		
		delete *x;
		delete *y;
		delete x;
		delete y;
		
	}
	
	//Test to see x and y's locations do not change - 1 pts
	void testSwapBLocation () {
		int **x = new int*;
		int **y = new int*;
		
		*x = new int;
		*y = new int;
		
		**x = 123;
		**y = -456;
		
		int *xPointerLoc = *x;
		int *yPointerLoc = *y;
		int **xLoc = x;
		int **yLoc = y;
				
		SwapExamples::SwapB(x, y);
		
		//Check to see values have changed
		string s = "Test Swap B with Location: ";
	if (*x == xPointerLoc && *y == yPointerLoc && x == xLoc && y == yLoc) {
		pass(s);
	} else {
		fail(s);
	}
		
		delete *x;
		delete *y;
		delete x;
		delete y;
	}
	
	//Test to see x and y swap - 1 pts
	void testSwapDSwapping() {
		int* x = new int;
		int* y = new int;		
		*x = 2;
		*y = -2;
		SwapExamples::SwapD(x, y);
		string s = "Test Swap D with value: ";
		//Check to see values have changed		
	if (*x == -2 && *y == 2) {
		pass(s);
	} else {
		fail(s);
	}	
		
		delete x;
		delete y;
	}
	
	//Test to see x and y's locations don't change - 1 pts
	void testSwapDLocation () {
		int *x = new int;
		int *y = new int;
		*x = 153;
		*y = 93;
				
		int *xLocation = x;
		int *yLocation = y;
		string s = "Test Swap D with Location: ";
		SwapExamples::SwapD(x, y);
	if (x == xLocation && y == yLocation) {
		pass(s);
	} else {
		fail(s);
	}	
		
		delete x;
		delete y;		
	}	

int main(void) {
	finalScore = 12; //they get 12 points if it runs

	testSwapASwapping();
	testSwapALocation ();
	testSwapBSwapping();
	testSwapBLocation ();
	testSwapCSwapping();
	testSwapCLocation ();
	testSwapDSwapping();
	testSwapDLocation ();
	cout << "Points: " << finalScore << "/" << 20;

	return EXIT_SUCCESS;
}

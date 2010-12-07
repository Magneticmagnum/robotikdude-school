#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "BankAccount.h"

int finalScore;

void pass(const string& str)
{
	cout << "PASS! :" << str << endl;
	finalScore += 1;
}

void fail(const string& str)
{
	cout << "FAIL! :" << str << endl;
}

// Deposit with non-negative amounts
void testDeposit1()
{
	string s = "Test deposit with positive amount: ";
	BankAccount acct("Jill", 17);
	int value = 0;
	value = acct.deposit(8);
	if (value == 8 && acct.getBalance() == 25)
	{
		pass(s);
	}
	else
	{
		fail(s);
	}
}

void testDeposit2()
{
	string s = "Test deposit with zero amount: ";
	BankAccount acct("Jill", 17);
	int value = 1;
	value = acct.deposit(0);
	if (value == 0 && acct.getBalance() == 17)
	{
		pass(s);
	}
	else
	{
		fail(s);
	}
}

// Deposit with negative amount
void testDeposit3()
{
	string s = "Test deposit with negative amount: ";
	BankAccount acct("Jack", 21);
	int value = acct.deposit(-3);
	if (value == 0 && acct.getBalance() == 21)
	{
		pass(s);
	}
	else
	{
		fail(s);
	}
}

// Withdraw with non-negative amount
void testWithdraw1()
{
	string s = "Test withdraw with non-negative amount: ";
	BankAccount acct("Jacob", 7);
	int value = acct.withdraw(6);
	if (value == 6 && acct.getBalance() == 1)
	{
		pass(s);
	}
	else
	{
		fail(s);
	}
}

void testWithdraw2()
{
	string s = "Test withdraw with non-negative amount: ";
	BankAccount acct("Jacob", 7);
	int value = acct.withdraw(0);
	if (value == 0 && acct.getBalance() == 7)
	{
		pass(s);
	}
	else
	{
		fail(s);
	}
}

// Withdraw with negative amount
void testWithdraw3()
{
	string s = "Test withdraw with negative amount: ";
	BankAccount acct("Jacob", 7);
	int value = acct.withdraw(9);
	if (value == 9 && acct.getBalance() == -2)
	{
		pass(s);
	}
	else
	{
		fail(s);
	}
}

// Not overdrawn with non-negative balance
void testOverdrawn1()
{
	string s = "Test not overdrawn with non-negative balance: ";
	BankAccount acct("Jim", 7);
	int value = acct.withdraw(5);
	if (value == 5 && acct.getBalance() == 2)
	{
		value = acct.withdraw(2);
		if (value == 2 && acct.getBalance() == 0 && !acct.isOverdrawn())
		{
			pass(s);
		}
		else
		{
			fail(s);
		}
	}
	else
	{
		fail(s);
	}
}

// Overdrawn with negative balance
void testOverdrawn2()
{
	string s = "Test overdrawn with negative balance: ";
	BankAccount acct("Jim", 7);
	int value = acct.withdraw(17);
	if (value == 17 && acct.getBalance() == -10 && acct.isOverdrawn())
	{
		pass(s);
	}
	else
	{
		fail(s);
	}
}

// Deposit in overdrawn account
void testDepositOverdrawn()
{
	string s = "Test deposit into overdrawn account: ";
	BankAccount acct("Jim", 7);
	int value = acct.withdraw(10); // balance is -3
	if (value == 10 && acct.getBalance() == -3 && acct.isOverdrawn())
	{
		value = acct.deposit(2);
		if (value == 2 && acct.getBalance() == -1 && acct.isOverdrawn())
		{
			value = acct.deposit(1);
			if (value == 1 && acct.getBalance() == 0 && !acct.isOverdrawn())
			{
				pass(s);
			}
			else
			{
				fail(s);
			}
		}
		else
		{
			fail(s);
		}
	}
	else
	{
		fail(s);
	}
}

// Withdraw from overdrawn account
void testWithdrawOverdrawn()
{
	string s = "Test withdraw from overdrawn account: ";
	BankAccount acct("Jim", 7);
	int value = acct.withdraw(10); // balance is -3
	value = acct.withdraw(2);
	if (value == 0 && acct.getBalance() == -3 && acct.isOverdrawn())
	{
		pass(s);
	}
	else
	{
		fail(s);
	}
}

int main(void)
{
	finalScore = 10; //they get 10 points if it runs

	testDeposit1();
	testDeposit2();
	testDeposit3();
	testWithdraw1();
	testWithdraw2();
	testWithdraw3();
	testOverdrawn1();
	testOverdrawn2();
	testDepositOverdrawn();
	testWithdrawOverdrawn();

	cout << "Points: " << finalScore << "/" << 20;

	return EXIT_SUCCESS;
}

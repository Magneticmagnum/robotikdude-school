/* $Id: Account.h,v 1.2 2006/08/21 19:19:58 jcollins Exp $ */

#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include <string>
using namespace std;

/**
 * A simple bank account.
 */

class BankAccount
{
public:

	/**
	 * Creates an account, given a name and an initial balance. The name
	 * defaults to an empty string, and the balance defaults to 0.
	 */
	BankAccount(const string& theName = "", int initialBalance = 0) :
		name(theName), balance(initialBalance)
	{
	}

	virtual ~BankAccount()
	{
	}

	/**
	 * Returns the account name.
	 */
	const string& getName() const;

	/**
	 * Sets the account name, but only if it's currently blank.
	 */
	void setName(const string& newName);

	/**
	 * Returns the account balance.
	 */
	int getBalance() const
	{
		return balance;
	}

	/**
	 * Deposits an amount in the account, returns the amount
	 * actually deposited. Amount must be non-negative, otherwise amount
	 * deposited will be 0.
	 */
	int deposit(int amount);

	/**
	 * Withdraws an amount from the account, returns amount actually
	 * withdrawn. Amount must be non-negative, and current balance > 0,
	 * otherwise amount withdrawn will be 0.
	 */
	int withdraw(int amount);

	/**
	 * True just in case the account balance < 0
	 */
	bool isOverdrawn();

private:
	string name;
	int balance;
};

#endif /*BANKACCOUNT_H*/

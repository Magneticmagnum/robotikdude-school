/* $Id: $ */
/* Implementation of the Account class */

#include <string>
#include "BankAccount.h"
using namespace std;

const string& BankAccount::getName() const
{
	return name;
}

void BankAccount::setName(const string& newName)
{
	name = newName;
}

/**
 * Deposits amount into the account and returns the
 * actual amount deposited. If amount is negative, zero
 * will be returned and deposited.
 */
int BankAccount::deposit(int amount)
{
	if (amount < 0)
		amount = 0;
	balance += amount;
	return amount;
}

/**
 * Withdraws amount from the account and returns the actual
 * amount withdrawn. If amount is negative, nothing will be
 * withdrawn and zero will be returned. If account is
 * overdrawn, any farther withdrawals, will be canceled.
 */
int BankAccount::withdraw(int amount)
{
	if (amount < 0 || isOverdrawn())
		amount = 0;
	balance -= amount;
	return amount;
}

bool BankAccount::isOverdrawn()
{
	return (balance < 0);
}

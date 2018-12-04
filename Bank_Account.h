#pragma once
#ifndef BANK_ACCOUNT_H
#define BANK_ACCOUNT_H

#include "Account_Kartik.h"
class Bank_Account : public Account
{
public:
	Bank_Account();
	double get_Bank_Balance();
	void view_account_balance();
	void deposit_money(double);
	void withdraw_money(double);
	char* returncurrenttime_Bank_Account();
	void update_transaction_on_account(int,double);			//1-deposit,0-withdraw;double:money deposit or withdraw
	void print_out_history();
private:
	double Total_Cash_Balance;
};

#endif 


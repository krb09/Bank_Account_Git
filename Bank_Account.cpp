#include "pch.h"
#define _CRT_SECURE_NO_WARNINGS
#include "Bank_Account.h"
#include <string>
#include<iostream>
#include<fstream>
#include<time.h>
using namespace std;

Bank_Account::Bank_Account()
{
	Total_Cash_Balance = getCashBalance();
}
double Bank_Account::get_Bank_Balance()
{
	return Total_Cash_Balance;
}
void Bank_Account::view_account_balance()
{
	cout << "The current account balance is:$" << getCashBalance()<<endl;
}
void Bank_Account::deposit_money(double deposit)
{
	cout << "The current account balance is:$" << getCashBalance();
	setCashBalance_new(getCashBalance() + deposit);
	Update_CashBalance_into_txt(CashBalance);
	cout<<"After deposit, the current account balance is:$"<< getCashBalance();
	update_transaction_on_account(1, deposit);

}
void Bank_Account::withdraw_money(double money)
{
	cout << "The current account balance is:$" << getCashBalance();
	setCashBalance_new(getCashBalance() - money);
	Update_CashBalance_into_txt(CashBalance);
	cout << "After withdrawal, the current account balance is:$" << getCashBalance();
	update_transaction_on_account(0, money);

}
char* Bank_Account::returncurrenttime_Bank_Account()
{
	time_t seconds;
	seconds = time(NULL);
	tm * timeinfo;
	timeinfo = localtime(&seconds);
	return asctime(timeinfo);
}
void Bank_Account::update_transaction_on_account(int choice,double money)
{
		ofstream write_trans;
		write_trans.open("Bank_Account_History.txt", ios::app);			//append and add at the end
		if (choice == 1)						//share was bought
		{
			write_trans << "Deposit" << "	" << money << "		" <<returncurrenttime_Bank_Account()<< "	" << get_Bank_Balance() << endl;
			write_trans.close();
		}
		else
		{
			write_trans << "Withdraw" << "	" << money << "		" <<returncurrenttime_Bank_Account()<< "	" << get_Bank_Balance() << endl;
			write_trans.close();

		}
}
void Bank_Account::print_out_history()
{
	ifstream read_bank;
	string item;
	read_bank.open("Bank_Account_History.txt");
	while (getline(read_bank,item))
	{
		cout << item << endl;
	}
	read_bank.close();
}


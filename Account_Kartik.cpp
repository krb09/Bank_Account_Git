#pragma
#include"pch.h"
#include"Account_Kartik.h"
#include<iostream>
#include<fstream>
#include<string>
using namespace std;

//X--------------------------------------------------------------------------------------------------------------------------------------------XX
Account::Account()
{
	setCashBalance_from_txt();
}
//X--------------------------------------------------------------------------------------------------------------------------------------------XX
void Account::setCashBalance_new(double money)
{
	CashBalance = money;
}

//X---------------------------------------------------------------------------------------------------------------------------------------------XX

void Account::setCashBalance_from_txt()
{
	double CB=-1;								//temporary variable to store Current balance
	ifstream read_CB;						
	read_CB.open("Current_CashBalance.txt");
	string item;							//to store the string read
	while (!read_CB.eof())
	{
		read_CB >> item;
		if (item == "CashBalance($)")
		{
			read_CB >> CB;
		}
	}
	read_CB.close();
	CashBalance = CB;
}
//X---------------------------------------------------------------------------------------------------------------------------------------------XX

void Account::Update_CashBalance_into_txt(double CCB)		//update current cashbalance
{
	string item;
	ofstream write_ccb;
	write_ccb.open("Current_CashBalance.txt",ios::ate);
	write_ccb << "CashBalance($)	"<<CCB<<endl;
	write_ccb.close();
	this->setCashBalance_from_txt();								//after you update, set the cashbalance for the object
}
double Account::getCashBalance() const
{
	return CashBalance;
}
void Account::Display_CashBalance() const
{
	cout << "Current CashBalance: $" << getCashBalance()<<endl;
}
//X--------------------------------------------------------------------------------------------------------------------------------------------XX

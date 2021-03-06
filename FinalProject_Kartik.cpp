// FinalProject_Kartik.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "Stock_portfolio_ListNode_Kartik.h"
#include "Stock_portfolio_List.h"
#include "Bank_Account.h"
#include <iostream>
#include <fstream>							//to read as well as write in an external file
#include <string>
using namespace std;

void stock_account_instructions();
void stock_account_execute();
void bank_account_instructions();
void bank_account_execute();

int main()
{
	int choice;
	do
	{
		cout <<"Welcome to the Account Management System" << endl;
		cout <<"1. Stock Portfolio Account\n"
			<< "2. Bank Account\n"
			<< "0. Exit\n";
		cout << "Please select an account to access :";
		cin >> choice;
		switch (choice)
		{
		case 1:
			stock_account_execute();
			break;
		case 2:
			bank_account_execute();
			break;
		case 3:
			break;
		}
	} while (choice != 0);	
		
}
void stock_account_instructions()
{
	{
		cout <<"Welcome to Stock Account!\n"
			<< "1. Display the price for a stock symbol\n"
			<< "2. Display the current portfolio\n"
			<< "3. Buy shares\n"
			<< "4. Sell shares\n"
			<< "5. View a graph for the portfolio value\n"
			<< "6. View transaction history\n"
			<< "0. Exit to previous menu." << endl;
		cout << "Please select an option:";
	}
}
void stock_account_execute()
{
	List L;
	int choice_SA;
	do
	{
		string symbol;
		double number;
		double amount;
		stock_account_instructions();
		cin >> choice_SA;
		switch (choice_SA)
		{
		case 1:
			cout << "Enter the symbol of the company you want to display the shares price for:";
			cin >> symbol;
			L.printStockPrice(symbol);
			break;
		case 2:
			L.print_stock_portfolio();
			break;
		case 3:
			cout << "Enter the symbol of the company you want to buy the shares for:";
			cin >> symbol;
			cout << "Enter the number of shares you want to buy:";
			cin >> number;
			cout << "Enter the maximum amount you are willing to pay for each share:$";
			cin >> amount;
			L.buy_stock(symbol, number, amount);
			L.totalPortfolioValue();			//every time you make a transaction, you update the txt files.
			break;
		case 4:
			cout << "Enter the symbol of the company you want to sell the shares for:";
			cin >> symbol;
			cout << "Enter the number of shares you want to sell:";
			cin >> number;
			cout << "Enter the minimum amount you are willing to sell each share for:$";
			cin >> amount;
			L.sell_stock(symbol, number, amount);
			L.totalPortfolioValue();			//every time you make a transaction, you update the txt files.
			break;
		case 5:
			L.ConnecttoMatlab();
		case 6:
			L.read_stock_transaction_history();
			break;
		case 0:
			return;
		}
	} while (choice_SA != 0);
}
void bank_account_instructions()
{
	{
		cout << "Welcome to Bank Account!\n"
			<< "1. View Account Balance\n"
			<< "2. Deposit Money\n"
			<< "3. Withdraw Money\n"
			<< "4. Print out history\n"
			<< "0. Exit to previous menu." << endl;
		cout << "Please select an option:";
	}
}
void bank_account_execute()
{
	Bank_Account BA;
	int choice_SA;
	do
	{
		string symbol;
		double amount;
		bank_account_instructions();
		cin >> choice_SA;
		switch (choice_SA)
		{
		case 1:
			BA.view_account_balance();
			break;
		case 2:
			cout << "Enter the amount of money you want to deposit:$";
			cin >> amount;
			BA.deposit_money(amount);
			break;
		case 3:
			cout<< "You currently have $" << BA.get_Bank_Balance() << " in your account."<<endl;
			cout << "Enter the amount of money you want to withdraw:$";
			cin >> amount;
			cout << endl;
			if (amount <= BA.get_Bank_Balance())
				BA.withdraw_money(amount);
			else
				cout << "Not enough balance in the account. You currently have $" << BA.get_Bank_Balance() << " in your account."<<endl;
			break;
		case 4:
			BA.print_out_history();
			break;
		case 0:
			return;
		}
	} while (choice_SA != 0);
}
#include "pch.h"
#include "Account_Kartik.h"
#pragma once
#include "Stock_portfolio_ListNode_Kartik.h"
#include<time.h>
#ifndef LIST_H
#define LIST_H
class List: public Account
{
public:
	List(ListNode* = nullptr, ListNode* = nullptr);
	bool IsEmpty();
	void print_stock_portfolio();
	void buy_stock(string,double,double);				//enter the share symbol and the number of share to be bought
	void sell_stock(string, double,double);
	double return_stockprice(string);
	double return_numberofshares_from_LinkedList(string);
	double return_share_per_price_from_LinkedList(string);
	void printStockPrice(string);
	void Copy_portfolio();
	string generate_random_file();
	void bubble_sort();
	void stock_transaction_history(int,string,double,double,double);  //(1:buy,0:sell;sym;number;share_price;totalvalue)
	char* returncurrenttime();
	void update_transaction_on_account_stockinfo(int, double);		//buy and sell stock update on bank_account_txt
	time_t returncurrenttime_in_seconds();					//I need this for plotting the files
	int return_number_of_companies();
	void totalPortfolioValue();
	void ConnecttoMatlab();
	void read_stock_transaction_history();


private:
	ListNode *firstptr;
	ListNode *lastptr;
	ListNode* getNewNode(string sym,double value);
	void updateList();
};
#endif

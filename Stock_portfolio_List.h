#include "pch.h"
#include "Account_Kartik.h"
#pragma once
#include "Stock_portfolio_ListNode_Kartik.h"
#ifndef LIST_H
#define LIST_H
class List: public Account
{
public:
	List(ListNode* = nullptr, ListNode* = nullptr);
	void insertatfront(string ,const int&);
	void removefromfront();
	void insertatlast(string,const int&);
	void removefromlast();
	void print_stock_portfolio();
	bool IsEmpty();
	void buy_stock(string,double,double);				//enter the share symbol and the number of share to be bought
	double return_stockprice(string);
	void printStockPrice(string);
	void Copy_portfolio();
	void sell_stock(string, double, double);
private:
	ListNode *firstptr;
	ListNode *lastptr;
	ListNode* getNewNode(string sym,int value);
	void updateList();
};
#endif

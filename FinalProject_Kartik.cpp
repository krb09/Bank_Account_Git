// FinalProject_Kartik.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "Stock_portfolio_ListNode_Kartik.h"
#include "Stock_portfolio_List.h"
#include <iostream>
#include <fstream>							//to read as well as write in an external file
#include <string>
using namespace std;

int main()
{
	List L;
	L.printStockPrice("GOOG");
	/*string s = "MSFT";
	double num = 1;
	double min = 30;
	L.buy_stock(s, num, min);


	string s1 = "GOOG";
	double num1 = 1;
	double min1 = 600;
	L.buy_stock(s1, num1, min1);


	string s2 = "AMZN";
	double num2 = 1;
	double min2 = 350;
	L.buy_stock(s2, num2, min2);


	string s3 = "AMZN";
	double num3 = 1;
	double min3 = 350;
	L.buy_stock(s3, num3, min3);


	string s4 = "GS";
	double num4 = 1;
	double min4 = 180;
	L.buy_stock(s4, num4, min4);*/

	L.print_stock_portfolio();
}

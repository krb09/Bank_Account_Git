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
	L.buy_stock("GOOG", 1, 600);
	L.print_stock_portfolio();
	L.buy_stock("GOOG", 1, 600);
	L.print_stock_portfolio();


}

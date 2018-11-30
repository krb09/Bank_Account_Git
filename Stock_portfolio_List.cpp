#include "pch.h"
#include <iostream>
#include <fstream>			// for input/output from the text files
#include<iomanip>


using namespace std;
#include "Stock_portfolio_List.h"
#include "Stock_portfolio_ListNode_Kartik.h"
List::List(ListNode *a, ListNode *b)
{
	a = nullptr;
	b = nullptr;
	updateList();
}
void List::insertatfront(string s,const int &a)
{
	ListNode *newptr = getNewNode(s,a);
	if (IsEmpty())
	{
		firstptr = lastptr = newptr;
	}
	else
	{
		newptr->nextptr = firstptr;
		firstptr->prevptr = newptr;
		firstptr = newptr;
	}
}
void List::insertatlast(string s,const int &a)
{
	ListNode *newptr = getNewNode(s,a);
	if (IsEmpty())
	{
		firstptr = lastptr = newptr;
	}
	else
	{
		newptr->prevptr = lastptr;
		lastptr->nextptr = newptr;
		lastptr = newptr;
	}
}
void List::removefromfront()
{
	ListNode *tempptr = firstptr;
	if (IsEmpty())
	{
		cout << "The list is empty.\n";
	}
	{
		if (firstptr == lastptr)
		{
			firstptr = lastptr = nullptr;
		}
		else
		{
			firstptr->nextptr->prevptr = nullptr;
			firstptr = firstptr->nextptr;
			delete tempptr;
		}
	}
}
void List::removefromlast()
{
	ListNode *tempptr = lastptr;
	if (IsEmpty())
	{
		cout << "The list is empty.\n";
	}
	else
	{
		if (firstptr == lastptr)
		{
			firstptr = lastptr = nullptr;
		}
		else
		{
			tempptr->prevptr->nextptr = nullptr;
			lastptr = lastptr->prevptr;
			delete tempptr;
		}
	}
}
void List::print_stock_portfolio()
{
	ListNode *tempptr = firstptr;
	if (IsEmpty())
	{
		cout << "The list is empty";
	}
	else
	{
		cout << "CompanyName" <<setw(15)<<"NumberOfStocks"<<setw(13)<<"PricePerShare"<<setw(10)<<"TotalValue"<<endl;
		while (tempptr != nullptr)
		{
			cout << tempptr->getSym()<< setw(15)<<tempptr->getData() << setw(13) <<return_stockprice(tempptr->getSym()) << setw(10) << tempptr->getData()*return_stockprice(tempptr->getSym()) << endl;
			tempptr = tempptr->nextptr;
		}
	}
}
bool List::IsEmpty()
{
	if (firstptr == nullptr)
		return true;
	else
		return false;
}
ListNode* List::getNewNode(string sym,int value)
{
	ListNode *newobj = new ListNode(sym,value);
	return newobj;
}
//XX----------------------------------------------------FUNCTIONS RELATED TO PROJECT-----------------------------------------------------------------------------XX
double List::return_stockprice(string s)
{
	ifstream read_txt;											//define a input object
	read_txt.open("Result_1.txt");								//read the file
	string item;												//to iterate through file	
	double value;												//store the value
	int flag = 0;
	while (!read_txt.eof())										//to iterate till the end of file
	{
		read_txt >> item;
		if (item == s)						// If the symbol exists
		{
			flag = 1;							//to check if the symbol is found
			read_txt >> value;					/*So this separates the contents on the white spaces in the text file
												Reads the value till white space and stores in the variable*/
		}
	}
	if (flag == 0)
	{
		cout << "Symbol not found.";
		return 0;
	}
	else
	{
		return value;														//to be used in print_portfolio
	}
	read_txt.close();								//close the file

}
void List::printStockPrice(string s)
{
	ifstream read_txt;											//define a input object
	read_txt.open("Result_1.txt");								//read the file
	string item;												//to iterate through file	
	double value;												//store the value
	int flag = 0;
	while (!read_txt.eof())										//to iterate till the end of file
	{
		read_txt >> item;
		if (item == s)						// If the symbol exists
		{
			flag = 1;							//to check if the symbol is found
			read_txt >> value;					/*So this separates the contents on the white spaces in the text file
												Reads the value till white space and stores in the variable*/
		}
	}
	if (flag == 0)
	{
		cout << "Symbol not found.";
	}
	else
	{
		cout << "Company-Symbol" << "  " << "Price per share" << endl;
		cout << s << "              " << "$" << value << endl;					//to be used in print_portfolio
	}
	read_txt.close();
	
}
void List::buy_stock(string sym1,double num,double min_amt)
{
	double curr_value=-1;
	ifstream read_share;
	string item;
	int flag = 0;
	read_share.open("Result_1.txt");
	while (!read_share.eof())
	{
		read_share >> item;
		if (item == sym1)
		{
			read_share >> curr_value;				// get the current value of share from the file
			flag = 1;
		}
	}
	read_share.close();
	if (num*min_amt <= getCashBalance() && min_amt >= curr_value)
	{
		ListNode *newptr = getNewNode(sym1, num);
		if (IsEmpty())																//if this is the first purchase
		{
			firstptr = lastptr = newptr;
		}
		else                                                                     //if the symbol is not present
		{
			ListNode *tempptr = firstptr;
			int flag = 0;
			while (tempptr != nullptr && flag == 0)		//search for the position
			{
				if (sym1 > tempptr->sym)
					tempptr = tempptr->nextptr;
				else if (sym1 == tempptr->sym)						//LOOKING FOR EXISTING SYMBOL
					flag = 2;
				else
					flag = 1;
			}
			if (tempptr == firstptr && flag != 2)					//its the minimum
			{
				firstptr->prevptr = newptr;
				newptr->nextptr = firstptr;
				firstptr = newptr;
			}
			else if (flag == 2)
			{
				tempptr->data = tempptr->data + num;
			}
			else if (tempptr == nullptr && flag != 2)		//if its the maximum
			{
				lastptr->nextptr = newptr;
				newptr->prevptr = lastptr;
				lastptr = newptr;
			}
			else                                                     //if its in between
			{
				(tempptr->prevptr)->nextptr = newptr;
				newptr->nextptr = tempptr;
				newptr->prevptr = tempptr->prevptr;
				tempptr->prevptr = newptr;
			}
		}
		Update_CashBalance(CashBalance - (curr_value*num));

	}
	else if(num*min_amt > getCashBalance())
	{
		cout << "Not enough balance"<<endl;
	}
	else
	{
		cout << "Price per share is more than what offered." << endl;
	}
	if (flag == 0)
		cout << "Symbol not found." << endl;
}
void List::Copy_portfolio()												//copy the contents to the files
{
	ofstream copy;
	copy.open("Current_portfolio.txt");										//replace the contents
	ListNode *tempptr = firstptr;
	while (tempptr != nullptr)
	{
		string symbol = tempptr->getSym();
		double value = tempptr->getData();
		copy << left << symbol <<"	" << value<<endl;
		tempptr = tempptr->nextptr;
	}
	copy.close();

}

void List::updateList()						//every time the system makes a list, a new file is generated
{
	ifstream read;
	string item;
	double num;
	read.open("Current_portfolio.txt");
	ListNode *tempptr = firstptr;
	while (read>>item>>num)
	{
		ListNode *newptr = getNewNode(item, num);
		if (IsEmpty())																//if this is the first purchase
		{
			firstptr = lastptr = newptr;
		}
		else                                                                     //if the symbol is not present
		{
			ListNode *tempptr = firstptr;
			int flag = 0;
			while (tempptr != nullptr && flag == 0)		//search for the position
			{
				if (item > tempptr->sym)
					tempptr = tempptr->nextptr;
				else if (item == tempptr->sym)						//LOOKING FOR EXISTING SYMBOL
					flag = 2;
				else
					flag = 1;
			}
			if (tempptr == firstptr && flag != 2)					//its the minimum
			{
				firstptr->prevptr = newptr;
				newptr->nextptr = firstptr;
				firstptr = newptr;
			}
			else if (flag == 2)
			{
				tempptr->data = tempptr->data + num;
			}
			else if (tempptr == nullptr && flag != 2)		//if its the maximum
			{
				lastptr->nextptr = newptr;
				newptr->prevptr = lastptr;
				lastptr = newptr;
			}
			else                                                     //if its in between
			{
				(tempptr->prevptr)->nextptr = newptr;
				newptr->nextptr = tempptr;
				newptr->prevptr = tempptr->prevptr;
				tempptr->prevptr = newptr;
			}
		}
	}
}
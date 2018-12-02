#include "pch.h"
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>			// for input/output from the text files
#include<iomanip>


using namespace std;
#include "Stock_portfolio_List.h"
#include "Stock_portfolio_ListNode_Kartik.h"

//XXXXX---------------------------------------------------------------------------------------------------------------------------------XXXXXXX
List::List(ListNode *a, ListNode *b)
{
	a = nullptr;
	b = nullptr;
	updateList();
}
//XXXXX---------------------------------------------------------------------------------------------------------------------------------XXXXXXX

void List::print_stock_portfolio()
{
	ListNode *tempptr = firstptr;
	if (IsEmpty())
	{
		cout << "The list is empty";
	}
	else
	{
		cout << "CompanySymbol" <<"\t"<<"NumberOfStocks"<< "\t" <<"PricePerShare"<< "\t" <<"TotalValue"<<endl;
		double total_stock_value = 0;
		while (tempptr != nullptr)
		{
			cout << setw(13)<<tempptr->getSym()<<"\t"
			<< setprecision(3) << fixed
			<<setw(14)<<tempptr->getData()<<"\t"
			<< setw(13) <<tempptr->getpps()<<"\t"
			<< setw(10) << tempptr->gettotalvalue() << endl;
			total_stock_value = total_stock_value + tempptr->gettotalvalue();
			tempptr = tempptr->nextptr;
		}
		cout << "Total potfolio value:$" << total_stock_value<<endl;
	}
}
//XXXXX---------------------------------------------------------------------------------------------------------------------------------XXXXXXX

bool List::IsEmpty()
{
	if (firstptr == nullptr)
		return true;
	else
		return false;
}
//XXXXX---------------------------------------------------------------------------------------------------------------------------------XXXXXXX

ListNode* List::getNewNode(string sym,int value)
{
	ListNode *newobj = new ListNode(sym,value);
	return newobj;
}
//XX------------------------------------------------------------------------------------------------------------------------------------------------------XX
//XX----------------------------------------------------FUNCTIONS RELATED TO PROJECT-----------------------------------------------------------------------------XX
double List::return_stockprice(string s)					//RETURN STOCK PRICE FROM RANDOM FILE
{
	ifstream read_txt;											//define a input object
	string file = generate_random_file();
	read_txt.open(file);								//read the file
	string item;												//to iterate through file	
	double value;												//store the value
	int flag = 0;
	while (!read_txt.eof())										//to iterate till the end of file
	{
		read_txt >> item;
		if (item == s)						// If the symbol exists
		{
			flag = 1;							//to check if the symbol is found
			read_txt >> value;					/*So this separates the contents on the white spaces in the text file,reads the value till white space and stores in the variable*/
		}
	}
	if (flag == 0)
	{
		return 0;
	}
	else
	{
		return value;														//to be used in print_portfolio
	}
	read_txt.close();								//close the file

}
//XXXXX---------------------------------------------------------------------------------------------------------------------------------XXXXXXX

void List::printStockPrice(string s)
{
	double printStockPrice_value = return_stockprice(s);
	if (printStockPrice_value == 0)
	{
		cout << "Symbol not found.";
	}
	else
	{
		cout << "Company-Symbol" << "	" << "Price per share" << endl;
		cout << setw(14)<<s << "	" << "$" << printStockPrice_value << endl;					//to be used in print_portfolio
	}	
}
//XXXXX---------------------------------------------------------------------------------------------------------------------------------XXXXXXX
void List::buy_stock(string sym1,double num,double min_amt)
{
	double curr_value = 0;								//find the sym and the corresponding value. ***STEP 1***
	string file = generate_random_file();
	ifstream read_share;
	string item;
	int flag = 0;
	read_share.open(file);
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
	if (flag == 0)
	{
		cout << "Symbol not found." << endl;				//symbol not found. Invalid symbol. End function
		return;
	}
	if (num*min_amt <= getCashBalance() && min_amt >= curr_value)			//if capable to buy the share
	{
		ListNode *searchsym = firstptr;						//If the symbol is already present
		int searchsymflag = 0;
		while (searchsym != nullptr && searchsymflag==0)
		{
			if (sym1 == searchsym->getSym())
			{
				searchsym->setData(searchsym->getData() + num);				//just update th value of number of shares
				searchsymflag = 1;											//found a value
				stock_transaction_history(1, sym1, num, searchsym->PPS, (searchsym->gettotalvalue())/searchsym->getData()); //add the transaction, divide by data because per share batani hai, its telling the total

			}
			searchsym = searchsym->nextptr;
		}
		if (searchsymflag == 0)												//if value not found
		{
			ListNode *newptr = getNewNode(sym1, num);			//add the share at the begining of the list IF NOT PRESENT. ***STEP 2***
			newptr->setpps(curr_value);							//SET THE VALUE OF PPS TO CURR_VALUE FROM TEXT FILE RESULTS
			if (IsEmpty())
			{
				firstptr = lastptr = newptr;
				stock_transaction_history(1, sym1, num, newptr->PPS,newptr->gettotalvalue()); //add the transaction
			}
			else
			{
				newptr->nextptr = firstptr;
				firstptr->prevptr = newptr;
				firstptr = newptr;
				stock_transaction_history(1, sym1, num, newptr->PPS, newptr->gettotalvalue()); //add the transaction
			}
		}
		ListNode *tempptr1 = firstptr;							//Update the pps of the current portfolio with this new file. ***STEP 3***
		while (tempptr1 != nullptr)
		{
			double curr_value_temp = 0;
			ifstream read_share_temp;
			string item_temp;
			read_share_temp.open(file);
			while (!read_share_temp.eof())
			{
				read_share_temp >> item_temp;
				if (item_temp == tempptr1->getSym())
				{
					read_share_temp >> curr_value_temp;
					tempptr1->setpps(curr_value_temp);
				}
			}
			tempptr1 = tempptr1->nextptr;
			read_share_temp.close();
		}
		this->bubble_sort();										//Sort *****STEP 4******
		Update_CashBalance(CashBalance - (curr_value*num));			//update the cashbalance if succesfull transaction happens
		Copy_portfolio();											//to copy the current portfolio to the file
	}
	else if (num*min_amt > getCashBalance())
	{
		cout << "Not enough balance" << endl;
	}
	else
	{
		cout << "Price per share is more than what offered." << endl;
	}
}
//XXXXX---------------------------------------------------------------------------------------------------------------------------------XXXXXXX
void List::sell_stock(string sym, double num,double amount_offered)
{
	//find the symbol first
	ListNode *findsym = firstptr;
	int flag_sym = 0;
	while (findsym!= nullptr && flag_sym ==0)
	{
		if (findsym->getSym() == sym)
		{
			flag_sym = 1;
		}
		else
			findsym = findsym->nextptr;
	}
	double current_stock_price = return_stockprice(sym);					//current random stockprice
	if (current_stock_price < amount_offered)			//if the price per share is smaller than what you offered
	{
		cout << "Price per stock is lower than the amount the user is willing to sell for" << endl;
		return;
	}
	else if (flag_sym == 0)
	{
		cout << "Symbol for the stock not found int the portfolio." << endl;
	}
	else                                                //symbol ol present in portfolio
	{
		ListNode *tempptr = firstptr;
		while (tempptr->getSym() != sym)		//to find the current number of shares from the linked list
		{
			tempptr = tempptr->nextptr;
		}
		double current_number_shares = tempptr->getData();
		if (current_number_shares > num)				//if you have more shares than you want to sell
		{
			tempptr->setData(current_number_shares - num);
			ListNode *tempptr1 = firstptr;							//Update the pps of the current portfolio with this new file. 
			string file = generate_random_file();
			while (tempptr1 != nullptr)
			{
				double curr_value_temp = 0;
				ifstream read_share_temp;
				string item_temp;
				read_share_temp.open(file);
				while (!read_share_temp.eof())
				{
					read_share_temp >> item_temp;
					if (item_temp == tempptr1->getSym())
					{
						read_share_temp >> curr_value_temp;
						tempptr1->setpps(curr_value_temp);
					}
				}
				tempptr1 = tempptr1->nextptr;
				read_share_temp.close();
			}
			bubble_sort();
			Update_CashBalance(getCashBalance() + (current_number_shares * return_share_per_price_from_LinkedList(sym)));
			Copy_portfolio();											//to copy the current portfolio to the file

		}
		else if (current_number_shares == num)			//if exactly the amount you want to sell
		{
			Update_CashBalance(getCashBalance() + (num * return_share_per_price_from_LinkedList(sym)));		//update it otherwise it will be lost
			tempptr->setData(0);
			bubble_sort();			//the zero number of shares stock should always be at the last********
			if (return_number_of_companies() == 1)
			{
				firstptr = lastptr = nullptr;
				Copy_portfolio();
			}
			else
			{
				tempptr = lastptr;		//delete the node
				lastptr = (tempptr->prevptr)->nextptr;
				(tempptr->prevptr)->nextptr = nullptr;
				delete tempptr;
				Copy_portfolio();											//to copy the current portfolio to the file
			}
		}
		else
		{
			cout << "You dont have that many shares!" << endl;
		}
	}
	
}
//XXXXX---------------------------------------------------------------------------------------------------------------------------------XXXXXXX

void List::Copy_portfolio()												//copy the contents to the files
{
	ofstream copy;
	copy.open("Current_portfolio.txt");										//replace the contents
	ListNode *tempptr = firstptr;
	while (tempptr != nullptr)
	{
		string symbol = tempptr->getSym();
		double value = tempptr->getData();
		double price_per_share = tempptr->getpps();
		copy << symbol <<"	" << setw(5)<<value<<"	"<<setw(13)<<price_per_share<<endl;
		tempptr = tempptr->nextptr;
	}
	copy.close();

}
//XXXXX---------------------------------------------------------------------------------------------------------------------------------XXXXXXX
void List::updateList()						//every time the system makes a list, a new file is generated
{
	ifstream read;
	string item;
	double num;
	double price_per_share;
	read.open("Current_portfolio.txt");
	ListNode *tempptr = firstptr;
	while (read>>item>>num>>price_per_share)
	{
		ListNode *newptr = getNewNode(item, num);							//SET THE OTHER TWO
		cout << price_per_share<<endl;
		newptr->setpps(price_per_share);									//SET PPS
		if (IsEmpty())																//if this is the first purchase
		{
			firstptr = lastptr = newptr;
		}
		else                                                                     //if the symbol is not present, add to front and sort
		{
			newptr->nextptr = firstptr;
			firstptr->prevptr = newptr;
			firstptr = newptr;
			bubble_sort();
		}
	}
}
//XXXXX---------------------------------------------------------------------------------------------------------------------------------XXXXXXX
string List::generate_random_file()
{
	srand(static_cast<unsigned int>(time(0)));                              //Generating the seed value according to the time in the systems in  seconds
	string s[] = { "Result_1.txt","Result_2.txt" };
	string file = s[0 + rand() % 2];
	return file;
}
//XXXXX---------------------------------------------------------------------------------------------------------------------------------XXXXXXX
void List::bubble_sort()
{
	int count = 0;											//Sort the List STEP 4
	ListNode *tempptr3 = firstptr;
	while (tempptr3 != nullptr)
	{
		count = count + 1;
		tempptr3 = tempptr3->nextptr;
	}
	if (count == 1)
	{
		return;
	}
	else
	{
		ListNode *i = firstptr;
		ListNode *j = firstptr;
		while (i != nullptr) {
			while (j->nextptr != nullptr) {
				if (j->gettotalvalue() < (j->nextptr)->gettotalvalue())		
				{
					double data_temp = j->getData();
					double pps_temp = j->getpps();
					string sym_temp = j->getSym();
					//xx---------------------------------------------------xx//
					double data_temp2 = j->nextptr->getData();
					double pps_temp2 = j->nextptr->getpps();
					string sym_temp2 = j->nextptr->getSym();
					//xx----------------------------------------------------xx// 
					j->setData(data_temp2);
					j->setpps(pps_temp2);
					j->setSym(sym_temp2);

					
					j->nextptr->setData(data_temp);
					j->nextptr->setpps(pps_temp);
					j->nextptr->setSym(sym_temp);
				

				}
				j = j->nextptr;
			}
			j = firstptr;
			i = i->nextptr;
		}
	}
}
//XX-------------------------------------------------------------------------------------------------------------------------------------------XX
double List::return_numberofshares_from_LinkedList(string Sym1)
{
	ListNode *tempptr = firstptr;
	int flag = 0;
	while (tempptr != nullptr && flag==0)
	{
		if (Sym1 == tempptr->getSym())
		{
			return tempptr->getData();
			flag = 1;									//if found
		}
		tempptr = tempptr->nextptr;
	}
	if (flag == 0)
		return 0;
}
//XX-------------------------------------------------------------------------------------------------------------------------------------------XX
double List::return_share_per_price_from_LinkedList(string Sym1)
{
	ListNode *tempptr = firstptr;
	int flag = 0;
	while (tempptr != nullptr && flag == 0)
	{
		if (Sym1 == tempptr->getSym())
		{
			return tempptr->getpps();
			flag = 1;									//if found
		}
		tempptr = tempptr->nextptr;
	}
	if (flag == 0)
		return 0;
}
//XX-------------------------------------------------------------------------------------------------------------------------------------------XX
void List::stock_transaction_history(int check, string sym, int num, double pricepstock, double total_value)
{
	ofstream write_trans;
	write_trans.open("stock_transaction_history.txt",ios::app);			//append and add at the end
	if (check == 1)						//share was bought
	{
		write_trans << "Buy" << "	" << sym << "		" << num << "	" << pricepstock << "		" << total_value<<"		"<<returncurrenttime()<<endl;
		write_trans.close();
	}
	else
	{
		write_trans << "Sell" << "	" << sym << "	" << num << "	" << pricepstock << "	" << total_value<<"	"<<returncurrenttime()<<endl;
		write_trans.close();

	}
}
//XX-------------------------------------------------------------------------------------------------------------------------------------------XX
char *List::returncurrenttime()
{
	time_t seconds;
	seconds = time(NULL);
	tm * timeinfo;
	timeinfo = localtime(&seconds);
	return asctime(timeinfo);
}
//XX-------------------------------------------------------------------------------------------------------------------------------------------XX
int List::return_number_of_companies()
{
	ListNode *tempptr = firstptr;
	int count = 0;
	while (tempptr != nullptr)
	{
		count = count + 1;
		tempptr = tempptr->nextptr;
	}
	return count;
}

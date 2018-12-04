#pragma once
#include"pch.h"
#ifndef ACCOUNT_KARTIK_H
#define ACCOUNT_KARTIK_H
class Account {
public:
	Account();				
	void setCashBalance_from_txt();		
	void setCashBalance_new(double);
	double getCashBalance() const;
	void Display_CashBalance() const;
	void Update_CashBalance_into_txt(double);
protected:
	double CashBalance;
};
#endif 

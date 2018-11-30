#pragma once
#include"pch.h"
#ifndef ACCOUNT_KARTIK_H
#define ACCOUNT_KARTIK_H
class Account {
public:
	Account();				//confusion in this !*************
	void setCashBalance();
	double getCashBalance() const;
	void Display_CashBalance() const;
	void Update_CashBalance(double);
protected:
	double CashBalance;
};
#endif 

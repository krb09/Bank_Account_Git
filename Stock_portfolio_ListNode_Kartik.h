#include"pch.h"
#include"Account_Kartik.h"
#pragma once
#ifndef LISTNODE_H
#define LISTNODE_H
#include <string>
using namespace std;
class ListNode: public Account
{
	friend class List;
public:
	ListNode(string=" ", double = 0,ListNode* = nullptr, ListNode* = nullptr);
	void setSym(string);
	string getSym() const;
	void setData(double);
	double getData() const;
	void setpps(double);
	double getpps() const;
	void setnextPtr(ListNode*);
	ListNode* getnextPtr();
	void setprevPtr(ListNode*);
	ListNode* getprevPtr();
	double gettotalvalue();
private:
	string sym;
	double data;
	double PPS;						//added a new field, price per share
	ListNode *nextptr;
	ListNode *prevptr;
};
#endif 


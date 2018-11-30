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
	ListNode(string=" ", int = 0, ListNode* = nullptr, ListNode* = nullptr);
	void setSym(string);
	string getSym() const;
	void setData(int);
	int getData() const;
	void setnextPtr(ListNode*);
	ListNode* getnextPtr();
	void setprevPtr(ListNode*);
	ListNode* getprevPtr();
private:
	string sym;
	int data;
	ListNode *nextptr;
	ListNode *prevptr;
};
#endif 


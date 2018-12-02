#include "pch.h"
#include "Stock_portfolio_ListNode_Kartik.h"
#include<iostream>
#include<string>
using namespace std;

ListNode::ListNode(string symbol, double a, ListNode* b, ListNode* c)
{
	setSym(symbol);
	setData(a);
	setnextPtr(b);
	setprevPtr(c);
}
void ListNode::setSym(string a)
{
	sym = a;
}
string ListNode::getSym() const
{
	return sym;
}
//----------------------------------------------------//
void ListNode::setData(double a)
{
	data = a;
}
double ListNode::getData() const
{
	return data;
}
//----------------------------------------------------//
void ListNode::setpps(double a)
{
	PPS = a;
}
double ListNode::getpps() const
{
	return PPS;
}
//---------------------------------------------------//
void ListNode::setnextPtr(ListNode* ptr)
{
	nextptr = ptr;
}
ListNode* ListNode::getnextPtr()
{
	return nextptr;
}
//---------------------------------------------------//
void ListNode::setprevPtr(ListNode* ptr)
{
	prevptr = ptr;
}
ListNode* ListNode::getprevPtr()
{
	return prevptr;
}
//---------------------------------------------------//
double ListNode::gettotalvalue()
{
	return (this->PPS)*(this->data);
}
//---------------------------------------------------//

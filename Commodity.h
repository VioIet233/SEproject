#pragma once
#include <string>
#include <iostream>
#include <regex>
#include "Admin.h"
#include "Seller.h"
#include "Buyer.h"
#include "Calculator.h"
using namespace std;


class Commodity
{
	friend void Seller::ChangeCommodity();
	friend void Buyer::BuyCommodities();
	friend ostream& operator << (ostream& X, Commodity& a);
public:
	void operator = (string& Y);
	bool operator == (string ID);
	bool operator >(Commodity C);
	bool operator <(Commodity C) ;
	bool operator >=(Commodity C) ;
	bool operator <=(Commodity C) ;
	Commodity() {}
	Commodity(int Commoditynum,string SellerID,string date);
	bool FindCommodity(string A,int Menu);
	void output(int Menu , bool X = false);
	string tranS();
	void StatusTran();
	bool C_judgeinfo(string a0 = "此字符串为空", string a1 = "此字符串为空", string a2 = "此字符串为空", string a3 = "此字符串为空");
	void C_setinfo(string a0 = "此字符串为空", string a1 = "此字符串为空", string a2 = "此字符串为空", string a3 = "此字符串为空");
	bool Removed();
private:
	string Commodity_ID;
	string Commodity_Name;
	string Price;
	string Number;
	string Description;
	string Seller_ID;
	string Added_Date;
	string Commodity_Status;
};

#pragma once
#include <string>
#include <iostream>
using namespace std;
class Order
{
	friend ostream& operator << (ostream& X, Order& a);
public:
	void operator=(string& Y);
	bool operator == (string& ID);
	Order() {}
	Order(int Ordernum,string CommodityID,string Price,string number, string Date , string SellerID, string BuyerID);
	void output(int Menu);
	string tranS();
	bool FindOrder(string ID, int Menu);
private:
	string Order_ID;
	string Commodity_ID;
	string UnitPrice;
	string Number;
	string Sold_Date;
	string Seller_ID;
	string Buyer_ID;
};


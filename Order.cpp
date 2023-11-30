#include "Order.h"

void Order:: operator=(string& Y)
{
	int num = 0;
	for (int i = 0; i < Y.size(); i++)
	{
		if (Y[i] == ',')
			num++;
		else
		{
			switch (num)
			{
			case 0:
				Order_ID += Y[i];
				break;
			case 1:
				Commodity_ID += Y[i];
				break;
			case 2:
				UnitPrice += Y[i];
				break;
			case 3:
				Number += Y[i];
				break;
			case 4:
				Sold_Date += Y[i];
				break;
			case 5:
				Seller_ID += Y[i];
				break;
			case 6:
				Buyer_ID += Y[i];
			}
		}
	}
}

bool Order::operator == (string& ID)
{
	if (ID == Order_ID)
		return true;
	else
		return false;
}

Order::Order(int Ordernum, string CommodityID, string Price, string number, string Date, string SellerID, string BuyerID)
{
	Order_ID = "T";
	Order_ID += (char)(Ordernum / 100 + 48);
	Order_ID += (char)(Ordernum / 10 % 10 + 48);
	Order_ID += (char)(Ordernum % 10 + 49);
	Commodity_ID = CommodityID;
	UnitPrice = Price;
	Number = number;
	Sold_Date = Date;
	Seller_ID = SellerID;
	Buyer_ID = BuyerID;
}

void Order::output(int Menu)
{
	//"OrderID  CommodityID  UnitPrice  Number  SoldDate   SellerID  BuyerID"
	//"D001     D001                            2020-02-11 1234      1234
	cout << Order_ID << "     ";
	cout << Commodity_ID << "         ";
	cout << UnitPrice << "  ";
	for (int i = 0; i < 9 - UnitPrice.size(); i++)
		cout << ' ';
	cout << Number << "  ";
	for (int i = 0; i < 6 - Number.size(); i++)
		cout << ' ';
	cout << Sold_Date << "  ";
	if (Menu != 4)
	{
		cout << Seller_ID << "      ";
	}
	if (Menu != 3)
	{
		cout << Buyer_ID;
	}
	cout << endl;
}

string Order::tranS()
{
	string A;
	A += Order_ID;
	A += ',';
	A += Commodity_ID;
	A += ',';
	A += UnitPrice;
	A += ',';
	A += Number;
	A += ',';
	A += Sold_Date;
	A += ',';
	A += Seller_ID;
	A += ',';
	A += Buyer_ID;
	return A;
}

bool Order::FindOrder(string ID, int Menu)
{
	if (Menu == 4 && Seller_ID == ID)
	{
		return true;
	}
	else if (Menu == 3 && Buyer_ID == ID)
	{
		return true;
	}
	return false;
}

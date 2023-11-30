#include "Commodity.h"


void Commodity::operator= (string& Y)
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
				Commodity_ID += Y[i];
				break;
			case 1:
				Commodity_Name += Y[i];
				break;
			case 2:
				Price += Y[i];
				break;
			case 3:
				Number += Y[i];
				break;
			case 4:
				Description += Y[i];
				break;
			case 5:
				Seller_ID += Y[i];
				break;
			case 6:
				Added_Date += Y[i];
				break;
			case 7:
				Commodity_Status += Y[i];
				break;
			}
		}
	}
}

Commodity::Commodity(int Commoditynum, string SellerID,string date)
{
	Commodity_ID += "M";
	Commodity_ID += (char)(Commoditynum / 100 + 48);
	Commodity_ID += (char)(Commoditynum / 10 % 10 + 48);
	Commodity_ID += (char)(Commoditynum % 10 + 49);
	Seller_ID = SellerID;
	Commodity_Status = "OnSale";
	Added_Date = date;
}

bool Commodity::FindCommodity(string A, int Menu)
{
	//卖家查看自己的商品（卖家ID搜索）
	if (Menu == 4)
	{
		if (Seller_ID == A)
			return true;
	}
	//买家和管理员搜索商品（Name搜索）
	else 
	{
		if (Menu != 1 && Commodity_Status == "Removed")
		{
			return false;
		}
		else if (Commodity_Name.find(A, 0) != -1)
		{
			return true;
		}
	}
	return false;
}

void Commodity::output(int Menu, bool X)
{
	//"CommodityID  CommodityName         Price   Number  Description                SellerID  SellDate   CommodityStatus\n";
	//"M001         12345678901234567980                  1234567890     1234567980            2020-02-11 "
	if (Menu == 3 && Commodity_Status == "Removed")
	{
		return;
	}
	cout << Commodity_ID << "         ";
	cout << Commodity_Name << "  ";
	for (int i = 0; i < 20 - Commodity_Name.size(); i++)
		cout << ' ';
	cout << Price << "  ";
	for (int i = 0; i < 6 - Price.size(); i++)
		cout << ' ';
	cout << Number << "  ";
	for (int i = 0; i < 6 - Number.size(); i++)
		cout << ' ';
	if (Menu != 3 || X ) 
	{
		cout << Description << "  ";
		for (int i = 0; i < 40 - Description.size(); i++)
			cout << ' ';
	}
	if (Menu != 4)
	{
		cout << Seller_ID << "  ";
		for (int i = 0; i < 8 - Seller_ID.size(); i++)
			cout << ' ';
	}
	cout << Added_Date << "  ";
	if (Menu != 3)
	{
		cout << Commodity_Status;
	}
	cout << endl;
}

bool Commodity::operator == (string ID)
{
	if (ID == Commodity_ID)
		return true;
	else
		return false;
}

string 	Commodity::tranS()
{
	string A;
	A += Commodity_ID;
	A += ',';
	A += Commodity_Name;
	A += ',';
	A += Price;
	A += ',';
	A += Number;
	A += ',';
	A += Description;
	A += ',';
	A += Seller_ID;
	A += ',';
	A += Added_Date;
	A += ',';
	A += Commodity_Status;
	return A;
}

bool Commodity::C_judgeinfo(string a0, string a1, string a2 , string a3 )
{
	bool X = true;
	//检验商品名称是否规范
	if (a0 != "此字符串为空")
	{
		regex name("[a-zA-Z]{1,20}");
		if (!regex_match(a0, name))
		{
			cout << "商品名称格式错误！" << endl;
			X = false;
		}

	}
	//检验商品价格是否规范
	if (a1 != "此字符串为空")
	{
		regex price("[1-9][0-9]{0,}[.][0-9]");
		if (!regex_match(a1, price ))
		{
			cout << "商品价格格式错误！" << endl;
			X = false;
		}

	}
	//检验商品数量是否规范
	if (a2 != "此字符串为空")
	{
		regex number("[1-9][0-9]{0,}");
		if (!regex_match(a2, number))
		{
			cout << "商品数量格式错误！" << endl;
			X = false;
		}
	}
	//检验商品描述是否规范
	if (a3 != "此字符串为空")
	{
		regex description("[a-zA-Z]{1,40}");
		if (!regex_match(a3, description))
		{
			cout << "商品描述格式错误！" << endl;
			X = false;
		}
	}
	//if (X)
	//{
	//	Commodity_Name = (a0 == "此字符串为空" ? Commodity_Name : a0);
	//	Price = (a1 == "此字符串为空" ? Price : a1);
	//	Number = (a2 == "此字符串为空" ? Number : a2);
	//	Description = (a3 == "此字符串为空" ? Description : a3);
	//}
	return X;

}

void Commodity::C_setinfo(string a0, string a1, string a2, string a3)
{
	if (a0 != "此字符串为空")
		Commodity_Name = a0;
	if (a1 != "此字符串为空")
		Price = a1;
	if (a2 != "此字符串为空")
		Number = a2;
	if (a3 != "此字符串为空")
		Description = a3;
}

void Commodity::StatusTran()
{
	Commodity_Status = Commodity_Status == "Removed" ? "OnSale" : "Removed";
}

bool Commodity::Removed()
{
	if (Commodity_Status == "Removed")
	{
		return true;
	}
	return false;
}

bool Commodity::operator >(Commodity C)
{
	if (calculator(Price + "-" + C.Price)[0] == '-')
	{
		return false;
	}
	return true;
}

bool Commodity::operator <(Commodity C)
{
	if (*this > C)
		return false;
	else
		return true;
}

bool Commodity::operator >=(Commodity C)
{
	int a, b;
	if (Commodity_Name == C.Commodity_Name)
	{
		return false;
	}
	if(Commodity_Name.length() >= C.Commodity_Name.length())
	{

		for (int i = 0; i < C.Commodity_Name.length(); i++)
		{
			a = (int)Commodity_Name[i] > 96 ? (int)Commodity_Name[i] - 32 : (int)Commodity_Name[i];
			b = (int)C.Commodity_Name[i] > 96 ? (int)C.Commodity_Name[i] - 32 : (int)C.Commodity_Name[i];
			if (a > b)
			{
				return true;
			}
			else if (a == b)
			{
				continue;
			}
			else
			{
				return false;
			}
		}
		return false;
	}
	else
	{
		for (int i = 0; i < Commodity_Name.length(); i++)
		{
			a = (int)Commodity_Name[i] > 96 ? (int)Commodity_Name[i] - 32 : (int)Commodity_Name[i];
			b = (int)C.Commodity_Name[i] > 96 ? (int)C.Commodity_Name[i] - 32 : (int)C.Commodity_Name[i];
			if (a > b)
			{
				return true;
			}
			else if (a == b)
			{
				continue;
			}
			else
			{
				return false;
			}
		}
		return false;
	}
}

bool Commodity::operator <=(Commodity C)
{
	if (Commodity_Name == C.Commodity_Name)
	{
		return false;
	}
	if (*this >= C)
		return false;
	else
		return true;
}
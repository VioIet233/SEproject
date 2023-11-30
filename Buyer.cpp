#include "Work.h"
extern Work* p;

Buyer::Buyer(const User& U)
{
	this->User::operator=(U);
}

void Buyer::ShowCommodities()
{
	if (p->Commodity_num != 0)
	{
		p->TranSQL(p->MakeSQL(Select, F_commodity), M_buyer);
	}
	else
	{
		cout << "当前无任何商品！" << endl;
	}

}

void Buyer::BuyCommodities()
{
	cout << "\n请输入您想购买的商品ID：";
	string ID;
	getline(cin, ID);
	regex CID("[M][0-9]{3}");
	if (regex_match(ID, CID))
	{
		vector <Commodity>::iterator it = find(p->commodities.begin(), p->commodities.end(), ID);

		if (it == p->commodities.end())
		{
			cout << "在售商品中未找到该商品！" << endl;
		}
		else if (it->Removed())
		{
			cout << "在售商品中未找到该商品！" << endl;
		}
		else
		{
			//cout << endl;
			//cout << "************************************************************************************************************************\n";
			//cout << "CommodityID  CommodityName         Price   Number  Description                     SellerID  SellDate    CommodityStatus\n";
			//it->output(M_admin);
			//cout << "************************************************************************************************************************\n" << endl;
			cout << "请输入您要购买的数量：";
			string B;
			getline(cin, B);
			regex Number("[1-9][0-9]{0,}");
			if (regex_match(B, Number))
			{
				if (calculator(it->Number + "-" + B)[0] == '-')
				{
					cout << "错误！商品数目不足！\n即将返回买家菜单！";
					return;
				}
				else
				{
					string NewBalance = calculator(Balance + "-" + B + "*" + it->Price);
					if (NewBalance[0] == '-')
					{
						cout << "错误！余额不足，请充值您的余额！" << endl;

						return;
					}
					else
					{
						cout << "购买成功！" << endl;
						//商品新数量
						string NewNumber = calculator(it->Number + "-" + B);
						NewNumber.erase(NewNumber.size() - 2, 2);
						if (NewNumber == "0")
						{
							p->TranSQL(p->MakeSQL(Update, F_commodity, "CommodityStatus = Removed", "CommodityID = " + it->Commodity_ID), M_admin);
						}
						p->TranSQL(p->MakeSQL(Update, F_commodity, "Number = " + NewNumber, "CommodityID = " + it->Commodity_ID), M_admin);
						//卖家余额
						vector <User> ::iterator Uit = find(p->users.begin(), p->users.end(), it->Seller_ID);
						Uit->operator[](0) += "+" + B + "*" + it->Price;
						p->TranSQL(p->MakeSQL(Update, F_user, "Balance = " + calculator("0.0" + Uit->operator[](0) + p->Simplify(Uit->operator[](1), Uit->operator[](2))), "UserID = " + Uit->getID()));
						//买家余额
						vector <User> ::iterator Bit = find(p->users.begin(), p->users.end(), User_ID);
						Bit->operator[](1) += "-" + B + "*" + it->Price;
						Balance = NewBalance;
						p->TranSQL(p->MakeSQL(Update, F_user, "Balance = " + calculator("0.0" + RBS[0] + p->Simplify(RBS[1], RBS[2])), "UserID = " + User_ID));
						//新订单
						Order NewOrder(p->Order_num, it->Commodity_ID, it->Price, B, p->Date(), Uit->getID(), User_ID);
						p->TranSQL(p->MakeSQL(Insert, F_order, NewOrder.tranS()));

						return;
					}
				}
			}
		}
	}
	else
	{
		cout << "商品ID格式错误！" << endl;
	}


}

void Buyer::SearchCommodities()
{
	cout << "\n请输入您想搜索的商品：";
	string A;
	getline(cin, A);
	bool found = false;
	for (int i = 0; i < p->Commodity_num; i++)
	{
		if (p->commodities[i].FindCommodity(A, M_buyer))
			found = true;
	}
	if (found)
	{
		p->TranSQL(p->MakeSQL(Select, F_commodity, "CommodityName", A), M_buyer);
	}
	else
	{
		cout << "在售商品中未找到该商品！" << endl;

	}

}

void Buyer::ShowMeMore()
{
	cout << "\n请输入您想搜索的商品ID：";
	string ID;
	getline(cin, ID);
	regex CID("[M][0-9]{3}");
	if (regex_match(ID, CID))
	{
		vector <Commodity>::iterator it = find(p->commodities.begin(), p->commodities.end(), ID);
		if (it == p->commodities.end())
		{
			cout << "在售商品中未找到该商品！" << endl;
		}
		else if (it->Removed())
		{
			cout << "在售商品中未找到该商品！" << endl;
		}
		else
		{
			cout << endl;
			cout << "*****************************************************************************************************************\n";
			cout << "CommodityID  CommodityName         Price   Number  Description                               SellerID  SellDate\n";
			p->TranSQL(p->MakeSQL(Select, F_commodity, "CommodityID", ID), M_buyer);
			cout << "*****************************************************************************************************************\n";
		}
	}
	else
	{
		cout << "商品ID格式错误！" << endl;
	}



}

void Buyer::ShowMyOrder()
{
	bool found = false;
	for (int i = 0; i < p->Order_num; i++)
	{
		if (p->orders[i].FindOrder(User_ID, M_buyer))
			found = true;
	}
	if (found)
	{
		cout << endl;
		cout << "*************************************************************\n";
		cout << "OrderID  CommodityID  UnitPrice  Number  SoldDate    SellerID\n";
		p->TranSQL(p->MakeSQL(Select, F_order, "BuyerID", User_ID), M_buyer);
		cout << "*************************************************************\n";
	}
	else
	{
		cout << "抱歉,未找到卖家与您交易的订单！\n";
	}

}

void Buyer::Buyer_Do()
{
	while (1)
	{
		cout << endl << "================================================================================="
			<< "\n1.查看商品列表 2.购买商品 3.搜索商品 4.查看历史订单 5.查看商品信息 6.返回用户界面"
			<< "\n================================================================================="
			<< "\n请输入您的操作：";
		string A;
		char choice;
		string change;
		bool X = false;
		getline(cin, A);
		choice = A[0];
		if (A.length() != 1)
		{
			cout << "输入错误！" << endl;
			continue;
		}
		switch (choice)
		{
		case '1':
			ShowCommodities();
			break;
		case '2':
			BuyCommodities();
			break;
		case '3':
			SearchCommodities();
			break;
		case '4':
			ShowMyOrder();
			break;
		case '5':
			ShowMeMore();
			break;
		case '6':
			return;
			break;
		default:
			cout << "输入错误！" << endl;
			continue;
			break;
		}
	}
}
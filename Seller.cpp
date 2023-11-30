#include "Work.h"
extern Work* p;

Seller::Seller(const User& U)
{
	this->User::operator=(U);
}

void Seller::AddCommodity()
{
	string A[4];
	cout << "请输入您的商品名称（不超过20英文字符）：";
	getline(cin, A[0]);
	cout << "请输入您的商品单价（精确到1位小数）：";
	getline(cin, A[1]);
	cout << "请输入您的商品数量（正整数）：";
	getline(cin, A[2]);
	cout << "请输入您的商品描述（不超过200英文字符）：";
	getline(cin, A[3]);
	cout << endl;
	Commodity NewCommodity(p->Commodity_num, User_ID, p->Date());
	if (NewCommodity.C_judgeinfo(A[0], A[1], A[2], A[3]))
	{
		NewCommodity.C_setinfo(A[0], A[1], A[2], A[3]);
		cout << "请确认发布的商品信息无误！" << endl;
		cout << "********************************************" << endl;
		cout << "商品名称：" << A[0] << endl;
		cout << "商品单价：" << A[1] << endl;
		cout << "商品数量：" << A[2] << endl;
		cout << "商品描述：" << A[3] << endl;
		cout << "********************************************" << endl;
		cout << "请输入Y确认发布该商品：";
		string A;
		getline(cin, A);
		if (A.size() == 1 && A[0] == 'Y')
		{
			cout << "\n商品发布成功！" << endl;
			p->TranSQL(p->MakeSQL(Insert, F_commodity, NewCommodity.tranS()));
		}
		else
		{
			cout << "\n取消发布商品！" << endl;
		}

		return;
	}
	else
	{
		cout << "\n商品发布失败！" << endl;

		return;
	}
}

void Seller::ShowMyCommodity()
{
	bool found = false;
	int size = p->Commodity_num;
	bool* mark = new bool[size];
	for (int i = 0; i < size; i++)
	{
		if (p->commodities[i].FindCommodity(User_ID, M_seller))
		{
			found = true;
			mark[i] = true;
		}
		else
			mark[i] = false;
	}
	if (found)
	{
		cout << endl;
		cout << "************************************************************************************************************************\n";
		cout << "CommodityID  CommodityName         Price   Number  Description                               SellDate    CommodityStatus\n";
		p->TranSQL(p->MakeSQL(Select, F_commodity, "SellerID", User_ID), M_seller);
		cout << "************************************************************************************************************************\n";
	}
	else
	{
		cout << "抱歉,您未发布过商品！\n";

	}
	delete[]mark;


}

void Seller::ChangeCommodity()
{
	string ID;
	cout << "请输入被修改商品的ID：";
	getline(cin, ID);
	regex CID("[M][0-9]{3}");
	if (regex_match(ID, CID))
	{
		vector<Commodity>::iterator it = find(p->commodities.begin(), p->commodities.end(), ID);
		if (it == p->commodities.end() || it->Seller_ID != User_ID)
		{
			cout << "您发布的商品中未找到该商品!" << endl;
		}
		else
		{
			cout << endl;
			cout << "************************************************************************************************************************\n";
			cout << "CommodityID  CommodityName         Price   Number  Description                               SellDate    CommodityStatus\n";
			it->output(M_seller);
			cout << "************************************************************************************************************************\n" << endl;
			cout << "请输入您想要修改的商品信息（1.商品名称 2.商品单价 3.商品描述）：";
			string A;
			char choice;
			getline(cin, A);
			choice = A[0];
			string change;
			bool X = false;
			if (A.length() != 1)
			{
				cout << "输入错误！" << endl;
			}
			else
			{
				switch (choice)
				{
				case '1':
					cout << "请输入修改后的商品名称：";
					getline(cin, change);
					X = it->C_judgeinfo(change);
					if (X)
					{
						cout << "修改成功！\n即将返回卖家菜单……\n";
						p->TranSQL(p->MakeSQL(Update, F_commodity, "CommodityName = " + change, "CommodityID = " + ID), M_seller);
					}
					else
						cout << "修改失败！\n";
					break;
				case '2':
					cout << "请输入修改后的商品单价：";
					getline(cin, change);
					X = it->C_judgeinfo("此字符串为空", change);
					if (X)
					{
						cout << "修改成功！\n即将返回卖家菜单……\n";
						p->TranSQL(p->MakeSQL(Update, F_commodity, "Price = " + change, "CommodityID = " + ID), M_seller);
					}
					else
						cout << "修改失败！\n";
					break;
				/*case '3':
					cout << "请输入修改后的商品数量：";
					getline(cin, change);
					X = it->C_judgeinfo("此字符串为空", "此字符串为空", change);
					if (X)
					{
						cout << "修改成功！\n即将返回卖家菜单……\n";
						p->TranSQL(p->MakeSQL(Update, F_commodity, "Number = " + change, "CommodityID = " + ID), M_seller);
					}
					else
						cout << "修改失败！\n";
					break;*/
				case '3':
					cout << "请输入修改后的商品描述：";
					getline(cin, change);
					X = it->C_judgeinfo("此字符串为空", "此字符串为空", "此字符串为空", change);
					if (X)
					{
						cout << "修改成功！\n即将返回卖家菜单……\n";
						p->TranSQL(p->MakeSQL(Update, F_commodity, "Description = " + change, "CommodityID = " + ID), M_seller);
					}
					else
						cout << "修改失败！\n";
					break;
				default:
					cout << "输入错误！" << endl;
					break;
				}
			}
		}
	}
	else
	{
		cout << "商品ID格式错误！" << endl;
	}

	return;
}

void Seller::CommodityStatus()
{
	string ID;
	cout << "请输入要修改商品的ID：";
	getline(cin, ID);
	regex CID("[M][0-9]{3}");
	if (regex_match(ID, CID))
	{
		vector<Commodity>::iterator it = find(p->commodities.begin(), p->commodities.end(), ID);
		if (it == p->commodities.end())
		{
			cout << "您发布的商品中未找到该商品!" << endl;
		}
		else
		{
			cout << endl;
			cout << "************************************************************************************************************************\n";
			cout << "CommodityID  CommodityName         Price   Number  Description                               SellDate    CommodityStatus\n";
			it->output(M_seller);
			cout << "************************************************************************************************************************\n";
			cout << "是否修改该商品的状态？请输入Y确认: ";
			string A;
			getline(cin, A);
			if (A.size() == 1 && A[0] == 'Y')
			{
				cout << "修改成功！" << endl;
				p->TranSQL(p->MakeSQL(Update, F_commodity, "CommodityStatus = Removed", "CommodityID = " + ID));
			}
			else
			{
				cout << "取消修改!" << endl;
			}
		}
	}
	else
	{
		cout << "商品ID格式错误！" << endl;
	}

}

void Seller::ShowMyOrder()
{
	bool found = false;
	for (int i = 0; i < p->Order_num; i++)
	{
		if (p->orders[i].FindOrder(User_ID, M_seller))
			found = true;
	}
	if (found)
	{
		cout << endl;
		cout << "*************************************************************\n";
			cout << "OrderID  CommodityID  UnitPrice  Number  SoldDate    BuyerID\n";
			p->TranSQL(p->MakeSQL(Select, F_order, "SellerID", User_ID), M_seller);		
		cout << "*************************************************************\n" ;
	}
	else
	{
		cout << "抱歉,未找到买家与您交易的订单！\n";
	}

}

void Seller::Seller_Do()
{
	while (1)
	{
		
		cout<< endl << "====================================================================================="
			<< "\n1.发布商品 2.查看我的商品 3.修改商品信息 4.修改商品状态 5.查看历史订单 6.返回用户界面"
			<< "\n====================================================================================="
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
			AddCommodity();
			break;
		case '2':
			ShowMyCommodity();
			break;
		case '3':
			ChangeCommodity();
			break;
		case '4':
			CommodityStatus();
			break;
		case '5':
			ShowMyOrder();
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

#include "Work.h"
extern Work* p;
//展示所有商品
void Admin::ShowCommodities()
{
	if (p->Commodity_num != 0) 
	{
		p->TranSQL(p->MakeSQL(Select, F_commodity), M_admin);
	}
	else
	{
		cout << "当前无任何商品！" << endl;
	}
	 
}
//搜索商品
void Admin::SearchCommodities()
{
	cout << "\n请输入您想搜索的商品：";
	string A;
	getline(cin, A);
	bool found = false;
	
	for (int i = 0; i < p->Commodity_num; i++)
	{
		if (p->commodities[i].FindCommodity(A, M_admin))
			found = true;			
	}
	if (found)
	{
		p->TranSQL(p->MakeSQL(Select, F_commodity, "CommodityName", A), M_admin);
	}
	else
	{
		cout << "抱歉，没找到该商品！\n";
	}
	 
}
//下架商品
void Admin::DeleteCommodities()
{
	cout << "\n请输入您想下架的商品ID：";
	string ID;
	getline(cin, ID);
	regex CID("[M][0-9]{3}");
	if (regex_match(ID, CID))
	{
		vector <Commodity>::iterator it = find(p->commodities.begin(), p->commodities.end(), ID);

		if (it == p->commodities.end())
		{
			cout << "未找到该商品！" << endl;
		}
		else if (it->Removed())
		{
			cout << "该商品已经下架！" << endl;
		}
		else
		{
			cout << "是否下架该商品？请输入Y确认: ";
			string A;
			getline(cin, A);
			if (A.size() == 1 && A[0] == 'Y')
			{
				cout << "下架成功！" << endl;
				p->TranSQL(p->MakeSQL(Update, F_commodity, "CommodityStatus = Removed", "CommodityID = " + ID));
			}
			else
			{
				cout << "取消下架!" << endl;
			}
		}
	}
	else
	{
		cout << "商品ID格式错误！" << endl;
	}
	 
}
//展示所有订单
void Admin::ShowOrders()
{
	if (p->Order_num != 0)
	{
		cout << endl;
		cout << "**********************************************************************\n";
		cout << "OrderID  CommodityID  UnitPrice  Number  SoldDate    SellerID  BuyerID\n";
		p->TranSQL(p->MakeSQL(Select, F_order), M_admin);
		cout << "**********************************************************************\n" ;
	}
	else
	{
		cout << "当前无任何订单！" << endl;
	}
	 
}
//展示所有用户
void Admin::ShowUsers()
{
	if (p->User_num != 0)
	{
		cout << endl;
		cout << "********************************************************************************************\n";
		cout << "UserID  UserName    Phone               Address                         Balance   UserStatus\n";
		p->TranSQL(p->MakeSQL(Select, F_user), M_admin);
		cout << "********************************************************************************************\n" ;
	}
	else
	{
		cout << "当前无任何用户！" << endl;
	}
	 
}
//封禁用户
void Admin::BanUsers()
{
	cout << "\n请输入您想封禁的用户ID：";
	string ID;
	getline(cin, ID);
	regex UID("[U][0-9]{3}");
	if (regex_match(ID,UID))
	{
		vector <User>::iterator it = find(p->users.begin(), p->users.end(), ID);
		if (it == p->users.end())
		{
			cout << "未找到该用户！" << endl;
		}
		else if (it->User_Status == "inactive")
		{
			cout << "该用户已处于封禁状态！" << endl;
		}
		else
		{
			/*cout << endl;
			cout << "********************************************************************************************\n";
			cout << "UserID  UserName    Phone               Address                         Balance   UserStatus\n";
			it->output(M_admin);
			cout << "********************************************************************************************\n" << endl;
			*/
			cout << "是否封禁该用户？请输入Y确认: ";
			string A;
			getline(cin, A);
			if (A.size() == 1 && A[0] == 'Y')
			{
				cout << "封禁成功！" << endl;
				//封禁用户
				p->TranSQL(p->MakeSQL(Update, F_user, "UserStatus = inactive", "UserID = " + ID));
				//下架商品
				bool found = false;
				for (int i = 0; i < p->Commodity_num; i++)
				{
					if (p->commodities[i].FindCommodity(ID, M_seller))
						found = true;
				}
				if (found) 
					p->TranSQL(p->MakeSQL(Update, F_commodity, "CommodityStatus = Removed", "SellerID = " + ID));
			}
			else
			{
				cout << "取消封禁!" << endl;
			}
		}
	}
	else
	{
		cout << "用户ID格式错误！" << endl;
	}

	 
}


#define _CRT_SECURE_NO_WARNINGS
#include "Work.h"

bool NameUp(Commodity A, Commodity B)
{
	return (A <= B);
}
bool NameDown(Commodity A, Commodity B)
{
	return (A >= B);
}
bool PriceUp(Commodity A, Commodity B)
{
	return (A < B);

}
bool PriceDown(Commodity A, Commodity B)
{
	return (A > B);
}


Work::Work()
{
	User_num = Commodity_num = Order_num = 0;
	fstream X;
	//初始化用户的充值 购买 出售记录文件
	X.open("RBS.txt", ios::in);
	if (!X)
	{
		X.close();
		X.open("RBS.txt", ios::out);
		X << "UserID,Recharge,Buy,Sell" << endl;
		X.close();
	}
	else
	{
		string Y;
		getline(X, Y);
		while (getline(X, Y))
		{
			RBS.push_back(Y);
		}
		X.close();
	}
	//初始化用户文件
	X.open("user.txt", ios::in);
	if (!X)
	{
		X.close();
		X.open("user.txt", ios::out);
		X << "UserID,UserName,Password,Phone,Address,Balance,UserStatus,Qusestion,Answer" << endl;
		X.close();
	}
	else
	{
		string Y;
		getline(X, Y);
		while (getline(X, Y))
		{
			User Z;
			Y = Y + ',' + RBS[User_num];
			Z = Y;
			User_num++;
			users.push_back(Z);
		}
		X.close();

	}
	//初始化商品文件
	X.open("commodity.txt", ios::in);
	if (!X)
	{
		X.close();
		X.open("commodity.txt", ios::out);
		X << "CommodityID,CommodityName,Price,Number,Description,SellerID,SellDate,CommodityStatus" << endl;
		X.close();
	}
	else
	{
		string Y;
		getline(X, Y);
		while (getline(X, Y))
		{
			Commodity_num++;
			Commodity Z;
			Z = Y;
			commodities.push_back(Z);
		}
		X.close();

	}
	//初始化订单文件
	X.open("order.txt", ios::in);
	if (!X)
	{
		X.close();
		X.open("order.txt", ios::out);
		X << "OrderID,CommodityID,UnitPrice,Number,SoldDate,SellerID,BuyerID" << endl;
		X.close();
	}
	else
	{
		string Y;
		getline(X, Y);
		while (getline(X, Y))
		{
			Order_num++;
			Order Z;
			Z = Y;
			orders.push_back(Z);
		}
		X.close();
	}
	//初始化指令文件
	X.open("commands.txt", ios::in);
	if (!X)
	{
		X.close();
		X.open("commands.txt", ios::out);
		X.close();
	}
	else
		X.close();
}
//主菜单
int Work::Menu_main()
{

	cout<< "========================================================"
		<< "\n1.管理员登录 2.用户登录 3.用户注册 4.忘记密码 5.退出平台"
		<< "\n========================================================"
		<< "\n请输入您的操作：";
	string A;
	char choice;
	int B;
	getline(cin, A);
	choice = A[0];
	if (A.length() != 1)
	{
		cout << "输入错误！" << endl;
		return -1;
	}
	switch (choice)
	{
	case '1':
		if (Admin_Login())
			return M_admin;
		else
			return -1;
		break;
	case '2':
		B = User_Login();
		if (B >= 0)
			return M_user + B * 10;
		else
			return -1;
		break;
	case '3':
		User_Register();
		return -1;
		break;
	case '4':
		forget();
		return -1;
	case '5':
		cout << "欢迎下次使用！" << endl;
		exit(-1);
		break;
	default:
		cout << "输入错误！" << endl;
		return -1;
		break;
	}
}
//管理员菜单
void Work::Menu_admin()
{
	while (1)
	{

		cout << endl << "===================================================================================="
			<< "\n1.查看所有商品 2.搜索商品 3.下架商品 4.查看所有订单 5.查看所有用户 6.封禁用户 7.注销"
			<< "\n===================================================================================="
			<< "\n请输入您的操作：";
		Admin admin;
		string A = "0";
		char choice;
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
			admin.ShowCommodities();
			break;
		case '2':
			admin.SearchCommodities();
			break;
		case '3':
			admin.DeleteCommodities();
			break;
		case '4':
			admin.ShowOrders();
			break;
		case '5':
			admin.ShowUsers();
			break;
		case '6':
			admin.BanUsers();
			break;
		case '7':
			cout << "是否注销账号？请输入Y进行确认: ";
			getline(cin, A);
			if (A.size() == 1 && A[0] == 'Y')
			{
				cout << "\n注销成功，即将返回主菜单！" << endl;

				return;
			}
			break;
		default:
			cout << "输入错误!" << endl;

			break;
		}
	}
}
//用户菜单
void Work::Menu_user(int num)
{
	while (1)
	{

		cout << endl << "=========================================================="
			<< "\n1.我是买家 2.我是卖家 3.个人信息管理 4.修改密码 5.注销账号"
			<< "\n==========================================================" 
			<< "\n请输入您的操作：";
		User Me = users[num];
		string A;
		char choice;
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
			//买家
		{
			Buyer me(Me);
			me.Buyer_Do();
			break;
		}
		case '2':
			//卖家
		{
			Seller me(Me);
			me.Seller_Do();
			break;
		}
		case '3':
			if (Me.Info_Do())
			{
				users.erase(users.begin() + num);
				users.insert(users.begin() + num, Me);
				File_save(F_user);
			}
			break;
		case'4':
			if (Me.change())
			{
				users.erase(users.begin() + num);
				users.insert(users.begin() + num, Me);
				File_save(F_user);
			}
			break;
		case '5':
			cout << "是否注销账号？请输入Y进行确认: ";
			getline(cin, A);
			if (A.size() == 1 && A[0] == 'Y')
			{
				cout << "\n注销成功，即将返回主菜单！" << endl;

				return;
			}
			break;
		default:
			cout << "输入错误！" << endl;

			break;
		}
	}
}
//管理员登录
bool Work::Admin_Login()
{
	while (1)
	{

		cout << endl << "=========================================================="
			<< "\n                      管理员登陆界面                      "
			<< "\n=========================================================="
			<< "\n管理员用户名：";
		string Name = "0";
		getline(cin, Name);
		cout << "请输入密码：";
		string Key = "0";
		getline(cin, Key);
		if (Name == "Admin" && Key == "123456")
		{
			cout << "\n登录管理员成功！" << endl;
			return true;
		}
		else
		{
			cout << "\n用户名/密码错误！" << endl
				<< "请输入Y进行重新输入，否则将返回到登录界面：" ;
			string A;
			getline(cin, A);
			if (A[0] == 'Y' && A.size() == 1)
				continue;
			else
			{
				return false;
			}
		}
	}
}
//用户登录
int Work::User_Login()
{
	while (1)
	{

		string Name, Pass;
		int i = 0;
		bool find = false;
		cout << endl << "=========================================================="
			<< "\n                       用户登录界面                       "
			<< "\n==========================================================" << endl;
		cout << "请输入您的用户名：";
		getline(cin, Name);
		cout << "请输入您的密码：";
		getline(cin, Pass);

		for (; i < User_num; i++)
		{
			int result = users[i].Login(Name, Pass);
			if (result == 0)
				continue;
			else if (result == 1)
			{
				cout << "登录成功！" << endl;

				return i;
			}
			else if (result == 2)
			{
				cout << "登录失败，该账号已被封禁！" << endl;
				find = true;
				break;
			}
			else if (result == 3)
				break;
		}
		if (!find)
		{
			cout << "登录失败，用户名不存在或密码错误！\n" << endl;
		}
		cout << "是否重新登录？输入Y进行确认:";
		string A;
		getline(cin, A);
		if (A.size() == 1 && A[0] == 'Y')
			continue;
		else
			return -1;
	}
}
//用户注册
void Work::User_Register()
{
	User NewUser(User_num);
	while (1)
	{

		string A[6];
		cout << endl << "=========================================================="
			<< "\n                       用户注册界面                       "
			<< "\n=========================================================="
			<< "\n请输入您的用户名（英文字母 不超过10字符）：";
		getline(cin, A[0]);
		cout << "请输入您的密码（小写字母/数字 不超过20字符）：";
		getline(cin, A[1]);
		cout << "请输入您的联系方式（数字 不超过20字符）：";
		getline(cin, A[2]);
		cout << "请输入您的地址（英文字母 不超过40字符）：";
		getline(cin, A[3]);
		cout << endl;
		if (NewUser.U_setinfo(A[0], A[1], A[2], A[3]))
		{

			cout << "\n注册成功！";
			cout << "\n为了您的账号安全，请输入您的密保问题：";
			getline(cin, A[4]);
			cout << "请输入您的密保问题的答案：";
			getline(cin, A[5]);
			cout << endl;
			for (int i = (A[4].length() > A[5].length() ? A[4].length() : A[5].length()) + 5; i >= 0; i--)
				cout << "-";
			cout << "\n密保问题：" << A[4];
			cout << "\n密保答案：" << A[5]<<endl;
			for (int i = (A[4].length() > A[5].length() ? A[4].length() : A[5].length()) + 5; i >= 0; i--)
				cout << "-";
			cout << "\n密保设置成功！请牢记您的密保问题";
			NewUser.SetQuestion(A[4], A[5]);
			cout << "\n即将返回主菜单……" << endl;
			users.push_back(NewUser);
			NewUser.DoRBS();
			User_num++;
			File_save(F_user);

			return;
		}
		else
		{
			cout << "\n注册失败！";
			cout << "是否重新输入？请输入Y进行确认：";
			string A;
			getline(cin, A);
			if (A[0] == 'Y' && A.size() == 1)
				continue;
			else
			{
				return;
			}

			continue;
		}
	}

}
//存一类 全存
void Work::File_save(int File)
{
	fstream X;
	switch (File)
	{
	case F_user:
		X.open("user.txt", ios::out | ios::trunc);
		X << "UserID,UserName,Password,Phone,Address,Balance,UserStatus,Qusestion,Answer" << endl << users;
		break;
	case F_commodity:
		X.open("commodity.txt", ios::out | ios::trunc);
		X << "CommodityID,CommodityName,Price,Number,Description,SellerID,AddedDate,CommodityStatus" << endl << commodities;
		break;
	case F_order:
		X.open("order.txt", ios::out | ios::trunc);
		X << "OrderID,CommodityID,UnitPrice,Number,SoldDate,SellerID,BuyerID" << endl << orders;
		break;
	case F_RBS:
		X.open("RBS.txt", ios::out | ios::trunc);
		X << "UserID,Recharge,Buy,Sell" << endl;
		for (int i = 0; i < RBS.size(); i++)
		{
			X << RBS[i];
			if (i != RBS.size())
				X << endl;
		}
		break;
	}
}
//获取时间
string Work::Time()
{
	char Time[9];
	const tm* T;
	time_t now;
	time(&now);
	T = localtime(&now);
	strftime(Time, 9, "%H:%M:%S", T);
	string time = Time;
	time = Date() + ' ' + time + ':';
	return time;
}
//获取日期
string Work::Date()
{
	char Date[11];
	const tm* T;
	time_t now;
	time(&now);
	T = localtime(&now);
	strftime(Date, 11, "%Y-%m-%d", T);
	string date = Date;
	return date;
}
//指令系统
string Work::MakeSQL(int choice, int TXT, string A, string B)
{
	string newSQL = Time();
	if (TXT == F_user)
	{
		newSQL += " user ";
	}
	else if (TXT == F_commodity)
	{
		newSQL += " commodity ";
	}
	else if (TXT == F_order)
	{
		newSQL += " order ";
	}
	if (choice == Select)
	{
		newSQL.insert(20, " SELECT * FROM");
		if (A != " ")
		{
			newSQL = newSQL + "WHERE " + A + " CONTAINS " + B;
		}
	}
	else if (choice == Update)
	{
		newSQL.insert(20, " UPDATE");
		newSQL += "SET ";
		newSQL = newSQL + A + " WHERE " + B;
	}
	else if (choice == Insert)
	{
		newSQL.insert(20, " INSERT INTO");
		newSQL += "VALUES (";
		newSQL += A;
		newSQL += ')';
	}
	fstream X;
	X.open("commands.txt", ios::app);
	X << newSQL << endl;
	X.close();
	return newSQL.substr(21);
}
void Work::TranSQL(string sql, int Menu)
{

	//select
	if (sql[0] == 'S')
	{
		string Where, Contain;
		sql.erase(0, 14);
		if (sql[0] == 'c')
		{
			vector<Commodity> MakeSort;
			sql.erase(0, 9);
			//商品选择性展示
			if (sql.size() > 1)
			{
				sql.erase(0, 7);
				int position = sql.find(" CONTAINS ");
				Contain = sql.substr(position + 10);
				Where = sql.erase(position, Contain.size() + 10);
				if (Where == "CommodityID")
				{
					vector <Commodity>::iterator it = find(commodities.begin(), commodities.end(), Contain);
					it->output(M_buyer, true);
				}
				else if (Where == "SellerID")
				{
					for (int i = 0; i < Commodity_num; i++)
					{
						if (commodities[i].FindCommodity(Contain, M_seller))
							commodities[i].output(M_seller);
					}
				}
				else if (Where == "CommodityName")
				{
					if (Menu == M_admin)
					{
						cout << endl;
						cout << "**********************************************************************************************************************************\n";
						cout << "CommodityID  CommodityName         Price   Number  Description                               SellerID  SellDate    CommodityStatus\n";
						for (int i = 0; i < Commodity_num; i++)
						{
							if (commodities[i].FindCommodity(Contain, M_admin))
							{
								commodities[i].output(M_admin);
								MakeSort.push_back(commodities[i]);
							}
						}
						cout << "**********************************************************************************************************************************\n";
						SortCommodity(MakeSort, Menu);
					}
					else if (Menu == M_buyer)
					{
						cout << endl;
						cout << "************************************************************************\n";
						cout << "CommodityID  CommodityName         Price   Number  SellerID  SellDate   \n";
						for (int i = 0; i < Commodity_num; i++)
						{
							if (commodities[i].FindCommodity(Contain, M_buyer))
							{
								commodities[i].output(M_buyer);
								MakeSort.push_back(commodities[i]);
							}
						}
						cout << "************************************************************************\n";

						SortCommodity(MakeSort, Menu);
					}
				}
			}
			//商品全展示 （管理员/买家）
			else
			{
				MakeSort = commodities;
				if (Menu == M_admin)
				{
					cout << endl;
					cout << "**********************************************************************************************************************************\n";
					cout << "CommodityID  CommodityName         Price   Number  Description                               SellerID  SellDate    CommodityStatus\n";
					for (int i = 0; i < Commodity_num; i++)
						commodities[i].output(M_admin);
					cout << "**********************************************************************************************************************************\n";
					SortCommodity(MakeSort, Menu);
				}
				else
				{
					cout << endl << "************************************************************************\n";
					cout << "CommodityID  CommodityName         Price   Number  SellerID  SellDate   \n";
					for (int i = 0; i < Commodity_num; i++)
						commodities[i].output(M_buyer);
					cout << "************************************************************************\n";
					SortCommodity(MakeSort, Menu);
				}

			}
		}
		else if (sql[0] == 'u')
		{
			for (int i = 0; i < User_num; i++)
				users[i].output(M_admin);

		}
		else if (sql[0] == 'o')
		{
			sql.erase(0, 5);
			if (sql.size() > 1)
			{
				sql.erase(0, 7);
				int contain = sql.find(" CONTAINS ");
				Contain = sql.substr(contain + 10);
				Where = sql.erase(contain, Contain.size() + 10);
				if (Where == "SellerID")
				{
					for (int i = 0; i < Order_num; i++)
					{
						if (orders[i].FindOrder(Contain, M_seller))
							orders[i].output(M_seller);
					}
				}
				else if (Where == "BuyerID")
				{
					for (int i = 0; i < Order_num; i++)
					{
						if (orders[i].FindOrder(Contain, M_buyer))
							orders[i].output(M_buyer);
					}
				}
			}
			else
			{
				for (int i = 0; i < Order_num; i++)
					orders[i].output(M_admin);
			}
		}
	}
	//update
	else if (sql[0] == 'U')
	{
		string Where, Set;
		string Where1, Where2, Set1, Set2;
		sql.erase(0, 7);
		if (sql[0] == 'c')
		{
			sql.erase(0, 14);
			int position = sql.find(" WHERE ");
			Where = sql.substr(position + 7);
			Set = sql.erase(position, Where.size() + 7);
			position = Where.find(" = ");
			Where2 = Where.substr(position + 3);
			Where1 = Where.erase(position, Where2.size() + 3);
			position = Set.find(" = ");
			Set2 = Set.substr(position + 3);
			Set1 = Set.erase(position, Set2.size() + 3);
			if (Where1 == "SellerID")
			{
				for (int i = 0; i < Commodity_num; i++)
				{
					if (commodities[i].FindCommodity(Where2, M_seller) && !commodities[i].Removed())
						commodities[i].StatusTran();
				}
			}
			else if (Where1 == "CommodityID")
			{
				vector<Commodity>::iterator it = find(commodities.begin(), commodities.end(), Where2);
				if (Set1 == "CommodityName")
					it->C_setinfo(Set2);
				else if (Set1 == "Price")
					it->C_setinfo("此字符串为空", Set2);
				else if (Set1 == "Number")
					it->C_setinfo("此字符串为空", "此字符串为空", Set2);
				else if (Set1 == "Description")
					it->C_setinfo("此字符串为空", "此字符串为空", "此字符串为空", Set2);
				else if (Set1 == "CommodityStatus")
					it->StatusTran();
			}

			File_save(F_commodity);
		}
		else if (sql[0] == 'u')
		{
			sql.erase(0, 9);
			int position = sql.find(" WHERE ");
			Where = sql.substr(position + 7);
			position = Where.find(" = ");
			Where2 = Where.substr(position + 3);
			vector <User>::iterator it = find(users.begin(), users.end(), Where2);
			if (sql.find("Balance") != -1)
				it->DoRBS();
			else if (sql.find("UserStatus") != -1)
				it->StatusTran();
			File_save(F_user);
		}
	}
	//insert
	else if (sql[0] == 'I')
	{
		sql.erase(0, 12);
		if (sql[0] == 'c')
		{
			sql.erase(0, 18);
			sql.erase(sql.size() - 1, 1);
			Commodity Newcommodity;
			Newcommodity = sql;
			commodities.push_back(Newcommodity);
			Commodity_num++;
			File_save(F_commodity);
		}
		else if (sql[0] == 'o')
		{
			sql.erase(0, 14);
			sql.erase(sql.size() - 1, 1);
			Order Neworder;
			Neworder = sql;
			orders.push_back(Neworder);
			Order_num++;
			File_save(F_order);
		}
	}
}

void Work::SortCommodity(vector<Commodity>  C , int Menu)
{
	while (1)
	{
		cout << "是否对上表重新排列?请输入选择(1.按商品名称升序 2.按商品名称降序 3.按单价升序 4.按单价降序 输入其他退出)：";
		string choice= "   ";
		getline(cin, choice);
		if (choice.length() == 1)
		{
			char a = choice[0];
			switch (a)
			{
			case '1':
				sort(C.begin(), C.end(), NameUp);
				break;
			case '2':
				sort(C.begin(), C.end(), NameDown);
				break;
			case '3':
				sort(C.begin(), C.end(), PriceUp);
				break;
			case '4':
				sort(C.begin(), C.end(), PriceDown);
				break;
			default:
				return;
				break;
			}
			cout << endl;
			if (Menu == M_buyer) 
			{
				cout << "************************************************************************\n";
				cout << "CommodityID  CommodityName         Price   Number  SellerID  SellDate   \n";
				for (int i = 0; i < C.size(); i++)
				{
					C[i].output(Menu);
				}
				cout << "************************************************************************\n";

			}
			else if (Menu == M_admin)
			{
				cout << "**********************************************************************************************************************************\n";
				cout << "CommodityID  CommodityName         Price   Number  Description                               SellerID  SellDate    CommodityStatus\n";
				for (int i = 0; i < C.size(); i++)
				{
					C[i].output(Menu);
				}
				cout << "**********************************************************************************************************************************\n";
			}

		}
		else
		{
			return;
		}
	}
}

void Work::forget()
{
	string Name,answer;
	int num = -1;
	cout << endl << "=========================================================="
		<< "\n                       账号找回界面                       "
		<< "\n==========================================================" << endl;
	cout << "请输入您的用户名：";
	getline(cin, Name);
	for (int i = 0; i < users.size(); i++)
	{
		if (Name == users[i].getName())
		{
			num = i;
			break;
		}
	}
	if (num == -1)
	{
		cout << "\n该用户不存在！" << endl;
	}
	else
	{
		if (users[num].change())
		{
			File_save(F_user);
		}
	}
}



//三个类的重载<<
ostream& operator << (ostream& X, User& a)
{
	X << a.User_ID << "," << a.User_Name << "," << a.Password << "," << a.Phone << "," << a.Address << "," << a.Balance << "," << a.User_Status << "," << a.Question << ","<<a.Answer;
	return X;
}
ostream& operator << (ostream& X, vector<User> A)
{
	for (int i = 0; i < A.size(); i++)
	{
		X << A[i];
		if (i != A.size())
			X << endl;
	}
	return X;
}
ostream& operator << (ostream& X, Commodity& a)
{
	X << a.Commodity_ID << "," << a.Commodity_Name << "," << a.Price << "," << a.Number << "," << a.Description << "," << a.Seller_ID << "," << a.Added_Date << "," << a.Commodity_Status;
	return X;
}
ostream& operator << (ostream& X, vector<Commodity> A)
{
	for (int i = 0; i < A.size(); i++)
	{
		X << A[i];
		if (i != A.size())
			X << endl;
	}
	return X;
}
ostream& operator << (ostream& X, Order& a)
{
	X << a.Order_ID << "," << a.Commodity_ID << "," << a.UnitPrice << "," << a.Number << "," << a.Sold_Date << "," << a.Seller_ID << "," << a.Buyer_ID;
	return X;
}
ostream& operator << (ostream& X, vector<Order> A)
{
	for (int i = 0; i < A.size(); i++)
	{
		X << A[i];
		if (i != A.size())
			X << endl;
	}
	return X;
}

string Work::Simplify(string B, string A)
{
	vector <string> Price, Num;
	int count = 0;
	string num, price;
	bool X = true;
	for (int i = 0; i < A.size(); i++)
	{
		X = true;
		if (A[i] == '+')
		{
			num.clear();
			for (int j = ++i; A[j] != '*'; j++)
			{
				i++;
				num += A[j];
			}
			if (count != 0)
			{
				for (int j = 0; j < count; j++)
				{
					if (num == Num[j])
						X = false;
				}
			}
			if (X)
			{
				count++;
				Num.push_back("");
				Price.push_back("");
				Num[count - 1] = num;
			}
		}
		if (A[i] == '*')
		{
			price.clear();
			for (int j = ++i; A[j] != '+' && j < A.size(); j++)
			{
				i++;
				price += A[j];
			}
			for (int j = 0; j < count; j++)
			{
				if (num == Num[j])
				{
					Price[j] += '+' + price;
				}
			}
		}
		i--;

	}
	for (int i = 0; i < B.size(); i++)
	{
		X = true;
		if (B[i] == '-')
		{
			num.clear();
			for (int j = ++i; B[j] != '*'; j++)
			{
				i++;
				num += B[j];
			}
			if (count != 0)
			{
				for (int j = 0; j < count; j++)
				{
					if (num == Num[j])
						X = false;
				}
			}
			if (X)
			{
				count++;
				Num.push_back("");
				Price.push_back("");
				Num[count - 1] = num;
			}
		}
		if (B[i] == '*')
		{
			price.clear();
			for (int j = ++i; B[j] != '-' && j < B.size(); j++)
			{
				i++;
				price += B[j];
			}
			for (int j = 0; j < count; j++)
			{
				if (num == Num[j])
				{
					Price[j] += '-' + price;
				}
			}
		}
		i--;
	}
	string simple;
	for (int i = 0; i < count; i++)
	{
		if (Price[i][0] == '+')
		{
			simple += '+' + Num[i] + "*(" + Price[i].erase(0, 1) + ')';
		}
		else if (Price[i][0] == '-')
		{
			for (int j = 0; j < Price[i].size(); j++)
			{
				if (Price[i][j] == '-')
				{
					Price[i][j] = '+';
				}
			}
			simple += '-' + Num[i] + "*(" + Price[i].erase(0, 1) + ')';
		}
	}
	int left= 0, right=0;
	bool Delete;
	for (int i = 0; i < simple.size(); i++)
	{
		if (simple[i] == '(')
		{
			Delete = true;
			left = i;
			for (int j = ++i; j < simple.size(); j++, i++)
			{
				if (simple[j] == '+' || simple[j] == '-')
				{
					Delete = false;
				}
				if (simple[j] == ')')
				{
					right = j;
					break;
				}

			}
			if (Delete)
			{
				simple = simple.erase(right, 1).erase(left, 1);
			}
		}

	}
	return simple;
}


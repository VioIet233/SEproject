#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <algorithm>
#include "User.h"
#include "Commodity.h"
#include "Order.h"
#include "Admin.h"
#include "Calculator.h"
#include "Buyer.h"
#include "Seller.h"
using namespace std;
enum MENU { M_admin = 1, M_user, M_buyer, M_seller };
enum TXT { F_user = 1, F_commodity, F_order, F_RBS };
enum SQL { Select = 1, Update, Insert };
class Work
{
public:
	Work();
	//主菜单
	int Menu_main();
	//管理员菜单
	void Menu_admin();
	//用户菜单
	void Menu_user(int num);
	//管理员登陆
	bool Admin_Login();
	//用户登录
	int User_Login();
	//用户注册
	void User_Register();
	//存储文件
	void File_save(int a);
	string Time();
	//获取日期
	string Date();
	//指令系统
	string MakeSQL(int choice, int TXT, string A = " ", string B = " ");
	void TranSQL(string sql, int Menu = 0);
	//商品排序
	void SortCommodity(vector<Commodity>  C , int menu);
	//化简算式
	string Simplify(string A, string B);
	//忘记密码
	void forget();
	vector <User> users;
	vector <Commodity> commodities;
	vector <Order> orders;
	vector <string> RBS;
	int User_num;
	int Commodity_num;
	int Order_num;
};

//重载User类及vector的<<
ostream& operator << (ostream& X, User& a);
ostream& operator << (ostream& X, vector<User> A);
//重载Commodity类及vector的<<
ostream& operator << (ostream& X, Commodity& a);
ostream& operator << (ostream& X, vector<Commodity> A);
//重载Order类及vector的<<
ostream& operator << (ostream& X, Order& a);
ostream& operator << (ostream& X, vector<Order> A);


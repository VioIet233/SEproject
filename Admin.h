#pragma once
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

class Admin
{
public:
	//展示所有商品
	void ShowCommodities();
	//搜索商品
	void SearchCommodities();
	//下架商品
	void DeleteCommodities();
	//展示所有订单
	void ShowOrders();
	//展示所有用户
	void ShowUsers();
	//封禁用户
	void BanUsers();
	
};

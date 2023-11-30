#pragma once
#include "User.h"

class Seller : public User
{
public:
	Seller() {};
	~Seller() {};
	Seller(const User& U);
	void Seller_Do();
	void AddCommodity();
	void ShowMyCommodity();
	void ChangeCommodity();
	void CommodityStatus();
	void ShowMyOrder();
};



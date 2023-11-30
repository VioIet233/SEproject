#pragma once
#include "User.h"

class Buyer : public User
{
public:
	Buyer() {};
	~Buyer() {}
	Buyer(const User& U);
	void Buyer_Do();
	void ShowCommodities();
	void SearchCommodities();
	void BuyCommodities();
	void ShowMeMore();
	void ShowMyOrder();
};
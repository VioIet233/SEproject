#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <regex>
#include "Admin.h"
using namespace std;
class User
{
	friend void Admin::BanUsers();
	friend ostream& operator << (ostream& X, User& a);
public:
	User();
	~User();
	void operator= (string& Y);
	User& operator= (const User& U);
	bool operator == (string ID);
	string& operator[](int i);
	User(int Usernum);
	bool U_setinfo( string a0 = "此字符串为空", string a1 = "此字符串为空", string a2 = "此字符串为空", string a3 = "此字符串为空");
	void SetQuestion(string question, string answer);
	void DoRBS();
	void output(int Menu);
	int Login(string Name, string Pass);
	bool Info_Do();
	void StatusTran();
	string getID();
	string getName();
	bool change();
protected:
	string User_ID;
	string Balance;
	string RBS[3];
private:
	string User_Name;
	string Password;
	string Phone;
	string Address;
	string User_Status;
	string Question;
	string Answer;
};


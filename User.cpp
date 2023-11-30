#include "Work.h"
extern Work* p;

User::User()
{
	User_ID = "";
	Balance = "";
	User_Name = "";
	Password = "";
	Phone = "";
	Address = "";
	User_Status = "";
	RBS[0] = "";
	RBS[1] = "";
	RBS[2] = "";
}
User::~User()
{
}
void User::operator= (string& Y)
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
				User_ID += Y[i];
				break;
			case 1:
				User_Name += Y[i];
				break;
			case 2:
				Password += Y[i];
				break;
			case 3:
				Phone += Y[i];
				break;
			case 4:
				Address += Y[i];
				break;
			case 5:
				Balance += Y[i];
				break;
			case 6:
				User_Status += Y[i];
				break;
			case 7:
				Question += Y[i];
				break;
			case 8:
				Answer += Y[i];
				break;
			case 9:
				break;
			case 10:
				RBS[0] += Y[i];
				break;
			case 11:
				RBS[1] += Y[i];
				break;
			case 12:
				RBS[2] += Y[i];
				break;
			}
		}

	}
}

User& User::operator= (const User& U)
{
	User_ID = U.User_ID;
	Balance = U.Balance;
	User_Name = U.User_Name;
	Password = U.Password;
	Phone = U.Phone;
	Address = U.Address;
	User_Status = U.User_Status;
	RBS[0] = U.RBS[0];
	RBS[1] = U.RBS[1];
	RBS[2] = U.RBS[2];
	return *this;
}

string& User::operator[](int i)
{
	switch (i)
	{
	case 0 :
		return RBS[0];
		break;
	case 1:
		return RBS[1];
		break;
	case 2:
		return RBS[2];
		break;
	default:
		break;
	}
	return RBS[0];
}

User::User(int Usernum)
{
	User_ID = "U";
	User_ID += (char)(Usernum / 100 + 48);
	User_ID += (char)(Usernum / 10 % 10 + 48);
	User_ID += (char)(Usernum % 10 + 49);
	Balance = "0.0";
	User_Status = "active";

}

bool User::U_setinfo(string a0, string a1, string a2, string a3)
{
	bool X = true;
	//检验用户名是否规范
	if (a0 != "此字符串为空")
	{
		regex name("[a-zA-Z]{1,10}");
		if (!regex_match(a0, name))
		{
			cout << "用户名格式错误！" << endl;
			X = false;
		}
		for (vector<User>::iterator it = p->users.begin(); it != p->users.end(); it++)
		{
			if (a0 == it->User_Name)
			{
				cout << "错误！已存在该用户名！" << endl;
				X = false;
				break;
			}
		}

	}
	//检验密码是否规范
	if (a1 != "此字符串为空")
	{
		regex password("[a-z0-9]{1,20}");
		if (!regex_match(a1, password))
		{
			cout << "密码格式错误！" << endl;
			X = false;
		}

	}
	//检验联系方式是否规范
	if (a2 != "此字符串为空")
	{
		regex phone("[0-9]{1,20}");
		if (!regex_match(a2, phone))
		{
			cout << "联系方式格式错误！" << endl;
			X = false;
		}
	}
	//检验地址是否规范
	if (a3 != "此字符串为空")
	{
		regex address("[a-zA-Z]{1,40}");
		if (!regex_match(a3, address))
		{
			cout << "地址格式错误！" << endl;
			X = false;
		}
	}
	if (X)
	{
		User_Name = (a0 == "此字符串为空" ? User_Name : a0);
		Password = (a1 == "此字符串为空" ? Password : a1);
		Phone = (a2 == "此字符串为空" ? Phone : a2);
		Address = (a3 == "此字符串为空" ? Address : a3);
	}
	return X;
}

void User::SetQuestion(string question, string answer)
{
	Question = question;
	Answer = answer;
}

bool User::operator == (string ID)
{
	if (ID == User_ID)
		return true;
	else
		return false;
}

void User::DoRBS()
{
	for (int i = 0; i < p->User_num; i++)
	{
		if (User_ID == p->RBS[i].substr(0, 4))
		{
			Balance = calculator("0.0" + RBS[0] + p->Simplify(RBS[1], RBS[2]));
			p->users[i].Balance = Balance;
			p->RBS.erase(p->RBS.begin() + i);
			p->RBS.insert(p->RBS.begin() + i, User_ID + ',' + RBS[0] + ',' + RBS[1] + ',' + RBS[2]);
			p->File_save(F_RBS);
			return;
		}
	}
	p->RBS.push_back(User_ID + ",,,");
	p->File_save(F_RBS);
}

void User::output(int Menu)
{
	//"UserID  UserName    Phone               Address                         Balance   UserStatus\n";
	//"U001    Z           123123123123123123  askdljasdasd                    10.1      active
	cout << User_ID << "    ";
	cout << User_Name << "  ";
	for (int i = 0; i < 10 - User_Name.size(); i++)
		cout << ' ';
	cout << Phone << "  ";
	for (int i = 0; i < 18 - Phone.size(); i++)
		cout << ' ';
	cout << Address << "  ";
	for (int i = 0; i < 30 - Address.size(); i++)
		cout << ' ';
	cout << Balance << "  ";
	for (int i = 0; i < 8 - Balance.size(); i++)
		cout << ' ';
	if (Menu == 1)
		cout << User_Status;
	cout << endl;
}

int User::Login(string Name, string Pass)
{
	if (Name == User_Name)
	{
		if (Pass == Password)
		{
			if (User_Status == "active")
				return 1;
			else
				return 2;
		}
		else
			return 3;
	}
	else
		return 0;

}

bool User::Info_Do()
{
	while (1)
	{
		cout << endl << "==========================================="
			<< "\n1.显示信息 2.修改信息 3.充值 4.返回用户界面"
			<< "\n==========================================="
			<< "\n请输入您的操作：";
		string A;
		char choice;
		string change;
		bool X = false;
		regex Money1("[0-9]{1,}[.][0-9]");
		regex Money2("[0-9]{1,}");
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
			cout << "您的信息如下：\n" << endl;
			cout << "*******************************************************************************\n";
			cout << "UserID  UserName    Phone               Address                         Balance\n";
			output(2);
			cout << "*******************************************************************************\n";
			 
			break;
		case '2':

			cout << "---------------------------------\n";
			cout << "1.用户名 2.密码 3.联系方式 4.地址\n";
			cout << "---------------------------------\n";
			cout << "请输入您想修改的信息类别：";
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
				cout << "请输入修改后的用户名：";
				getline(cin, change);
				X = this->U_setinfo(change);
				if (X)
				{
					cout << "修改成功！\n即将返回用户菜单……\n";
					 
					return 1;
				}
				else
				{
					cout << "修改失败！\n";
					  continue;
				}
				break;
			case '2':
				cout << "请输入修改后的密码：";
				getline(cin, change);
				X = this->U_setinfo("此字符串为空", change);
				if (X)
				{
					cout << "修改成功！\n即将返回用户菜单……\n";
					 
					return 1;
				}
				else
				{
					cout << "修改失败！\n";
					  continue;
				}
				break;
			case '3':
				cout << "请输入修改后的联系方式：";
				getline(cin, change);
				X = this->U_setinfo("此字符串为空", "此字符串为空", change);
				if (X)
				{
					cout << "修改成功！\n即将返回用户菜单……\n"; 
					return 1;
				}
				else
				{
					cout << "修改失败！\n";
					  continue;
				}
				break;
			case '4':
				cout << "请输入修改后的地址：";
				getline(cin, change);
				X = this->U_setinfo("此字符串为空", "此字符串为空", "此字符串为空", change);
				if (X)
				{
					cout << "修改成功！\n即将返回用户菜单……\n";					 
					return 1;
				}
				else
				{
					cout << "修改失败！地址格式错误！\n";
					  continue;
				}
				break;
			default:
				cout << "输入错误！" << endl; 
				break;
			}
			break;
		case '3':
			cout << "请输入充值金额(正数，整数/保留一位小数)：";
			getline(cin, change);
			if (regex_match(change, Money1) || regex_match(change, Money2))
			{
				cout << "充值成功！" << endl;
				 
				RBS[0] += "+" + change;
				DoRBS();
				p->File_save(F_user);
			}
			else
			{
				cout << "充值失败，输入错误！\n";
				 
			}
			break;
		case '4':
			return 0;
			break;
		default:
			cout << "输入错误！" << endl;
			 
			continue;
			break;
		}

	}
}

void User::StatusTran()
{
	User_Status = "inactive";
	//User_Status == "active" ? "inactive" : "active";
}

string User::getID()
{
	return User_ID;
}

string User::getName()
{
	return User_Name;
}

bool User::change()
{
	cout << "\n您的密保问题是：" << Question;
	cout << "\n请输入您的答案：";
	string answer,password;
	getline(cin, answer);
	if (answer == Answer)
	{
		while (1)
		{
			cout << "\n请输入新密码：";
			getline(cin, password);
			if (U_setinfo("此字符串为空", password))
			{
				cout << "\n修改成功！" << endl;
				return true;
			}
			else
			{
				cout << "\n修改失败！" << endl;
				cout << "是否重新输入？输入Y进行确认:";
				string A;
				getline(cin, A);
				if (A.size() == 1 && A[0] == 'Y')
					continue;
				else
					return false;
			}
		}
	}
	else
	{
		cout << "\n答案错误！" << endl;
		return false;
	}

}
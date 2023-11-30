#include "Calculator.h"

string calculator(string A)
{
	int correct = Calcul_Judge(A);
	switch (correct)
	{
	case 1:
		return"数字格式有误！";
		break;
	case 2:
		return"圆括号使用有误！";
		break;
	case 3:
		return "算式中无数字！";
		break;
	case 4:
		return"算式格式有误！";
	default:
		break;
	}
	vector <string> B = Calcultran(A);
	vector<string> suffix = Suffix(B);
	return Calcul_Suffix(suffix);
}
//初步判断 小数点 空格 括号 是否规范
int Calcul_Judge(string& A)
{
	int Left = 0, Right = 0;
	bool Num_con = false;
	for (int i = 0; i < A.size(); i++)
	{
		if (Num(A[i]) && !Num_con)
		{
			Num_con = true;
		}
		if (!Num(A[i]) && A[i] != '(' && A[i] != ')' && A[i] != ' ' && A[i] != '.' && A[i] != '/' && A[i] != '+' && A[i] != '-' && A[i] != '*')
		{
			return form_;
		}
		if (A[0] == '.' || A[A.size() - 1] == '.')
		{
			return num_;
		}
		if (A[0] == ' ')
		{
			A.erase(A.begin());
			i--;
		}
	}
	if (!Num_con)
		return nonum_;
	for (int i = 0; i < A.size(); i++)
	{
		if (A[i] == '.')
		{
			if (Num(A[1 + i]) && Num(A[i - 1]) && !Num(A[i + 2])) {}
			else
			{
				return num_;
			}
		}
		else if (A[i] == '(')
		{
			Left++;
			if (A[i + 1] == ')')
				return bracket_;
		}
		else if (A[i] == ')')
		{
			Right++;
			if (A[i + 1] == '(')
				return bracket_;
		}
		else if (A[i] == ' ')
		{
			if ((Num(A[i - 1]) || A[i - 1] == '.') && (Num(A[i + 1]) || A[i + 1] == '.'))
			{
				return num_;
			}
			else
			{
				A.erase(A.begin() + i);
				i--;
			}
		}
		if (i == A.size() - 1 && Right != Left)
		{
			return bracket_;
		}
		if (Right > Left)
		{
			return bracket_;
		}

	}
	return 0;
}
//中缀转后缀
vector<string> Suffix(const vector<string> A)
{
	stack<string> STACK;
	vector<string> suffix;
	int Now = 0;
	int Last[50] = {0,0,0,0,0,0,0,0};
	int left = 0;
	for (int i = 0; i < A.size(); i++)
	{
		if (A[i] == "*" || A[i] == "/")
		{
			Now = 2;
			if (STACK.empty() || Now > Last[left])
			{
				STACK.push(A[i]);
				Last[left] = Now;
			}
			else// * / 
			{
				while (!STACK.empty() && STACK.top() != "(")
				{
					suffix.push_back(STACK.top());
					STACK.pop();
				}
				STACK.push(A[i]);
				Last[left] = Now;
			}
		}
		else if (A[i] == "+" || A[i] == "-")
		{
			Now = 1;
			if (STACK.empty() || Now > Last[left])
			{
				STACK.push(A[i]);
				Last[left] = Now;
			}
			else//+ - 
			{
				while (!STACK.empty() && STACK.top() != "(")
				{
					suffix.push_back(STACK.top());
					STACK.pop();
				}
				STACK.push(A[i]);
				Last[left] = Now;
			}
		}
		else if (A[i] == "(")
		{
			left++;
			STACK.push(A[i]);
			Last[left] = 3;
		}
		else if (A[i] == ")")
		{
			while (STACK.top() != "(")
			{
				suffix.push_back(STACK.top());
				STACK.pop();
			}
			STACK.pop();
			left--;
		}
		else
		{
			suffix.push_back(A[i]);
		}
		if (i == A.size() - 1)
		{
			while (!STACK.empty())
			{
				suffix.push_back(STACK.top());
				STACK.pop();
			}
		}
	}
	return suffix;
}
//字符串分隔
vector<string>Calcultran(string A)
{
	vector<string> Calcul;
	string B;
	for (int i = 0; i < A.size(); i++)
	{
		B.clear();
		if (A[0] == '-')
		{
			A.replace(0, 1, "(-1)*");
		}
		if (A[i] == '(' && A[i + 1] == '-')
		{
			if (A[i + 2] == '(')
			{
				A.replace(i + 1, 1, "(-1)*");
				i--;
				continue;
			}
			else
			{
				for (int j = ++i; Num(A[j]) || A[j] == '.' || A[j] == '-'; j++)
				{
					B += A[j];
					i++;
					if (!Num(A[j + 1]) && A[j] != '.')
					{
						if (A[j + 1] == ')')
						{
							break;
						}
						else
						{
							Calcul.push_back("(");
							i--;
							break;
						}
					}

				}
				Calcul.push_back(B);
				continue;
			}
		}
		else
		{
			//判断负数之外的可能的符号
			if (A[i] == '(' || A[i] == ')' || A[i] == '*' || A[i] == '/' || A[i] == '+' || A[i] == '-')
			{
				B += A[i];
				Calcul.push_back(B);
				continue;
			}
			else if (Num(A[i]))
			{
				for (int j = i; Num(A[j]) || A[j] == '.'; j++)
				{
					B += A[j];
					i++;
				}
				i--;
				Calcul.push_back(B);
				continue;
			}
			else
			{
			}
		}
	}
	return Calcul;
}
//判断是否为数字
bool Num(char a)
{
	return (a >= '0' && a <= '9');
}
bool Num(string a)
{
	if (a != "+" && a != "-" && a != "*" && a != "/")
		return true;
	else
		return false;
}
//后缀计算
string Calcul_Suffix(vector<string> suffix)
{
	double A, B;
	stack<double> STACK;
	for (int i = 0; i < suffix.size(); i++)
	{
		if (Num(suffix[i]))
		{
			STACK.push(Num_tran(suffix[i]));
		}
		else
		{
			if (STACK.size() < 2)
			{
				return "操作符误用！";
			}
			else
			{
				B = STACK.top();
				STACK.pop();
				A = STACK.top();
				STACK.pop();
				if (suffix[i] == "+")
					STACK.push(A + B);
				else if (suffix[i] == "-")
					STACK.push(A - B);
				else if (suffix[i] == "*")
					STACK.push(A * B);
				else if (B == 0)
					return "除数为零！";
				else
					STACK.push(A / B);
			}
		}
	}
	if (STACK.size() != 1)
	{
		return "算式格式有误！";
	}
	return tran_Num(STACK.top());
}
//字符串转数字
double Num_tran(string A)
{
	double NUM = 0.0;
	bool sign_ = false;
	bool point = false;
	if (A[0] == '-')
	{
		sign_ = true;
	}
	for (int i = 0; i < A.size(); i++)
	{
		if (A[i] == '.')
		{
			point = true;
		}
		if (Num(A[i]))
		{
			if (point)
			{
				NUM += (double(int(A[i] - '0'))) / 10.0;
			}
			else
			{
				NUM *= 10;
				NUM += int(A[i] - '0');
			}
		}
	}
	if (sign_)
		NUM *= -1;
	return NUM;
}
//浮点数转字符串
string tran_Num(double A)
{
	int integer, decimal, digit;
	bool zero = false;
	bool sign_ = false;
	if (A < 0)
	{
		sign_ = true;
		A *= -1;
	}
	else if (A == 0)
		return "0.0";
	integer = int(A * 10);
	if (A * 10.0 - (double)integer >= 0.5)
	{
		integer++;
	}
	A = (double)integer / 10.0;
	decimal = integer % 10;
	string X;
	integer /= 10;
	if (integer == 0)
		zero = true;
	while (integer != 0)
	{
		digit = integer % 10;
		X.insert(X.begin(), (char)(digit + 48));
		integer /= 10;
	}
	if (zero)
		X.push_back('0');
	X.push_back('.');
	X.push_back((char)(decimal + 48));
	if (sign_)
	{
		X.insert(X.begin(), '-');
	}
	return X;
}

/*测试*/
//int main()
//{
//	string A;
//	getline(cin, A);
//	vector <string> B = Calcultran(A);
//	for (vector<string>::iterator it = B.begin(); it != B.end(); it++)
//	{
//		cout << *it << " ";
//	}
//	 
//
//	vector<string> suffix = Suffix(B);
//	for (vector<string>::iterator it = suffix.begin(); it != suffix.end(); it++)
//	{
//		cout << *it << " ";
//	}
//	 
//
//	cout << Calcul_Suffix(suffix);
//
//}

//int main()
//{
//	string a;
//	getline(cin, a);
//	cout << calculator(a);
//}
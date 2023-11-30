#pragma once
#include <iostream>
#include <string>
#include <stack>
#include <vector>
using namespace std;
enum Error {num_ = 1,bracket_,nonum_,form_};
//计算器！
string calculator(string A);
//初步判断 小数点 和 括号 是否规范
int Calcul_Judge(string& A);
//中缀转后缀
vector<string> Suffix(const vector<string> A);
//字符串分隔
vector<string> Calcultran(string A);
//后缀计算
string Calcul_Suffix(vector<string> suffix);
//字符串转数字
double Num_tran(string A);
//浮点数转字符串
string tran_Num(double A);
//判断是否为数字
bool Num(char a);
bool Num(string a);
#include<iostream>
#include<string>
#include <vector>
#include<math.h>
#include"advanced_calculator.h"
using namespace std;
bool isO(string a)//檢測是否為運算子
{
	switch (a[0])
	{
	case '+':
	case '-':
	case '*':
	case '/':
		return true;
	}
	return false;
}

double cal(string &a)
{
	double R = 0;
	vector<string> F;
	string TEMP = "";
	bool end = false;
	while (!end)
	{
		char c = a[0];
		a.erase(a.begin() + 0);
		switch (c)
		{
		case '+':
		case '-':
		case '*':
		case '/':
		case '^':
			if (TEMP != "")F.push_back(TEMP);
			TEMP = "";
			F.push_back(string(1, c));//C to S
			break;
		case '(':
			if (TEMP != "")F.push_back(TEMP);
			TEMP = "";
			if (F.size() >= 1)if (!isO(F[F.size() - 1]))F.push_back("*");

			F.push_back(to_string(cal(a)));
			break;

		case ')':
		case '\0':
			if (TEMP != "")F.push_back(TEMP);
			end = true;
		case ' ':
			break;
		default:
			TEMP += c;
		}

	}


	//讀取到結尾 開始運算
	//第一階運算(^)
	for (int i = 1; i < F.size(); i += 2)
	{
		if (F[i] == "^")
		{
			F[i - 1] = to_string(pow(stod(F[i - 1]) , stod(F[i + 1])));
			F.erase(F.begin() + i, F.begin() + i + 2);
			i -= 2;
		}

	}
	//第二階運算(*,/)
	for (int i = 1; i < F.size(); i += 2)
	{
		if (F[i] == "*")
		{
			F[i - 1] = to_string(stod(F[i - 1])*stod(F[i + 1]));
			F.erase(F.begin() + i, F.begin() + i + 2);
			i -= 2;
		}
		else if (F[i] == "/")
		{
			F[i - 1] = to_string(stod(F[i - 1]) / stod(F[i + 1]));
			F.erase(F.begin() + i, F.begin() + i + 2);
			i -= 2;
		}

	}
	//第三階運算(+,-)
	for (int i = 1; i < F.size(); i += 2)
	{
		if (F[i] == "+")
		{
			F[i - 1] = to_string(stod(F[i - 1]) + stod(F[i + 1]));
			F.erase(F.begin() + i, F.begin() + i + 2);
			i -= 2;
		}
		else if (F[i] == "-")
		{
			F[i - 1] = to_string(stod(F[i - 1]) - stod(F[i + 1]));
			F.erase(F.begin() + i, F.begin() + i + 2);
			i -= 2;
		}

	}


	return stod(F[0]);
}
#include<iostream>
#include<string>
#include <vector>
#include<math.h>
#include"advanced_calculator.h"
using namespace std;
bool isO(string a)//�˴��O�_���B��l
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


	//Ū���쵲�� �}�l�B��
	//�Ĥ@���B��(^)
	for (int i = 1; i < F.size(); i += 2)
	{
		if (F[i] == "^")
		{
			F[i - 1] = to_string(pow(stod(F[i - 1]) , stod(F[i + 1])));
			F.erase(F.begin() + i, F.begin() + i + 2);
			i -= 2;
		}

	}
	//�ĤG���B��(*,/)
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
	//�ĤT���B��(+,-)
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
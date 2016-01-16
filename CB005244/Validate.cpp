#include<string>
#include<iostream>
#include<string>
#include <conio.h>
#include"Validate.h"


using namespace std;

using namespace std;

string Validate::checkString(string a)
{
	bool flag = false;
	string v;
	cout << "Enter " << a << ": ";
	cin >> v;

	while (flag == false)
	{
	if (v.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") != std::string::npos)
	{
		cout <<"Enter a Valid  "<<a<<": ";
		cin >> v;
	}
	else{ flag = true; }
	}

	return v;
}

int Validate::checkInteger(string a)
{
	cout << endl<<"Enter " << a<<": ";

	bool flag = false;
	int result;
	string b;
	cin >> b;
	while (flag == false)
	{
	try
	{
		result = std::stoi(b);
		if (result >= 0)
		{
			flag = true;	
		}
		else
		{
			cout << "Invalid Input Enter " << a << " Again: "; 
			cin >> b;
		}

	}
	catch (...)
	{
		cout << "Invalid Input Enter " << a << " Again: ";
		cin >> b;
	}
	}

	return result;
}

string Validate::validatePassword()
{
	string b;
	string c="o";
	while (b != c)
	{
		cout << "Enter password:";
		b = passwordInput();
		cout << endl<< "Enter password Again: ";
		c = passwordInput();
		if (b != c)cout << endl << "password Dosent Match Enter again" << endl;
	}
	return c;
}

string Validate::passwordInput()
{
	char ch = _getch();
	string password;
	while (ch != 13)
	{
		password.push_back(ch);
		cout << '*';
		ch = _getch();
	}
	return password;
}

string Validate::paragraphInput()
{
	char ch = _getch();
	string password;
	while (ch != 13)
	{
		password.push_back(ch);
		cout << ch;
		ch = _getch();
	}

	return password;
}

double Validate::checkDouble(string a )
{
	cout << "Enter " << a << ": ";
	bool flag = false;
	double result;
	string b;
	cin >> b;
	while (flag == false)
	{
		try
		{
			result = std::stold(b);
			if (result >= 0)
			{
				flag = true;
			}
			else
			{
				cout << "Invalid Input Enter " << a << " Again: ";
				cin >> b;
			}
		}
		catch (...)
		{
			cout << "Invalid Input Enter " << a << " Again: ";
			cin >> b;
		}
	}

	return result;
}
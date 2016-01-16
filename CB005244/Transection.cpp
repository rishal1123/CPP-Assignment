#include<vector>
#include<string>
#include <iomanip>
#include <iostream>
#include <sstream>
#include"Transection.h"
#include"FileDriver.h"
#include"Validate.h"
#include"Customer.h"


using namespace std;


void Transection::setAccNo(string acc){accNo = acc;}
string Transection::getAccNo(){ return accNo;}

void Transection::setTtype(string type){ tType = type; }
string Transection::getTtype(){ return tType;}

void Transection::settDetails(string details){ tDetails = details;}
string Transection::gettDetails(){ return tDetails; }

void Transection::setTamount(double amount){ tAmount = amount; }
double Transection::getTamount(){ return tAmount; }

void Transection::setDate()
{
	SYSTEMTIME tdate;
	GetLocalTime(&tdate);
	tDate.day = tdate.wDay;
	tDate.month =tdate.wMonth;
	tDate.year = tdate.wYear;

}
MyDate Transection::getTdate()
{ 

	return tDate;
}

void Transection::makeTransaction(string c){}



vector<Transection> Transection::readTransectionFile(string acc)
{
	FileDriver d;
	Transection tran;
	vector<Transection> b;
	vector<string> r = d.readFile(tFile);
	int j = 0;
	for (auto i = begin(r); i != end(r); i++)
	{
		string tempArray[7];
		int c = 0;
		string token;
		while (token != r[j])
		{
			token = r[j].substr(0, r[j].find_first_of("#"));
			r[j] = r[j].substr(r[j].find_first_of("#") + 1);
			tempArray[c] = token.c_str();
			c++;
		}
		if (tempArray[0] == acc )
		{
			tran.accNo = tempArray[0];
			tran.tType = tempArray[1];
			tran.tAmount = stod(tempArray[2]);
			tran.tDate.day= std::stoi(tempArray[3]);
			tran.tDate.month = std::stoi(tempArray[4]);
			tran.tDate.year = std::stoi(tempArray[5]);
			tran.tDetails = tempArray[6];
			b.push_back(tran);
		}

		j++;
	}
	return b;
	d.~FileDriver();
}



double Transection::transectionBalance(string a)
{
	setDate();
	MyDate date = getTdate();
	vector<Transection> tran = readTransectionFile(a);
	int c = 0;
	double balance=80000;

	for (auto i = begin(tran); i != end(tran); i++)
	{
		if (tran[c].tType == "Withdraw" && tran[c].tDate.day == date.day && tran[c].tDate.month == date.month && tran[c].tDate.year == date.year)
			balance -= tran[c].tAmount;
		c++;
	}


	return balance;
}
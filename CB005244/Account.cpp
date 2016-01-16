#include<string>
#include<vector>
#include<iostream>
#include <iomanip>
#include"FileDriver.h"
#include"Customer.h"
#include"Validate.h"
#include"Account.h"
#include"Transection.h"

using namespace std;

string Account::getAccNo()
{
	return accNo;
}

string Account::getAccType()
{
	return accType;
}

long double Account::getAccBalance()
{
	return accBalance;
}
string Account::getAccCID()
{
	return accCID;
}



void Account::createNewAccount(string cid)
{
	Validate v;
	FileDriver d;
	accCID = cid;
	accNo = createAccNo();
	accType = "null";
	cout << "\n\nCreate Account" << endl;
	while (accType == "null")
	{
		cout << "\nSelect Account Type" << endl;
		cout << "1:Saving" << endl;
		cout << "2:Current" << endl;
		cout << "3:Loan" << endl;

		int acType = v.checkInteger("Account Type");
		switch (acType)
		{
		case 1:accType = "saving"; break;
		case 2:accType = "current"; break;
		case 3:accType = "loan"; break;
		default:cout << "Input Invalid" << endl;
		}
	}
	accBalance = v.checkDouble("Account Balance");
	accStatus = "approved";
	d.updateFile(accFile, accNo + "#" + accType + "#" + accStatus + "#" + to_string(accBalance) + "#" + accCID);

	cout << "\nAccount Created: " << accNo << endl;
	cout << "\nAccount No: " << accNo << endl;
	cout << "Account Type: " << accType << endl;
	system("PAUSE");
}

/*Create Account number for new Account.Reads bank officer file count the number of records and adds one
to the count checks whether account number exists*/
string Account::createAccNo()
{
	vector<Account> b = readAccountFile("null");
	int a = 1000;
	string d = "null";


	while (d == "null")
	{
		int c = 0;
		bool flag = false;

		for (auto i = begin(b); i != end(b); i++)
		{
			if (b[c].accNo == "ACC" + to_string(a))
				flag = true;
			c++;
		}

		if (flag != true)
			d = "ACC" + to_string(a);
		a++;
	}

	return d;
}

vector<Account> Account::readAccountFile(string cid)
{
	FileDriver d;
	Account a;
	vector<Account> b;
	vector<string> r = d.readFile(accFile);
	int j = 0;
	for (auto i = begin(r); i != end(r); i++)
	{
		string tempArray[5];
		int c = 0;
		string token;
		while (token != r[j])
		{
			token = r[j].substr(0, r[j].find_first_of("#"));
			r[j] = r[j].substr(r[j].find_first_of("#") + 1);
			tempArray[c] = token.c_str();
			c++;
		}

		a.accNo = tempArray[0];
		a.accType = tempArray[1];
		a.accStatus = tempArray[2];
		a.accBalance = stold(tempArray[3]);
		a.accCID = tempArray[4];
		
		if (cid!="null" && a.accCID==cid)b.push_back(a);
		if(cid=="null") b.push_back(a);
		j++;
	}
	return b;
	d.~FileDriver();
}

void Account::displayAccounts(string cid)
{
	vector<Account> acc = readAccountFile(cid);
	string a;
	int c = 0;
	cout <<endl<<endl<< "Acc No" << setw(15) << "Acc Type" << setw(15) << "Acc Status" << setw(15) << "Acc Balance" << setw(15) << "Acc OwnerID" << endl;

	for (auto i = begin(acc); i != end(acc); i++)
	{
		cout << acc[c].accNo << setw(15) << acc[c].accType << setw(15) << acc[c].accStatus << setw(15) << acc[c].accBalance << setw(15) << acc[c].accCID << endl;
		c++;
	}
}

void Account::updateAccount()
{
	vector<Account> b = readAccountFile("null");
	displayAccounts("null"); //displays all accounts when null
	int c = 0;
	string a;
	bool flag = false;
	Validate v;

	cout << "Enter Account Number: ";
	cin >> a;

	for (auto i = begin(b); i != end(b); i++)
	{
		if (b[c].accNo == a)
		{
			cout << "\nChoose:\n" << endl;
			cout << "1: Change Status" << endl;
			cout << "2: Delete Account" << endl;

			int f = v.checkInteger("Action");
			switch (f)
			{
			case 1:
				cout << "Current Status: " << b[c].accStatus<< endl;
				if (b[c].accStatus == "approved")b[c].accStatus = "suspended";
				else b[c].accStatus = "approved";
				overwriteAccountFile(b);
				cout << "New Status: " << b[c].accStatus<< endl;
				break;
			default:cout << "Invalid Input" << endl;;
			}
			flag = true;
		}
		c++;
	}
	if (flag == false)cout << "Account not Found" << endl;
	system("PAUSE");
}
/*overwrites whole file when a change is made to the account ,update status,update balance*/
void Account::overwriteAccountFile(vector<Account> b)
{
	FileDriver d;
	d.overwriteFile(accFile);
	int c = 0;
	for (auto i = begin(b); i != end(b); i++)
	{
			string s = (b[c].accNo+"#"+b[c].accType+"#"+ b[c].accStatus+"#"+to_string(b[c].accBalance)+"#"+b[c].accCID);
			d.updateFile(accFile, s);
		c++;
	}
}

bool Account::performTransection(string accno,double amount,string cid,string action)
{
	vector<Account> acc = readAccountFile("null");

	bool flag = false;
	int c = 0;
	for (auto i = begin(acc); i != end(acc); i++)
	{
		if (acc[c].accStatus == "approved" && action == "Deposit" && acc[c].accNo== accno)
		{
			acc[c].accBalance += amount;
			flag = true;
			overwriteAccountFile(acc);
		}
		if (acc[c].accStatus == "approved" && action == "Withdraw" && acc[c].accCID == cid && acc[c].accBalance >= amount && acc[c].accNo == accno)
		{
			acc[c].accBalance -= amount;
			flag = true;
			overwriteAccountFile(acc);
		}
		c++;
	}
	
	return flag;
}



void Account::displayMonthlyTransection(string cid)
{
	Customer cus;
	if (cid == "null")
		cid = cus.checkCID();

	vector<Account> acc = readAccountFile(cid);
	Validate v;
	Transection tran;
	vector<Transection> tranvector;
	int c = 0;

	cout << "Customers Accounts" << endl;
	for (auto i = begin(acc); i != end(acc); i++)
	{
		cout << c+1<<": " << acc[c].accNo << endl;
		c++;
	}

	int accno = v.checkInteger("Select Account");
	accno--;

	if (accno < c && accno>=0)
	{
	tranvector=tran.readTransectionFile(acc[accno].accNo);
	int month = v.checkInteger("Month");
	int year = v.checkInteger("Year");

	c = 0;
	cout << endl << "Account No" << setw(10) << "Tran Type" << setw(10) << "Tran Amount" <<setw(10) << "Tran Date" << setw(10) << "Tran Detail" << endl;
	for (auto i = begin(tranvector); i != end(tranvector); i++)
		{
		if (tranvector[c].getTdate().month == month&&tranvector[c].getTdate().year == year)
		cout << tranvector[c].getAccNo() << setw(10) << tranvector[c].getTtype() << setw(10) << tranvector[c].getTamount() << setw(10) << tranvector[c].getTdate().day << "/" << tranvector[c].getTdate().month << "/" << tranvector[c].getTdate().year<< setw(15) << tranvector[c].gettDetails() << endl;
		c++;
		}
	}
	else
	cout << "Selection Error" << endl;
}
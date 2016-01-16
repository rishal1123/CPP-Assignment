#include<vector>
#include<iostream>
#include<sstream>
#include <iomanip>
#include"Customer.h"
#include"Validate.h"
#include "FileDriver.h"
#include"Transection.h"
#include"Account.h"



using namespace std;


Customer::Customer(){}

void Customer::addNewCustomer()
{
	Validate v;
	FileDriver d;
	Account acc;
	Account check;
	cID = createCID();
	cFirstName = v.checkString("First Name");
	cLastName = v.checkString("Last Name");
	cout << "Please Enter Address: "; cAddress = v.paragraphInput();
	cUsername = checkUsername();
	cPassword = v.validatePassword();
	acc.createNewAccount(cID);
	d.updateFile(fileName, cID + "#" + cFirstName + "#" + cLastName + "#" + cUsername + "#" + cPassword + "#" + cAddress);
}

string Customer::createCID()
{
	vector<Customer> b = readCustomerFile();
		int a = 1000;
		string d = "null";


		while (d == "null")
		{
			int c = 0;
			bool flag = false;

			for (auto i = begin(b); i != end(b); i++)
			{
				if (b[c].cID == "CID" + to_string(a))
					flag = true;
				c++;
			}

			if (flag != true)
				d = "CID" + to_string(a);
			a++;
		}

		return d;
}

vector<Customer> Customer::readCustomerFile()
{
	FileDriver d;
	Customer a;
	vector<Customer> b;
	//Account account;
	vector<string> r = d.readFile(fileName);
	int j = 0;
	d.checkFileExistance(fileName,"#####");
	for (auto i = begin(r); i != end(r); i++)
	{
		string tempArray[6];
		int c = 0;
		string token;	
		while (token != r[j])
		{
			token = r[j].substr(0, r[j].find_first_of("#"));
			r[j] = r[j].substr(r[j].find_first_of("#") + 1);
			tempArray[c] = token.c_str();
			c++;
		}
	
		a.cID = tempArray[0];
		a.cFirstName = tempArray[1];
		a.cLastName = tempArray[2];
		a.cUsername = tempArray[3];
		a.cPassword = tempArray[4];
		a.cAddress = tempArray[5];
		b.push_back(a);
		j++;
	}
	return b;
	d.~FileDriver();
}

string Customer::login(string username,string password)
{
	vector<Customer> b = readCustomerFile();
	string boid = "null";

	int a = 0;

	for (auto i = begin(b); i != end(b); i++)
	{

		if (b[a].cUsername == username && b[a].cPassword == password){
			boid = b[a].cID;
		}
		a++;
	}
	return boid;
}

string Customer::checkUsername()
{
	bool flag = false;
	vector<Customer> b = readCustomerFile();
	string user;
	cout << "\nEnter Username:";
	cin >> user;
	while (flag == false)
	{
		int c = 0;
		for (auto i = begin(b); i != end(b); i++)
		{
			if (b[c].cUsername == user)
			{
				cout << "Please enter a defferent Username: ";
				cin >> user;
			}else{flag = true; }
			c++;
		}
	}
	return user;
}

void Customer::displayCustomers(string cid)
{
	vector<Customer> cus = readCustomerFile();
	string a;
	int c = 0;
	system("CLS");
	cout << "CID" << setw(15) << "FirstName" << setw(15) << "LastName" << setw(15) << "Username" <<setw(15)<< "Address" << endl;

	for (auto i = begin(cus); i != end(cus); i++)
	{
		if (cid != "null" && cus[c].cID==cid)
		cout << cus[c].cID << setw(15) << cus[c].cFirstName << setw(15) << cus[c].cLastName << setw(15) << cus[c].cUsername << setw(15) << cus[c].cAddress << endl;
		if (cid == "null")
		cout << cus[c].cID << setw(15) << cus[c].cFirstName << setw(15) << cus[c].cLastName << setw(15) << cus[c].cUsername << setw(15) << cus[c].cAddress << endl;
		c++;
	}
}

string Customer::checkCID()
{
	bool flag = false;
	vector<Customer> b = readCustomerFile();
	string user;
		while (flag == false)
		{
			cout << "\nEnter CID: ";
			cin >> user;
			int c = 0;
		for (auto i = begin(b); i != end(b); i++)
		{
			if (b[c].cID == user)flag = true;
			c++;
		}
		if (flag == false) cout << "Customer not found!" << endl; 
		}
		return user;
}

void Customer::dislaySpecificCustomerDetails()
{
	Account a;
	string cid = checkCID();
	vector<Account> acc = a.readAccountFile(cid);
	Validate v;
	Transection tran;
	vector<Transection> tranvector;
	int c = 0;
	displayCustomers(cid);

	cout <<endl<< "Customers Accounts" << endl;
	for (auto i = begin(acc); i != end(acc); i++)
	{
		cout << c + 1 << ": " << acc[c].getAccNo() << endl;
		c++;
	}

	int accno = v.checkInteger("Select Account");
	accno--;

	if (accno < c && accno >= 0)
	{
		tranvector = tran.readTransectionFile(acc[accno].getAccNo());
		c = 0;
		cout << endl << "Account No" << setw(13) << "Tran Type" << setw(13) << "Tran Amount" << setw(13) << "Tran Date" << setw(16) << "Tran Detail" << endl;
		for (auto i = begin(tranvector); i != end(tranvector); i++)
		{
			cout << tranvector[c].getAccNo() << setw(13) << tranvector[c].getTtype() << setw(13) << tranvector[c].getTamount() << setw(10) << tranvector[c].getTdate().day << "/" << tranvector[c].getTdate().month << "/" << tranvector[c].getTdate().year << setw(16) << tranvector[c].gettDetails() << endl;
			c++;
		}
	}
	else
		cout << "Selection Error" << endl;


	system("PAUSE");
}

void Customer::displayCustomersBalance()
{
	Account acc;
	vector<Account> accVector = acc.readAccountFile("null");
	vector<Customer> cus = readCustomerFile();


	cout << "CID" << setw(15) << "FirstName" << setw(15) << "LastName" << setw(15) << "Balance" << endl;

	int c=0;
	for (auto i = begin(cus); i != end(cus); i++)
	{
		long double balance=0;
		cout << cus[c].cID << setw(15) << cus[c].cFirstName << setw(15) << cus[c].cLastName;
		int j = 0;
		for (auto a = begin(accVector); a != end(accVector); a++)
		{
			string cusID = accVector[j].getAccCID();
			if (cusID == cus[c].cID)
				balance += accVector[j].getAccBalance();
			j++;
		}
		cout << setw(15) << balance << endl;
		c++;
	}


}
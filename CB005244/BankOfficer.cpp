#include<iostream>
#include<vector>
#include <string>
#include <sstream>
#include "BankOfficer.h"
#include"Validate.h"
#include"FileDriver.h"

using namespace std;

BankOfficer::BankOfficer(){}

void BankOfficer::addNewBankOfficer(){
	string pass;
	Validate v;
	
	boID =createBoID();
	boFirstName=v.checkString("First Name");
	bolastName=v.checkString("Last Name");
	boUsername=checkUsernameAvailability();
	boPassword=v.validatePassword();
	 FileDriver d;
	 string s = boID + " " + boFirstName + " " + bolastName + " " + boUsername + " "+boPassword;
	 d.updateFile(boFileNAme, s);
	 cout << endl << "User has been added successfully" << endl;
	 system("PAUSE");
}


vector<BankOfficer> BankOfficer::readBankOfficerFile()
{
	vector<BankOfficer> b;
	BankOfficer a;
	FileDriver d;
	const int arraySize =5;
	vector<string> r =d.readFile(boFileNAme);
	int j = 0;
	for (auto i = begin(r); i != end(r); i++)
		{
			string tempArray[arraySize];
			stringstream ssin(r[j]);
			int z = 0;
			while (ssin.good() && z < arraySize)
			{
				ssin >> tempArray[z];
				++z;
			}

			a.boID = tempArray[0];
			a.boFirstName = tempArray[1];
			a.bolastName = tempArray[2];
			a.boUsername = tempArray[3];
			a.boPassword = tempArray[4];

			b.push_back(a);

			j++;
		}
	return b;
	d.~FileDriver();

}

string BankOfficer::login(string username,string password){
	vector<BankOfficer> b;
	string boid = "null";
	b = readBankOfficerFile();
	int a = 0;

	for (auto i = begin(b); i != end(b); i++)
	{
		
		if (b[a].boUsername == username && b[a].boPassword == password){
			boid = b[a].boID;
		}
		a++;
	}


	return boid;
}

string BankOfficer::createBoID()
{
	vector<BankOfficer> b = readBankOfficerFile();
	int a = 1000;
	string d = "null";

	
	while (d == "null")
	{

		int c = 0;
		bool flag = false;

		for (auto i = begin(b); i != end(b); i++)
		{
			if (b[c].boID == "BO" + to_string(a))
				flag = true;
			c++;
		}

		if (flag != true)
			d = "BO" + to_string(a);
		a++;
	} 

	return d;
	
}
void BankOfficer::displayAllBankOfficers(){
	vector<BankOfficer> b = readBankOfficerFile();
	string a;
	int c = 0;
	system("CLS");
	cout <<"BOID"<< "\t" << "FirstName" << "\t" << "LastName"<< "\t" << "Username"<< "\t\n" << endl;

	for (auto i = begin(b); i != end(b); i++)
	{
		cout << b[c].boID << "\t"<<b[c].boFirstName<<"\t"<<b[c].bolastName<<"\t"<< b[c].boUsername<<"\t"<< endl;
		c++;
	}
}

void BankOfficer::overwriteBOfile(vector<BankOfficer> b)
{
	FileDriver d;
	d.overwriteFile(boFileNAme);
	int c = 0;
	for (auto i = begin(b); i != end(b); i++)
	{
		if (b[c].boID != "0/")
		{
			string s = b[c].boID + " " + b[c].boFirstName + " " + b[c].bolastName + " " + b[c].boUsername + " " + b[c].boPassword;
			d.updateFile(boFileNAme, s);
		}
			c++;
	}
}

void BankOfficer::deleteBankOfficer(string boid)
{
	int c = 0;
	bool flag = false;
	string dBO;
	vector<BankOfficer> b = readBankOfficerFile();
	displayAllBankOfficers();
	cout << "Enter BOID to Delete: ";
		cin >> dBO;
		if (dBO != boid)
		{
			int x = 0;
			for (auto i = begin(b); i != end(b); i++)
			{
				if (b[c].boID == dBO)
				{
					b[c].boID ="0/";
					overwriteBOfile(b);
					cout << "BankOfficer has been deleted" << endl;
					system("PAUSE");
					flag = true;
				}
				c++;
			}
		}
		else{
			cout << "user is logged in" << endl;
			system("PAUSE");
			flag = true;
		}
		if (flag == false)
		{
			cout << "User NOT FOUND" << endl;
			system("PAUSE");
		}
	
}

void BankOfficer::updateBankOfficer()
{
	vector<BankOfficer> b = readBankOfficerFile();
	displayAllBankOfficers();
	int c = 0;
	string a;
	bool flag = false;
	Validate v;

	cout << "Enter BOID: ";
	cin >> a;

	for (auto i = begin(b); i != end(b); i++)
	{
		if (b[c].boID ==a)
		{
			cout << "\nChoose:\n" << endl;
			cout << "1: Change First Name" << endl;
			cout << "2: Change Last Name" << endl;
			cout << "3: Change Username" << endl;
			cout << "4:Change Password" << endl;
			int f = v.checkInteger("Action");
			switch (f)
			{
			case 1:b[c].boFirstName = v.checkString("First Name");cout << "User Updated" << endl; break;
			case 2:b[c].bolastName = v.checkString("Last Name");cout << "User Updated" << endl; break;
			case 3:b[c].boUsername = checkUsernameAvailability(); cout << "User Updated" << endl; break;
			case 4:b[c].boPassword = v.validatePassword(); cout << "User Updated" << endl; break;
			default:cout << "Invalid Input" << endl;;
			}
			overwriteBOfile(b);
			flag = true;
		}
			c++;
	}
	if (flag == false)cout << "User not Found"<< endl;
	system("PAUSE");

}

string BankOfficer::checkUsernameAvailability()
{
	bool flag = false;
	vector<BankOfficer> b = readBankOfficerFile();
	int c = 0;
	string user;
	cout << "Enter Username: ";
	cin >> user;
	while (flag == false)
	{
	for (auto i = begin(b); i != end(b); i++)
	{
		if (b[c].boUsername == user)
		{
			cout << "Please enter a defferent Username: ";
			cin >> user;
		}
		else{ flag = true; }
		c++;
	}
	}
	return user;
}

void BankOfficer::checkFileExistance()
{
	FileDriver d;
	string s = "admin admin admin admin admin";
	d.checkFileExistance(boFileNAme,s);
}
// CB005244.cpp : Defines the entry point for the console application.

#include<iostream>
#include<string>
#include<vector>
#include <string>
#include <cstdlib>
#include"Validate.h"
#include "BankOfficer.h"
#include "Customer.h"
#include "FileDriver.h"
#include"Transection.h"
#include"Deposit.h"
#include"Withdraw.h"
#include"Transfer.h"
#include"Account.h"

using namespace std;


void bankofficerMode();
void atm();
void fileUpload();

int main()
{
	Validate v;
	int userType =0;

	while (userType != 4)
	{
		cout << "\n1: Enter ATM \n2: Enter as Bank Officer\n3: Upload File\n4: Exit\n" << endl;

		userType = v.checkInteger("User Type");

		if (userType>4)
		{
			cout << "\nInput Invalid\n" << endl;
		}
		else
		{
		switch (userType)
			{
				case 1: atm(); break;
				case 2: bankofficerMode(); break;
				case 3: fileUpload(); break;
			}
		}
		system("CLS");
	}

	return 0;
}

void bankofficerMode(){
	int action = 0;
	Validate v;
	Customer cus;
	Account acc;
	Transfer tran;
	string userInput;
	BankOfficer bankOfficer;
	bankOfficer.checkFileExistance();

	string boid = "null";


	if (boid == "null")
	{

		string username;
		string password;
		system("CLS");
		cout << "Bank Officer mode \n" << endl;
		cout << "Enter Username:   ";
		cin >> username;
		cout << "Enter Password:   ";
		password = v.passwordInput();

		boid = bankOfficer.login(username,password);

		if (boid == "null")
		{
			system("CLS");
			cout << "Username Or Password incorrect" << endl;
		}
	}


		while (boid != "null")
	{
		system("CLS");
		cout << "Bank Officer mode\n" << endl;
		cout << "1:Add new Bank Officer" << endl;
		cout << "2:Add new Customer" << endl;
		cout << "3:Create Account For existing Customer" << endl;
		cout << "4:Update Accounts" << endl;
		cout << "5:Display Specic Customer details" << endl;
		cout << "7:Update BankOfficer" << endl;
		cout << "8:Delete Bank Officer" << endl;
		cout << "9:View Bank Officers Information" << endl;
		cout << "10:View Customers Balances" << endl;
		cout << "11:Logout" << endl;
		action = v.checkInteger("Action");
		string cid;
		switch (action)
		{
		case 1: bankOfficer.addNewBankOfficer(); break;
		case 2:cus.addNewCustomer(); break;
		case 3:
			cus.displayCustomers("null");
			cid = cus.checkCID();
			acc.createNewAccount(cid);
			break;
		case 4:acc.updateAccount(); break;
		case 5:cus.dislaySpecificCustomerDetails(); system("PAUSE"); break;
		case 7:bankOfficer.updateBankOfficer(); break;
		case 8:bankOfficer.deleteBankOfficer(boid); break;
		case 9:bankOfficer.displayAllBankOfficers(); system("PAUSE"); break;
		case 10:cus.displayCustomersBalance(); system("PAUSE"); break;
		case 11:boid = "null"; break;
		default:cout << "Input Invalid";
		}
	}
	
}

void fileUpload()
{
	FileDriver  fileDriver;

	fileDriver.uploadFile();

}
void atm(){
	Validate v;
	Customer cus;
	int action = 0;
	string username;
	string password;
	string cID = "null";
	system("CLS");

	if (cID=="null")
	{
		cout << "ATM Mode\nEnter Username: ";
		cin >> username;
		cout << "Enter Password: ";
		password=v.passwordInput();
		cID=cus.login(username,password);
		if (cID == "null"){ cout << "\nInvalid Username or Password" << endl; system("PAUSE"); }
	}

	while (action != 5 && cID != "null")
	{
		Account acc;
		Deposit deposit;
		Withdraw withdraw;
		Transfer transfer;
		system("CLS");
		cout << "Welcome " << username << endl << endl;
		cout << "1:Withdraw" << endl;
		cout << "2:Deposit" << endl;
		cout << "3:Transfer" << endl;
		cout << "4:View Monthly Statements" << endl;
		cout << "5:Logout" << endl;
		action=v.checkInteger("Action");
		switch (action)
		{
		case 1:acc.displayAccounts(cID); withdraw.makeTransaction(cID); withdraw.~Withdraw(); system("PAUSE"); break;
		case 2:acc.displayAccounts(cID); deposit.makeTransaction(cID); deposit.~Deposit(); system("PAUSE"); break;
		case 3:acc.displayAccounts(cID); transfer.makeTransaction(cID);  transfer.~Transfer();  system("PAUSE"); break;
		case 4:acc.displayMonthlyTransection(cID);system("PAUSE");break;
		case 5:cID = "null"; break;
		default:cout << endl << "Incorrect Input";
		}
	}
}

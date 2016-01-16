#include<iostream>
#include<string>
#include<vector>
#include"Transection.h"
#include"Deposit.h"
#include"FileDriver.h"
#include"Account.h"
#include"Validate.h"
#include <Windows.h>




using namespace std;

void Deposit::makeTransaction(string cid)
{
	Account acc;
	FileDriver d;
	Validate v;
	bool flag = false;
	string accno;
	double amount;
	cout << "Enter Account Number: ";
	cin >> accno;
	amount=v.checkDouble("Deposit");

	flag=acc.performTransection(accno,amount,cid,"Deposit");
	if (flag == true)
	{
		setAccNo(accno);
		setTtype("deposit");
		setTamount(amount);
		settDetails("Deposited by: "+cid);
		setDate();
		MyDate t = getTdate();
		string date = to_string(t.day) + "#" + to_string(t.month) + "#" + to_string(t.year);
		d.updateFile(tFile, getAccNo() + "#" + getTtype() + "#" + to_string(getTamount()) + "#" + date + "#" + gettDetails());
		cout << "\nDeposit Successfull\n" << endl;
	}
	else cout << "\nDeposit Unsucessful check Account Number and Deposit Amount\n" << endl;
}

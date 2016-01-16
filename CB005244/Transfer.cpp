#include<string>
#include<iostream>
#include<vector>
#include"Account.h"
#include"FileDriver.h"
#include"Validate.h"
#include"Transection.h"
#include"Transfer.h"
using namespace std;
void Transfer::makeTransaction(string cid)
{
	Account acc;
	FileDriver d;
	Validate v;
	bool flag = false;
	string accno;
	double amount;

	cout << "Enter Account Number to transfer From: ";
	cin >> accno;
	cout << "Enter Account Number to transfer To: ";
	cin >> transferAcc;
	amount = v.checkDouble("amount to Transfer: ");


		flag = acc.performTransection(accno, amount, cid, "Withdraw");
		if(flag==true)
		flag = acc.performTransection(transferAcc, amount, cid, "Deposit");
		if (flag == false)
		acc.performTransection(accno, amount, cid, "Deposit");

	if (flag == true)
	{
		setDate();
		setAccNo(accno);
		setTtype("Transfer");
		setTamount(amount);
		settDetails("Transfered To:  " + transferAcc);
		MyDate t = getTdate();
		string date = (to_string(t.day) + "#" + to_string(t.month) + "#" + to_string(t.year));
		d.updateFile(tFile, getAccNo() + "#" + getTtype() + "#" + to_string(getTamount()) + "#" + date + "#" + gettDetails());
		cout << "\nTransfer Successfull\n" << endl;
	}
	else cout << "\nTransfer Unsucessful" << endl;
}
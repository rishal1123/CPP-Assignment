#include<iostream>
#include<string>
#include<vector>
#include"Transection.h"
#include"Withdraw.h"
#include"FileDriver.h"
#include"Account.h"
#include"Validate.h"


using namespace std;

void Withdraw::makeTransaction(string cid)
{
	Account acc;
	FileDriver d;
	Validate v;
	bool flag = false;
	string accno;
	double amount;

	cout << "Enter Account Number: ";
	cin >> accno;
	amount = v.checkDouble("Withdrawal");

	double balance = transectionBalance(accno);
	if (amount <= balance)
	{
		flag = acc.performTransection(accno, amount, cid, "Withdraw");
	}
	else
	{
		cout << endl << "Amount Greater than dailylimit   ... Daily Available Balance is: " << balance << endl;
	}
	if (flag == true)
	{
		setDate();
		setAccNo(accno);
		setTtype("Withdraw");
		setTamount(amount);
		settDetails("");
		MyDate t = getTdate();
		string date =( to_string(t.day) + "#" + to_string(t.month) + "#" + to_string(t.year));

		d.updateFile(tFile, getAccNo() + "#" + getTtype() + "#" + to_string(getTamount()) + "#" + date + "#" + gettDetails());
		cout << "\nWithdraw Successfull\n" << endl;
	}
	else cout << "\nWithdraw Unsucessful" << endl;
}

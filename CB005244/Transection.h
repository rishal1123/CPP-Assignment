#include<Windows.h>

struct MyDate
{
	int month;
	int day;
	int year;
};


class Transection{
private:
	std::string accNo;
	double tAmount;
	MyDate tDate;
	std::string tType;
	std::string tDetails;

public:

	void setAccNo(std::string);
	std::string getAccNo();

	void setTamount(double);
	double getTamount();

	 void setTtype(std::string);
	std::string getTtype();

	void setDate();
	MyDate getTdate();

	void settDetails(std::string);
	std::string gettDetails();


	virtual void makeTransaction(std::string);
	double transectionBalance(std::string);
	const std::string tFile = "Transection.txt";
	std::vector<Transection> readTransectionFile(std::string);
	void displayMonthlyTransection(std::string);
};

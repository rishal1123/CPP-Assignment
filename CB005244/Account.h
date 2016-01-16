
class Account{
private:
	std::string accNo;
	std::string accType;
	std::string accStatus;
	long double accBalance;
	std::string accCID;
public:
	Account(){}
	std::string accFile = "Account.txt";
	std::string getAccNo();
	std::string getAccType();
	long double getAccBalance();
	std::string getAccCID();

	void createNewAccount(std::string);
	std::string createAccNo();
	std::vector<Account> readAccountFile(std::string);
	void displayAccounts(std::string);
	void updateAccount();
	void overwriteAccountFile(std::vector<Account>);
	bool performTransection(std::string, double,std::string,std::string);
	void displayMonthlyTransection(std::string);
};
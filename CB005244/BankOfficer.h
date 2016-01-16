class BankOfficer
{
private:
	std::string boID;
	std::string boFirstName;
	std::string bolastName;
	std::string boUsername;
	std::string boPassword;

public:
	const std::string boFileNAme = "BankOfficer.txt";
	BankOfficer();
	std::string createBoID();
	std::string login(std::string, std::string);
	void addNewBankOfficer();
	void checkFileExistance();
	std::vector<BankOfficer> readBankOfficerFile();
	void displayAllBankOfficers();
	void overwriteBOfile(std::vector<BankOfficer>);
	void deleteBankOfficer(std::string);
	void updateBankOfficer();
	std::string checkUsernameAvailability();
};


class Customer{
private:
	std::string cID;
	std::string cFirstName;
	std::string cLastName;
	std::string cUsername;
	std::string cPassword;
	std::string cAddress;

public:
	const std::string fileName = "Customer.txt";
	Customer();
	std::string login(std::string,std::string);
	std::string checkUsername();
	void addNewCustomer();
	std::string createCID();
	std::vector<Customer>readCustomerFile();
	void displayCustomers(std::string);
	std::string checkCID();
	void dislaySpecificCustomerDetails();
	void displayCustomersBalance();
};
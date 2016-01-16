
class Deposit : public Transection
{
public:
	using Transection::makeTransaction;
	void makeTransaction(std::string);
	~Deposit(){}
};
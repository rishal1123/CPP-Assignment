
class Withdraw : public Transection
{
public:
	using Transection::makeTransaction;
	void makeTransaction(std::string);
	~Withdraw(){}
};

class Transfer : public Transection
{
private:
	std::string transferAcc;
public:
	using Transection::makeTransaction;
	void makeTransaction(std::string);

	~Transfer(){};
};
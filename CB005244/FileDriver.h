class FileDriver{

public:
	void updateFile(std::string, std::string);
	std::string uploadFile();
	void checkFileExistance(std::string,std::string);
	void overwriteFile(std::string);
	std::vector<std::string> readFile(std::string);
	~FileDriver();
};
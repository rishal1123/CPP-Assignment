#include<string>
#include<fstream>
#include<vector>
#include <sstream>
#include<iostream>
#include<Shlwapi.h>
#include"FileDriver.h"


using namespace std;

void FileDriver::updateFile(string filename, string upString)
{
	try
	{

		ofstream checkFile(filename, ios::app);
		checkFile << upString << endl;
		checkFile.close();

	}
	catch (...) {}
}


string FileDriver::uploadFile()
{
	string initialFilePath="D:\\Projects\\C++\\CPP-Assignment\\CB005244\\Account.txt";

	string a;
	if (initialFilePath.find_last_of(".") != std::string::npos)
		 a = initialFilePath.substr(initialFilePath.find_last_of(".") + 1);


	string b = "..//Upload//name." + a;
	string outputFilePath =b ;



	ifstream initialFile(initialFilePath.c_str(), ios::in | ios::binary);
	ofstream outputFile(outputFilePath.c_str(), ios::out | ios::binary);
	//defines the size of the buffer
	initialFile.seekg(0, ios::end);
	long fileSize = initialFile.tellg();
	//Requests the buffer of the predefined size


	//As long as both the input and output files are open...
	if (initialFile.is_open() && outputFile.is_open())
	{
		short * buffer = new short[fileSize / 2];
		//Determine the file's size
		//Then starts from the beginning
		initialFile.seekg(0, ios::beg);
		//Then read enough of the file to fill the buffer
		initialFile.read((char*)buffer, fileSize);
		//And then write out all that was read
		outputFile.write((char*)buffer, fileSize);
	}
	//If there were any problems with the copying process, let the user know
	else if (!outputFile.is_open())
	{
		cout << "I couldn't open " << outputFilePath << " for copying!\n";
		return 0;
	}
	else if (!initialFile.is_open())
	{
		cout << "I couldn't open " << initialFilePath << " for copying!\n";
		return 0;
	}



	initialFile.close();
	outputFile.close();


	return "a";
}


void FileDriver::checkFileExistance(string fileName, string writeString)
{
	try
	{
		ifstream checkFile(fileName, ios::in);
		if (!checkFile)
		{
			ofstream outBankOfficerFile(fileName, ios::out);
			outBankOfficerFile << writeString << endl;

		}
		checkFile.close();
	}
	catch (...) {}
}

void FileDriver::overwriteFile(string fileName)
{
	try
	{
		ofstream outBankOfficerFile(fileName, ios::out);
		outBankOfficerFile << "";
		outBankOfficerFile.close();
	}
	catch (...) {}
}

vector<string> FileDriver::readFile(string FileName)
{
	vector<string> sv;
	string line;
	//const int arraySize = 5;

	ifstream checkFile(FileName);
	if (checkFile.is_open())
	{
		while (getline(checkFile, line))
		{
			sv.push_back(line);
		}
	}
	checkFile.close();
	return sv;
}
FileDriver::~FileDriver() {
}
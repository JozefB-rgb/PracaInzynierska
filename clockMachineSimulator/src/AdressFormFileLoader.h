#ifndef FILE_READER_H
#define FILE_READER_H

#include <gmock/gmock.h>
#include <string.h>
#include <exception>
#include <fstream>
#include "IPStructures.h"

class EndOfFileException :public ::std::exception
{
	const std::string msg_;
public:
	explicit EndOfFileException(const std::string msg) : msg_(msg) {}
	const char* what() const noexcept override
	{
		return msg_.c_str();
	}
};

class IFileReader
{
public:
	virtual std::string readLine() = 0;
	virtual ~IFileReader() = default;
};

class FileReader :public ::IFileReader
{
	std::ifstream adressFile_;
public:
	FileReader(const std::string& filePath);
	std::string readLine();
};

class MockFileReader :public ::IFileReader
{
public:
	MOCK_METHOD(std::string, readLine, (), (override));
};

class AdressFormFileLoader
{
	IFileReader& fileReader_;
	RemoteDevices& remoteDevices_;

public:
	AdressFormFileLoader(IFileReader& fileReader, RemoteDevices& remoteDevices) : fileReader_(fileReader), remoteDevices_(remoteDevices) { ; };
	void loadData();
};


#endif //FILE_READER_H

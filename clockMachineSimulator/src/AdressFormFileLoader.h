#ifndef FILE_READER_H
#define FILE_READER_H

#include <gmock/gmock.h>
#include <string.h>
#include <exception>
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
public:
	FileReader() { ; };
	FileReader(std::string filePath) { ; };		//should Open File
	std::string readLine() {
		return ("");
	}
	~FileReader() { ; };						//shoudld close FIle
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

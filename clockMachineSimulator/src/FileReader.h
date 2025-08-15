#ifndef FILE_READER_H
#define FILE_READER_H

#include <gmock/gmock.h>
#include <string.h>

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



#endif //FILE_READER_H

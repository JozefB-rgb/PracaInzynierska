#include <gtest/gtest.h>
//#include <gmock/gmock.h>

#include "AdressFormFileLoader.h"
#include "IPStructures.h"

class AdressFormFileLoaderTest :public ::testing::Test {
};


TEST_F(AdressFormFileLoaderTest, testMockReadLine)
{
	MockFileReader fileReader;
	std::string expectedLine = "0.0.0.1,12345";

	EXPECT_CALL(fileReader, readLine)
		.WillOnce(testing::Return(expectedLine));

	EXPECT_EQ(fileReader.readLine(), expectedLine);
}

#include <filesystem>
TEST_F(AdressFormFileLoaderTest, testCreatingDevicesListWithDataFromMockFileReader)
{
	MockFileReader fileReader;
	RemoteDevices remoteDevices;
	AdressFormFileLoader dataLoader(fileReader, remoteDevices);

	EXPECT_CALL(fileReader, readLine)
		.WillOnce(testing::Return("0.1.2.255,10000,10001"))
		.WillOnce(testing::Return("255.255.255.255,2000,0,2001,15"))
		.WillOnce(testing::Throw(EndOfFileException("End of file reached")));

	dataLoader.loadData();

	EXPECT_EQ(remoteDevices.getIP(0), "0.1.2.255");
	EXPECT_EQ(remoteDevices.getPort(0, 0), "10000");
	EXPECT_EQ(remoteDevices.getPort(0, 1), "10001");
	EXPECT_EQ(remoteDevices.getIP(1), "255.255.255.255");
	EXPECT_EQ(remoteDevices.getPort(1, 0), "2000");
	EXPECT_EQ(remoteDevices.getPort(1, 1), "2001"); //port "0" skipped due to out of expected value, "15" also skipped
}

TEST_F(AdressFormFileLoaderTest, testIfRealFileReaderThrowsExceptionIfFileDoesntExist)
{
	const std::string filePath = "wrong path";
	EXPECT_THROW(FileReader{ filePath }, std::runtime_error);
}

TEST_F(AdressFormFileLoaderTest, testLoadRealDataFromFile)
{
	std::string filePath = "../../../../clockMachineSimulator/testFiles/remoteDevices.csv";
	FileReader fileReader(filePath);
	RemoteDevices remoteDevices;
	AdressFormFileLoader dataLoader(fileReader, remoteDevices);

	dataLoader.loadData();

	EXPECT_EQ(remoteDevices.getIP(0), "001.001.002.3");
	EXPECT_EQ(remoteDevices.getPort(0, 0), "12345");
	EXPECT_EQ(remoteDevices.getPort(0, 1), "3333");
	EXPECT_EQ(remoteDevices.getIP(1), "0.0.0.5");
	EXPECT_EQ(remoteDevices.getPort(1, 0), "5000");
	EXPECT_EQ(remoteDevices.getIP(2), "1.2.3.4");
	EXPECT_EQ(remoteDevices.getPort(2), "4000");
}

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

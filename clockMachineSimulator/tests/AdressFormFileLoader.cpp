#include <gtest/gtest.h>
//#include <gmock/gmock.h>

#include "AdressFormFileLoader.h"
#include "IPStructures.h"

class FileReaderTest :public ::testing::Test {
};

TEST_F(FileReaderTest, testFileReaderCreation)
{
	EXPECT_NO_THROW(FileReader());
}

TEST_F(FileReaderTest, testMockReadLine)
{
	MockFileReader fileReader;
	std::string expectedLine = "0.0.0.1,12345";

	EXPECT_CALL(fileReader, readLine)
		.WillOnce(testing::Return(expectedLine));

	EXPECT_EQ(fileReader.readLine(), expectedLine);
}

TEST_F(FileReaderTest, testCreatingDevicesListWithDataFromMockFileReader)
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

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

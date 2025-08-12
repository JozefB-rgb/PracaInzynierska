#include <gtest/gtest.h>

#include "IPStructures.h"

class IPStructureTest :public ::testing::Test {
};

TEST_F(IPStructureTest, testIPclassCreation)
{
	std::string stringIP = "12.34.5.5";
	IP ip(stringIP);

	EXPECT_EQ(stringIP, ip.getIP());
}

TEST_F(IPStructureTest, testIPclassExceptionThrow)
{
	EXPECT_THROW(IP("12354"), std::invalid_argument);
	EXPECT_THROW(IP("12.354"), std::invalid_argument);
	EXPECT_THROW(IP("12.35.4"), std::invalid_argument);
	EXPECT_THROW(IP("4.2..4"), std::invalid_argument);
	EXPECT_THROW(IP("-12.35.4.4"), std::invalid_argument);
	EXPECT_THROW(IP("-12.35.4.4"), std::invalid_argument);
	EXPECT_THROW(IP("256.35.4.4"), std::invalid_argument);
	EXPECT_THROW(IP("255.35.4.4a"), std::invalid_argument);
	EXPECT_THROW(IP("255.35.4.4.4"), std::invalid_argument);

	EXPECT_NO_THROW(IP("12.35.4.4"));
	EXPECT_NO_THROW(IP("255.35.4.4"));
	EXPECT_NO_THROW(IP("0.0.04.40"));
}
/*
//test whole process of loading IP, ports and local port adress form file 
TEST_F(IPStructureTest, testLoadingIPFromFileProcess) {
	OwnPort ownPort("321");
	AdressStructure firstDevice = {
		.IP = "195.128.0.1",
		.port = "8008"
	};
	AdressStructure secondDevice = {
		.IP = "295.128.0.1",
		.port = "12024"
	};
	AdressStructure thirdDevice = {
		.IP = "5.1523.42.1",
		.port = "12024"
	};

	//loading IP and ports of remote devices from file to adress structure
	std::string IPFilePath = "";
	IPFileReader fileReader;
	RemoteDeviceList remoteDevices;
	OwnPort ownPortFromFile;
	fileReader.loadAdresses(IPFilePath, remoteDevices, ownPortFromFile);

	//checks if local port adress match
	EXPECT_EQ(ownPort.get(), ownPortFromFile.get());

	//checks if firstDevice form test and form file match
	EXPECT_EQ(firstDevice, remoteDevices.getDevice(0));

	//checks if secondDevice IP from test match second IP from file
	EXPECT_EQ(secondDevice.IP, remoteDevices.getIP(1));

	//checks if thirdDevice port from test match third port from file
	EXPECT_EQ(thirdDevice.port, remoteDevices.getPort(2));
}
*/

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
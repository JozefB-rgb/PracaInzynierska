#include <gtest/gtest.h>

#include "IPStructures.h"

class IPStructureTest :public ::testing::Test {
};


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

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
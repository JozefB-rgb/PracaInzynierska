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
	EXPECT_THROW(IP("256.35.4.4"), std::invalid_argument);
	EXPECT_THROW(IP("255.35.4.4a"), std::invalid_argument);
	EXPECT_THROW(IP("255.35.4.4.4"), std::invalid_argument);
	EXPECT_THROW(IP("1000.35.4.4"), std::invalid_argument);

	EXPECT_NO_THROW(IP("12.35.4.4"));
	EXPECT_NO_THROW(IP("255.35.4.4"));
	EXPECT_NO_THROW(IP("0.0.04.40"));
}

TEST_F(IPStructureTest, testPortClassCreation)
{
	std::string stringPort = "12345";
	Port port(stringPort);

	EXPECT_EQ(port.getPort(), stringPort);
}

TEST_F(IPStructureTest, testPortClassExceptionsThrow)
{
	EXPECT_THROW(Port(""), std::invalid_argument);
	EXPECT_THROW(Port("0"), std::invalid_argument);
	EXPECT_THROW(Port("1023"), std::invalid_argument);
	EXPECT_THROW(Port("49152"), std::invalid_argument);
	EXPECT_THROW(Port("2000."), std::invalid_argument);
	EXPECT_THROW(Port("2000a"), std::invalid_argument);
	EXPECT_THROW(Port("FFF"), std::invalid_argument);
	EXPECT_THROW(Port("-2000"), std::invalid_argument);

	EXPECT_NO_THROW(Port("1024"));
	EXPECT_NO_THROW(Port("49151"));
	EXPECT_NO_THROW(Port("2000"));
}

TEST_F(IPStructureTest, testAdressStructureCreation)
{
	//test initializing with strings vector
	std::string stringIP = "255.254.0.001";
	std::vector<std::string> stringPorts = { "12345", "0", "2455", "-2454", "aa99" };
	std::string stringPort = "20000";
	AdressStructure adressStructure(stringIP, stringPorts);
	adressStructure.addPort(stringPort);

	EXPECT_EQ(adressStructure.getIP(), stringIP);
	EXPECT_EQ(adressStructure.getPort(), stringPorts.at(0));
	EXPECT_EQ(adressStructure.getPort(0), stringPorts.at(0));
	EXPECT_EQ(adressStructure.getPort(1), stringPorts.at(2));	//2455, port with value 0 should not be created due to invalid range
	EXPECT_EQ(adressStructure.getPort(2), stringPort);			//20000, -2455 and  aa99 are also skipped. 

	//test initializing with initialization list
	AdressStructure adressStructure2(stringIP, { "12345", "0", "2455", "-2454", "aa99" });
	EXPECT_EQ(adressStructure2.getIP(), stringIP);
	EXPECT_EQ(adressStructure2.getPort(0), stringPorts.at(0));
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
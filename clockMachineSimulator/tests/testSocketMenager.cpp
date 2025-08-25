#include <gtest/gtest.h>
#include <string>
#include <memory>

#include "SocketMenager.h"
#include "TimeMenager.h"

class SocketMenagerTest :public ::testing::Test
{

};

TEST_F(SocketMenagerTest, testMockSocketClientReturningData)
{
	MockSocketServer socketServer;
	MockSocketClient socketClient(socketServer);
	socketClient.connectToServer();
	std::string message1 = "2025-02-01 10:59:48.012340";
	std::string message2 = "3025-02-01 10:59:48.012340";

	EXPECT_CALL(socketClient, read)
		.WillOnce(::testing::Return(message1))
		.WillOnce(::testing::Return(message2));

	EXPECT_EQ(socketClient.read(), message1);
	EXPECT_EQ(socketClient.read(), message2);
}

TEST_F(SocketMenagerTest, testMockClientAndServerWritingToEachOther)
{
	MockSocketServer socketServer;
	MockSocketClient socketClient(socketServer);
	socketClient.connectToServer();
	std::string messageToServer = "TO_SERVER";
	std::string messageToClient = "TO_CLIENT";

	socketClient.writeNoUpdate(messageToServer);
	socketServer.write(messageToClient);

	EXPECT_EQ(socketClient.read(), messageToClient);
	EXPECT_EQ(socketServer.read(), messageToServer);
}

TEST_F(SocketMenagerTest, testMockSocketClientAskingMockSocketServerForTime)
{
	MockSocketServer socketServer;
	MockSocketClient socketClient(socketServer);
	socketClient.connectToServer();
	std::string messageToServer = "TIME?";
	std::string time = "2000-01-02 03:04:05.678901";

	EXPECT_CALL(socketServer, getTime)
		.WillOnce(::testing::Return(time));

	socketClient.writeNoUpdate(messageToServer);
	socketServer.update();
	
	EXPECT_EQ(socketClient.read(), time);
}


TEST_F(SocketMenagerTest, testSocketMenagerMultiThreeatingReadingTimeFromServers)
{
	
	MockSocketServer socketServer;
	std::string timeServer0 = "2000-01-01 00:00:10.000000";
	std::string timeServer1 = "2001-01-01 00:00:50.000000";
	std::vector<std::string> times(2);
	MockSocketServer remoteServer0;
	MockSocketServer remoteServer1;
	MockSocketClient socketClient0(remoteServer0);
	MockSocketClient socketClient1(remoteServer1);
	SocketMenager socketMenager(socketServer, times);
	socketMenager.addClient(socketClient0);
	socketMenager.addClient(socketClient1);
	socketMenager.connectClients();

	EXPECT_CALL(remoteServer0, getTime)
		.WillOnce(::testing::Return(timeServer0));
	EXPECT_CALL(remoteServer1, getTime)
		.WillOnce(::testing::Return(timeServer1));

	socketMenager.updateTimes();
	//while (!socketMenager.timeUpdatedFlag) { ; }

	EXPECT_EQ(times.at(0), timeServer0);
	EXPECT_EQ(times.at(1), timeServer1);
}


int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
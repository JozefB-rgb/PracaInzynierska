#include <gtest/gtest.h>
#include <string>
#include <memory>

#include "SocketMenager.h"
#include "TimeMenager.h"

class SocketMenagerTest :public ::testing::Test
{

};

TEST_F(SocketMenagerTest, testEstablishedConnectionBetweenSockets)
{
	MockSocket socket_1;
	MockSocket socket_2;

	EXPECT_EQ(socket_1.getStatus(), DISCONNECTED);
	EXPECT_EQ(socket_2.getStatus(), DISCONNECTED);
	EXPECT_EQ(socket_2.connectTo(&socket_1), 0);
	EXPECT_EQ(socket_1.getStatus(), CONNECTED);
	EXPECT_EQ(socket_2.getStatus(), CONNECTED);
}


TEST_F(SocketMenagerTest, testClosingConnectionBetweenSockets)
{
	MockSocket socket_1;
	MockSocket socket_2;

	EXPECT_EQ(socket_1.connectTo(&socket_2), 0);
	EXPECT_EQ(socket_1.getStatus(), CONNECTED);
	EXPECT_EQ(socket_2.getStatus(), CONNECTED);
	socket_2.disconnect();
	EXPECT_EQ(socket_1.getStatus(), DISCONNECTED);
	EXPECT_EQ(socket_2.getStatus(), DISCONNECTED);
}

TEST_F(SocketMenagerTest, testCommunicationBetweenSockets)
{
	MockSocket socket_1;
	MockSocket socket_2;
	std::string message_to_1 = "2025-02-01 10:59:48.000001";
	std::string message_to_2 = "2025-02-01 10:59:48.000002";

	EXPECT_EQ(socket_1.connectTo(&socket_2), 0);
	socket_1.write(message_to_2);
	socket_2.write(message_to_1);
	EXPECT_EQ(socket_1.read(), message_to_1);
	EXPECT_EQ(socket_2.read(), message_to_2);
}
/*
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
	
	MockSocketServer remoteServer0;
	MockSocketServer remoteServer1;
	MockSocketClient socketClient0(remoteServer0);
	MockSocketClient socketClient1(remoteServer1);
	std::string timeServer0 = "2000-01-01 00:00:10.000000";
	std::string timeServer1 = "2001-01-01 00:00:50.000000";
	std::vector<std::string> times(2);

	MockSocketServer socketServer;
	SocketMenager socketMenager(socketServer, times);
	socketMenager.addClient(socketClient0);
	socketMenager.addClient(socketClient1);
	socketMenager.connectClients();

	EXPECT_CALL(remoteServer0, getTime)
		.WillOnce(::testing::Return(timeServer0));
	EXPECT_CALL(remoteServer1, getTime)
		.WillOnce(::testing::Return(timeServer1));

	socketMenager.updateTimes();
	
	EXPECT_EQ(socketMenager.timeUpdatedFlag, true);
	EXPECT_EQ(times.at(0), timeServer0);
	EXPECT_EQ(times.at(1), timeServer1);
}
*/


int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
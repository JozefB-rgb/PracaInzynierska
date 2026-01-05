#include <gtest/gtest.h>
#include <string>
#include <memory>
#include <thread>

#include "SocketMenager.h"
#include "TimeMenager.h"

class SocketMenagerTest :public ::testing::Test
{

};

TEST_F(SocketMenagerTest, testEstablishedConnectionBetweenSockets)
{
	FakeSocket socket_1;
	FakeSocket socket_2;
	EXPECT_EQ(socket_1.getStatus(), ISocket::SocketStatus::Disconnected);
	EXPECT_EQ(socket_2.getStatus(), ISocket::SocketStatus::Disconnected);
	EXPECT_EQ(socket_2.connectTo(&socket_1), FakeSocket::SocketStatus::Connected);
	EXPECT_EQ(socket_1.getStatus(), FakeSocket::SocketStatus::Connected);
	EXPECT_EQ(socket_2.getStatus(), FakeSocket::SocketStatus::Connected);
}


TEST_F(SocketMenagerTest, testClosingConnectionBetweenSockets)
{
	FakeSocket socket_1;
	FakeSocket socket_2;

	EXPECT_EQ(socket_1.connectTo(&socket_2), FakeSocket::SocketStatus::Connected);
	EXPECT_EQ(socket_1.getStatus(), FakeSocket::SocketStatus::Connected);
	EXPECT_EQ(socket_2.getStatus(), FakeSocket::SocketStatus::Connected);
	socket_2.disconnect();
	EXPECT_EQ(socket_1.getStatus(), FakeSocket::SocketStatus::Disconnected);
	EXPECT_EQ(socket_2.getStatus(), FakeSocket::SocketStatus::Disconnected);
}

TEST_F(SocketMenagerTest, testCommunicationBetweenSockets)
{
	FakeSocket socket_1;
	FakeSocket socket_2;
	std::string message_to_1 = "2025-02-01 10:59:48.000001";
	std::string message_to_2 = "2025-02-01 10:59:48.000002";

	EXPECT_EQ(socket_1.connectTo(&socket_2), FakeSocket::SocketStatus::Connected);
	socket_1.write(message_to_2);
	socket_2.write(message_to_1);
	EXPECT_EQ(socket_1.read(), message_to_1);
	EXPECT_EQ(socket_2.read(), message_to_2);
}

TEST_F(SocketMenagerTest, testMultiThreatingFakeSockets)
{
	FakeSocket socket_1;
	FakeSocket socket_2;
	std::string message_to_1 = "IAmSocket_2";
	std::string message_to_2 = "IAmSocket_1";

	std::thread t1([&socket_1, &socket_2, message_to_1, message_to_2] {
		std::string message_from_2;

		EXPECT_THAT(socket_1.connectTo(&socket_2), ::testing::AnyOf(
			FakeSocket::SocketStatus::Connected,
			FakeSocket::SocketStatus::AlreadyConnected)
		);
		socket_1.write(message_to_2);
		for (int i = 0; i < 10; i++)
		{
			message_from_2 = socket_1.read();
			if (message_from_2 != "") break;
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
		EXPECT_EQ(message_from_2, message_to_1);
	});

	std::thread t2([&socket_1, &socket_2, message_to_1, message_to_2] {
		std::string message_from_1;

		EXPECT_THAT(socket_2.connectTo(&socket_1), ::testing::AnyOf(
				FakeSocket::SocketStatus::Connected,
				FakeSocket::SocketStatus::AlreadyConnected)
		);
		socket_2.write(message_to_1);
		for (int i = 0; i < 10; i++)
		{
			message_from_1 = socket_2.read();
			if (message_from_1 != "") break;
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
		EXPECT_EQ(message_from_1, message_to_2);
	});

	t1.join();
	t2.join();
}

/*
TEST_F(SocketMenagerTest, testMockClientAndServerWritingToEachOther)
{
	FakeSocketServer socketServer;
	FakeSocketClient socketClient(socketServer);
	socketClient.connectToServer();
	std::string messageToServer = "TO_SERVER";
	std::string messageToClient = "TO_CLIENT";

	socketClient.writeNoUpdate(messageToServer);
	socketServer.write(messageToClient);

	EXPECT_EQ(socketClient.read(), messageToClient);
	EXPECT_EQ(socketServer.read(), messageToServer);
}

TEST_F(SocketMenagerTest, testFakeSocketClientAskingFakeSocketServerForTime)
{
	FakeSocketServer socketServer;
	FakeSocketClient socketClient(socketServer);
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
	
	FakeSocketServer remoteServer0;
	FakeSocketServer remoteServer1;
	FakeSocketClient socketClient0(remoteServer0);
	FakeSocketClient socketClient1(remoteServer1);
	std::string timeServer0 = "2000-01-01 00:00:10.000000";
	std::string timeServer1 = "2001-01-01 00:00:50.000000";
	std::vector<std::string> times(2);

	FakeSocketServer socketServer;
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
#include <gtest/gtest.h>
#include <string>
#include <memory>

#include "SocketMenager.h"

class SocketMenagerTest :public ::testing::Test
{

};

TEST_F(SocketMenagerTest, testMockSocketClientReturningData)
{
	MockSocketServer socketServer;
	auto socketClient = std::make_shared <MockSocketClient> (socketServer);
	socketClient->connectTo();
	std::string message1 = "2025-02-01 10:59:48.012340";
	std::string message2 = "3025-02-01 10:59:48.012340";

	EXPECT_CALL(*socketClient, read)
		.WillOnce(::testing::Return(message1))
		.WillOnce(::testing::Return(message2));

	EXPECT_EQ(socketClient->read(), message1);
	EXPECT_EQ(socketClient->read(), message2);
}

TEST_F(SocketMenagerTest, testMockSocketClientAskingMockSocketServerForTime)
{
	MockSocketServer socketServer;
	auto socketClient = std::make_shared <MockSocketClient>(socketServer);
	socketClient->connectTo();
	std::string messageToServer = "TIME?";
	std::string messageToClient = "2000-01-02 03:04:05.678901";

	EXPECT_CALL(socketServer, getTime)
		.WillOnce(::testing::Return(messageToClient));

	socketClient->write(messageToServer);
	socketServer.update();
	
	EXPECT_EQ(socketClient->read(), messageToClient);
}

TEST_F(SocketMenagerTest, test)
{
	
}

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
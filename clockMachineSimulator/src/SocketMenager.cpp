#include "SocketMenager.h"

//MockSocketServer
void MockSocketServer::connectTo(MockSocketClient* mockClient)
{
	mockClient_ = mockClient;
}
void MockSocketServer::write(std::string message)
{
	EXPECT_CALL(*mockClient_, read)
		.WillOnce(::testing::Return(message));
}
void MockSocketServer::update()
{
	if (read() == "TIME?")
	{
		EXPECT_CALL(*mockClient_, read)
			.WillOnce(::testing::Return(getTime()));
	}
}

//MockSocketClient
void MockSocketClient::connectTo()
{
	mockServer_.connectTo(this);
}
void MockSocketClient::write(std::string message)
{
	EXPECT_CALL(mockServer_, read)
		.WillOnce(::testing::Return(message));
}
#include "SocketMenager.h"

//MockSocketServer
void MockSocketServer::connectTo(const std::shared_ptr<MockSocketClient>&mockClient)
{
	mockClient_ = mockClient;
}
void MockSocketServer::write(std::string message)
{
	;
}
void MockSocketServer::update()
{
	if (read() == "TIME?")
	{
		EXPECT_CALL(*mockClient_, read)
			.WillOnce(::testing::Return(getTime()));
	}
}
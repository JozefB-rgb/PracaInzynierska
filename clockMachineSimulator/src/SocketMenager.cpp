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
void MockSocketClient::connectToServer()
{
	mockServer_.connectTo(this);
}
void MockSocketClient::write(std::string message)
{
	EXPECT_CALL(mockServer_, read)
		.WillOnce(::testing::Return(message));
	mockServer_.update();
}
void MockSocketClient::writeNoUpdate(std::string message)
{
	EXPECT_CALL(mockServer_, read)
		.WillOnce(::testing::Return(message));
}

//SocketMenager
void SocketMenager::updateTime_(ISocketClient& socketClient, std::string& time, int timeOut_ms, int& failFlag)
{
	failFlag = 1;
	std::chrono::microseconds duration;

	socketClient.write("TIME?");
	auto start = std::chrono::steady_clock::now();
	while (duration.count() * 1000 < timeOut_ms)
	{
		auto currentTime = std::chrono::steady_clock::now();
		duration = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - start);
		time = socketClient.read();
		if (time != "")
		{
			failFlag = 0;
			break;
		}
	}
	if (failFlag)
		std::cout << "Time out occured\n";
	else
		std::cout << time << "\n";
}
void SocketMenager::addClient(ISocketClient& socketClient)
{
	socketClients_.emplace_back(socketClient);
	transmitionFailedFlag_.emplace_back(0);
}
void SocketMenager::connectClients()
{
	for (ISocketClient& socket : socketClients_)
	{
		socket.connectToServer();
	}
}
void SocketMenager::updateTimes()
{
	timeUpdatedFlag = false;

	for (int i = 0; i < socketClients_.size(); i++)
	{
		threads_.emplace_back(
			&SocketMenager::updateTime_,
			this,
			std::ref(socketClients_.at(i).get()),
			std::ref(times_.at(i)),
			timeOut_ms_,
			std::ref(transmitionFailedFlag_.at(i))
		);
	}
	for (auto& t : threads_) {
		if (t.joinable()) {
			t.join();
		}
	}

}
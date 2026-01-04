#include "SocketMenager.h"

//MockSocket
int MockSocket::connectTo(MockSocket* remoteMockSocket)
{
	remoteMockSocket_ = remoteMockSocket;
	remoteMockSocket_->acceptConnection(this);
	this->write(whoAmI_);
	remoteMockSocket_->update();
	if (this->read() == IAmSocket_)
	{
		socketConnected_ = true;
		return (0);
	}
	else
	{
		socketConnected_ = false;
		remoteMockSocket_ = NULL;
		return (1);
	}
}
void MockSocket::write(std::string message)
{
	EXPECT_CALL(*remoteMockSocket_, read)
		.WillOnce(::testing::Return(message));
}

void MockSocket::update()
{
	std::string message = this->read();
	if (message == whoAmI_)
	{
		this->write(IAmSocket_);
	}
	else if (message == closeConnection_)
	{
		remoteMockSocket_ = NULL;
		socketConnected_ = false;
	}
}

void MockSocket::disconnect()
{
	this->write(closeConnection_);
	remoteMockSocket_->update();
	remoteMockSocket_ = NULL;
	socketConnected_ = false;
}

void MockSocket::acceptConnection(MockSocket *remoteSocket)
{
	socketConnected_ = true;
	remoteMockSocket_ = remoteSocket;
}

bool MockSocket::getStatus()
{
	return (socketConnected_);
}
/*
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
*/
/*
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
	bool timeUpdateFail = false;

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
	for (int i = 0; i < transmitionFailedFlag_.size(); i++)
	{
		if (transmitionFailedFlag_.at(i))
		{
			std::cout << "Updateing time form socketClient" << i << "\n";
			timeUpdateFail = true;
		}
	}
	if (!timeUpdateFail) timeUpdatedFlag = true;

}*/
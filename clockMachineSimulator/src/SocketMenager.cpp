#include "SocketMenager.h"

//FakeSocket
ISocket::SocketStatus FakeSocket::connectTo(FakeSocket* remoteFakeSocket)
{
	if (!remoteFakeSocket) {
		this->socketStatus_ = SocketStatus::Disconnected;
		return (socketStatus_);
	}
	if (this < remoteFakeSocket)
	{
		std::lock_guard<std::mutex> guard(this->socketMutex_);
		if (remoteFakeSocket_) return (SocketStatus::AlreadyConnected);
		remoteFakeSocket_ = remoteFakeSocket;
		std::lock_guard<std::mutex> guard2(remoteFakeSocket_->socketMutex_);
		remoteFakeSocket_->acceptConnection(this);
	}
	else
	{
		if (remoteFakeSocket_) return (SocketStatus::AlreadyConnected);
		remoteFakeSocket_ = remoteFakeSocket;
		std::lock_guard<std::mutex> guard(remoteFakeSocket_->socketMutex_);
		std::lock_guard<std::mutex> guard2(this->socketMutex_);
		remoteFakeSocket_->acceptConnection(this);
	}
	this->write(whoAmI_);
	remoteFakeSocket_->update();
	if (this->read() == IAmSocket_)
	{
		socketStatus_ = SocketStatus::Connected;
		return (socketStatus_);
	}
	else
	{
		remoteFakeSocket_ = NULL;
		socketStatus_ = SocketStatus::Disconnected;
		return (socketStatus_);
	}
}
void FakeSocket::write(std::string message)
{
	if (this < remoteFakeSocket_)
	{
		std::lock_guard<std::mutex> guard(this->socketMutex_);
		std::lock_guard<std::mutex> guard2(remoteFakeSocket_->socketMutex_);
		remoteFakeSocket_->queue_.push(std::move(message));
	}
	else
	{
		std::lock_guard<std::mutex> guard(remoteFakeSocket_->socketMutex_);
		std::lock_guard<std::mutex> guard2(this->socketMutex_);
		remoteFakeSocket_->queue_.push(std::move(message));
	}
}

void FakeSocket::update()
{
	std::string message = this->read();
	if (message == whoAmI_)
	{
		this->write(IAmSocket_);
	}
	else if (message == closeConnection_)
	{
		remoteFakeSocket_ = NULL;
		socketStatus_ = SocketStatus::Disconnected;
	}
}

void FakeSocket::disconnect()
{
	this->write(closeConnection_);
	remoteFakeSocket_->update();
	remoteFakeSocket_ = NULL;
	socketStatus_ = SocketStatus::Disconnected;
}

void FakeSocket::acceptConnection(FakeSocket *remoteSocket)
{
	socketStatus_ = SocketStatus::Connected;
	remoteFakeSocket_ = remoteSocket;
}

ISocket::SocketStatus FakeSocket::getStatus()
{
	return (socketStatus_);
}

std::string FakeSocket::read()
{
	std::lock_guard<std::mutex> guard(socketMutex_);
	if (queue_.empty()) return ("");
	auto result = std::move(queue_.front());
	queue_.pop();
	return (result);
}
/*
//FakeSocketClient
void FakeSocketClient::connectToServer()
{
	mockServer_.connectTo(this);
}
void FakeSocketClient::write(std::string message)
{
	EXPECT_CALL(mockServer_, read)
		.WillOnce(::testing::Return(message));
	mockServer_.update();
}
void FakeSocketClient::writeNoUpdate(std::string message)
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
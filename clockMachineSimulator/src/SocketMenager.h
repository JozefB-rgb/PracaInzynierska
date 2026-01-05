#ifndef SOCKET_MENAGER_H
#define SOCKET_MENAGER_H

#include <string>
#include <memory>
#include <functional>
#include <thread>
#include <chrono>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <queue>

class ISocket
{
public:
	enum class SocketStatus
	{
		Connected,
		Disconnected,
		AlreadyConnected
	};
public:
	virtual std::string read() = 0;
	virtual void write(std::string) = 0;
	virtual SocketStatus getStatus() = 0;
	virtual ~ISocket() = default;
};

class FakeSocket :public ISocket
{
private:
	FakeSocket* remoteFakeSocket_ = NULL;
	std::string whoAmI_ = "whoAmI";
	std::string IAmSocket_ = "IAmSocket";
	std::string closeConnection_ = "closeConnection_";
	std::mutex	socketMutex_;
	std::queue<std::string> queue_;
	SocketStatus socketStatus_ = SocketStatus::Disconnected;
	void update();
	void acceptConnection(FakeSocket* remoteSocket);

public:
	void write(std::string message);
	void disconnect();
	SocketStatus getStatus();
	SocketStatus connectTo(FakeSocket* fakeSocket);
	std::string read();
};

/*
class SocketMenager
{
	ISocketServer& socketServer_;
	std::vector<std::reference_wrapper<ISocketClient>> socketClients_;
	std::vector<std::string>& times_;
	std::vector<std::thread> threads_;
	std::vector<int> transmitionFailedFlag_;
	int timeOut_ms_ = 10;

	void updateTime_(ISocketClient& socketClient, std::string& time, int timeOut_ms, int& failFlag);
public:
	bool timeUpdatedFlag = false;
	SocketMenager(ISocketServer& socketServer, std::vector<std::string>& times) : socketServer_(socketServer), times_(times) { ; }
	void addClient(ISocketClient& socketClient);
	void connectClients();
	void updateTimes();
};
*/

#endif // SOCKET_MENAGER_H

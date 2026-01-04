#ifndef SOCKET_MENAGER_H
#define SOCKET_MENAGER_H

#define CONNECTED true
#define DISCONNECTED false

#include <string>
#include <memory>
#include <functional>
#include <thread>
#include <chrono>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

class ISocket
{
public:
	virtual std::string read() = 0;
	virtual void write(std::string) = 0;
	virtual bool getStatus() = 0;
	virtual ~ISocket() = default;
};

class SocketBase :public ISocket
{
protected:
	bool socketConnected_ = false;
};

class MockSocket :public SocketBase
{
	MockSocket* remoteMockSocket_ = NULL;
	std::string whoAmI_ = "whoAmI";
	std::string IAmSocket_ = "IAmSocket";
	std::string closeConnection_ = "closeConnection_";

public:
	void write(std::string message);
	void update();
	void acceptConnection(MockSocket *remoteSocket);
	void disconnect();
	bool getStatus();
	int connectTo(MockSocket* mockSocket);
	MOCK_METHOD(std::string, read, (), (override));
	MOCK_METHOD(std::string, getTime, (), ());
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

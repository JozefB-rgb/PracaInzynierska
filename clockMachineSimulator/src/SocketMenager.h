#ifndef SOCKET_MENAGER_H
#define SOCKET_MENAGER_H

#include <string>
#include <memory>
#include <functional>
#include <thread>
#include <chrono>
#include <gmock/gmock.h>

class ISocketServer
{
public:
	virtual std::string read() = 0;
	virtual void write(std::string) = 0;
	virtual ~ISocketServer() = default;
};

class MockSocketClient;
class MockSocketServer :public ISocketServer
{
	MockSocketClient* mockClient_;
public:
	void connectTo(MockSocketClient* mockClient);
	void write(std::string message);
	void update();
	MOCK_METHOD(std::string, read, (), (override));
	MOCK_METHOD(std::string, getTime, (), ());
};

class ISocketClient
{
public:
	virtual std::string  read() = 0;
	virtual void write(std::string) = 0;
	virtual void connectToServer() = 0;
	virtual ~ISocketClient() = default;
};

class MockSocketClient :public ISocketClient
{
	MockSocketServer& mockServer_;
public:
	MockSocketClient(MockSocketServer& mockServer) : mockServer_(mockServer) { ; }
	void connectToServer();
	void write(std::string message);
	void writeNoUpdate(std::string message);
	MOCK_METHOD(std::string, read, (), (override));
};

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

#endif // SOCKET_MENAGER_H

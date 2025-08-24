#ifndef SOCKET_MENAGER_H
#define SOCKET_MENAGER_H

#include <string>
#include <memory>
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
	virtual ~ISocketClient() = default;
};

class MockSocketClient :public ISocketClient
{
	MockSocketServer& mockServer_;
public:
	MockSocketClient(MockSocketServer& mockServer) : mockServer_(mockServer) { ; }
	void connectTo();
	void write(std::string message);
	MOCK_METHOD(std::string, read, (), (override));
};

#endif // SOCKET_MENAGER_H

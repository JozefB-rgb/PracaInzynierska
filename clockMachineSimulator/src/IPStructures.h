#ifndef IP_STRUCTURES_H

#define IP_STRUCTURES_H

#include <string>
#include <vector>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <initializer_list>

class OwnPort {
	std::string port_;

public:
	OwnPort();
	OwnPort(std::string port);
	std::string get();
};

class IP
{
	std::string ip_;

	std::string checkIP(std::string ip);
public:
	IP(const std::string& ip) : ip_(checkIP(ip)) {}
	const std::string& getIP() const { return ip_; };
};

class Port
{
	std::string port_;

	std::string checkPort(std::string port);
public:
	Port(const std::string& port) : port_(checkPort(port)) {}
	const std::string& getPort() const { return port_; };
};

class AdressStructure {
	IP ip_;
	std::vector<Port> ports_;
	
public:
	AdressStructure(std::string ip, std::initializer_list<std::string> ports);
	AdressStructure(std::string ip, std::vector<std::string> ports);
	void addPort(std::string port);
	const std::string getIP() { return ip_.getIP(); };
	const std::string getPort() { return ports_.at(0).getPort(); };
	const std::string getPort(int pos) { return ports_.at(pos).getPort(); };
	/*bool operator==(const AdressStructure& other) const {
		return IP == other.IP && port == other.port;
	}*/
};
//for printhing to console during project Testing
//inline void PrintTo(AdressStructure& device, std::ostream* os);

/*
class RemoteDeviceList {
	std::vector<AdressStructure> devices_;

public:
	AdressStructure getDevice(int pos);
	std::string getIP(int pos);
	std::string getPort(int pos);
};

class IPFileReader {
public:
	void loadAdresses(std::string path, RemoteDeviceList& remoteDevices, OwnPort& ownPort);
};
*/
#endif // !IP_STRUCTURES_H

#include "IPStructures.h"

/*
//for printhing to console during project Testing
inline void PrintTo(AdressStructure& device, std::ostream* os) {
	*os << "Device IP: " << device.IP << ", port: " << device.port;
};*/

//class OwnPort
OwnPort::OwnPort() : port_(NULL) {};
OwnPort::OwnPort(std::string port) : port_(port) {}
std::string OwnPort::get() { return port_; };

//class IP
std::string IP::checkIP(std::string ip)
{
	size_t dotPossition;
	size_t prevoiusDotPossition;
	std::string ipBlock;
	int i_ipBlock;

	dotPossition = 0;
	prevoiusDotPossition = -1;
	for (int block = 1; block <= 4; block++)
	{
		dotPossition = ip.find(".", dotPossition + 1);
		if ((dotPossition == std::string::npos && (block != 4)))
			throw std::invalid_argument("IP is not ***.***.***.*** format");
		else if (block == 4)
			ipBlock = ip.substr(prevoiusDotPossition + 1);
		else
			ipBlock = ip.substr(prevoiusDotPossition + 1, dotPossition - prevoiusDotPossition - 1);
		{
			size_t len;
			i_ipBlock = std::stoi(ipBlock, &len);
			if (len != ipBlock.size())
				throw std::invalid_argument("Not only digits inside IP");
		}
		if (!(0 <= i_ipBlock && i_ipBlock <= 255))
			throw std::invalid_argument("Invalid Ip block");
		prevoiusDotPossition = dotPossition;
	}
	return ip;
}

//class Port
std::string Port::checkPort(std::string port)
{
	int i_port;
	size_t len;

	i_port = stoi(port, &len);
	if (len != port.size())
		throw std::invalid_argument("Not only digits inside Port");
	if (i_port < 1024 || 49151 < i_port)
		throw std::invalid_argument("Port out of expected range <1024...49151>");
	return port;
}

//class AdressStructure
AdressStructure::AdressStructure(std::string ip, std::initializer_list<std::string> ports) : ip_(IP(ip))
{
	for (const std::string& port : ports)
	{
		try
		{
			ports_.emplace_back(Port(port));
		}
		catch (const std::invalid_argument& e)
		{
			std::cerr << "Port value " << port << " is invalid \n";
		}
	}
}
AdressStructure::AdressStructure(std::string ip, std::vector<std::string> ports) : ip_(IP(ip))
{
	for (const std::string& port : ports)
	{
		try
		{
			ports_.emplace_back(Port(port));
		}
		catch (const std::invalid_argument& e)
		{
			std::cerr << "Port value " << port << " is invalid \n";
		}
	}
}
void AdressStructure::addPort(std::string port)
{ 
	try
	{
		ports_.emplace_back(Port(port));
	}
	catch (std::invalid_argument& e)
	{
		std::cerr << "Port value " << port << " is invalid \n";
	}
}


//RemoteDevices
void RemoteDevices::addDevice(AdressStructure device) { devices_.emplace_back(device); }
const std::string RemoteDevices::getIP(int device) { return devices_.at(device).getIP(); }
const std::string RemoteDevices::getPort(int device) { return devices_.at(device).getPort(0); }
const std::string RemoteDevices::getPort(int device, int port) { return devices_.at(device).getPort(port); }
/*
//class RemoteDeviceList
AdressStructure RemoteDeviceList::getDevice(int pos) { return devices_.at(pos); };
std::string RemoteDeviceList::getIP(int pos) { return devices_.at(pos).IP; };
std::string RemoteDeviceList::getPort(int pos) { return devices_.at(pos).port; };

//class IPFileReader
void IPFileReader::loadAdresses(std::string path, RemoteDeviceList& remoteDevices, OwnPort& ownPort) {
	;
};*/
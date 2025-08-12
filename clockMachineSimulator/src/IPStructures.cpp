#include "IPStructures.h"

//for printhing to console during project Testing
inline void PrintTo(AdressStructure& device, std::ostream* os) {
	*os << "Device IP: " << device.IP << ", port: " << device.port;
};

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
			size_t pos;
			i_ipBlock = std::stoi(ipBlock, &pos);
			if (pos != ipBlock.size())
				throw std::invalid_argument("Not only digits inside IP");
		}
		if (!(0 <= i_ipBlock && i_ipBlock <= 255))
			throw std::invalid_argument("Invalid Ip block");
		prevoiusDotPossition = dotPossition;
	}
	return ip;
}

//class RemoteDeviceList
AdressStructure RemoteDeviceList::getDevice(int pos) { return devices_.at(pos); };
std::string RemoteDeviceList::getIP(int pos) { return devices_.at(pos).IP; };
std::string RemoteDeviceList::getPort(int pos) { return devices_.at(pos).port; };

//class IPFileReader
void IPFileReader::loadAdresses(std::string path, RemoteDeviceList& remoteDevices, OwnPort& ownPort) {
	;
};
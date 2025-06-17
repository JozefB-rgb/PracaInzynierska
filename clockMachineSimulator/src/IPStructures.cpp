#include "IPStructures.h"

//for printhing to console during project Testing
inline void PrintTo(AdressStructure& device, std::ostream* os) {
	*os << "Device IP: " << device.IP << ", port: " << device.port;
};

//class OwnPort
OwnPort::OwnPort() : port_(NULL) {};
OwnPort::OwnPort(std::string port) : port_(port) {}
std::string OwnPort::get() { return port_; };

//class RemoteDeviceList
AdressStructure RemoteDeviceList::getDevice(int pos) { return devices_.at(pos); };
std::string RemoteDeviceList::getIP(int pos) { return devices_.at(pos).IP; };
std::string RemoteDeviceList::getPort(int pos) { return devices_.at(pos).port; };

//class IPFileReader
void IPFileReader::loadAdresses(std::string path, RemoteDeviceList& remoteDevices, OwnPort& ownPort) {
	;
};
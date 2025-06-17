#ifndef IP_STRUCTURES_H

#define IP_STRUCTURES_H

#include <string>
#include <vector>
#include <iomanip>
#include <iostream>
#include <sstream>

class OwnPort {
	std::string port_;

public:
	OwnPort();
	OwnPort(std::string port);
	std::string get();
};

struct AdressStructure {
	std::string IP;
	std::string port;

	bool operator==(const AdressStructure& other) const{
		return IP == other.IP && port == other.port;
	}
};
//for printhing to console during project Testing
inline void PrintTo(AdressStructure& device, std::ostream* os);

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

#endif // !IP_STRUCTURES_H

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

class IP
{
	std::string ip_;

	std::string checkIP(std::string ip)
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
public:
	IP(const std::string& ip) : ip_(checkIP(ip)) {}
	const std::string& getIP() const { return ip_; };
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

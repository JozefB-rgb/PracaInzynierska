#include "FileReader.h"

//AdressFormFileLoader
void AdressFormFileLoader::loadData()
{
	std::string line;
	size_t commaPossition;
	size_t prevoiusCommaPossition;
	std::string stringCell;
	std::string ip;
	std::vector <std::string> ports;
	
	try
	{
		while (1)
		{
			line = fileReader_.readLine();
			commaPossition = 0;
			prevoiusCommaPossition = -1;
			while (((prevoiusCommaPossition != std::string::npos) || (commaPossition != std::string::npos)))
			{
				commaPossition = line.find(",", commaPossition + 1);
				if (commaPossition == std::string::npos)
					stringCell = line.substr(prevoiusCommaPossition + 1);
				else
					stringCell = line.substr(prevoiusCommaPossition + 1, commaPossition - prevoiusCommaPossition - 1);
				if (prevoiusCommaPossition == -1)
					ip = stringCell;
				else
					ports.emplace_back(stringCell);
				prevoiusCommaPossition = commaPossition;
			}
			AdressStructure device(ip, ports);
			remoteDevices_.addDevice(device);
			ports.clear();
		}
	}
	catch (const EndOfFileException& e)
	{
		std::cout << "File ended\n";
	}
}


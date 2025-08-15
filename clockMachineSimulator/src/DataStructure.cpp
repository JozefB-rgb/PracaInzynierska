#include "DataStructure.h"

#include <iomanip>
#include <iostream>
#include <sstream>

//for printhing to console during project Testing
inline void PrintTo(TimeStructure& time, std::ostream* os) {
	TimeConverter converter;
	*os << converter.timeToString(time);
};

//class TimeConverter
//connvets time data to TimeStructure or to String
TimeConverter::TimeConverter() { ; }
std::string TimeConverter::timeToString(TimeStructure& time)
{
	std::ostringstream oss;

	oss << std::setw(4) << std::setfill('0') << time.year << "-" \
		<< std::setw(2) << std::setfill('0') << time.month << "-" \
		<< std::setw(2) << std::setfill('0') << time.day << " "
		<< std::setw(2) << std::setfill('0') << time.hour << ":"
		<< std::setw(2) << std::setfill('0') << time.min << ":"
		<< std::setw(2) << std::setfill('0') << time.sec << "."
		<< std::setw(6) << std::setfill('0') << time.uSec;

	std::string result = oss.str();
	return result;
}
TimeStructure TimeConverter::stringToTime(std::string stringTime) {
	//stringTime format: "0000-00-00 00:00:00.000000"
	TimeStructure customTime = {
		.year = stoi(stringTime.substr(0,4)),
		.month = stoi(stringTime.substr(5,2)),
		.day = stoi(stringTime.substr(8,2)),
		.hour = stoi(stringTime.substr(11,2)),
		.min = stoi(stringTime.substr(14,2)),
		.sec = stoi(stringTime.substr(17,2)),
		.uSec = stoi(stringTime.substr(20,6))
	};
	return customTime;
}
//~class TimeConverter


//class DataStructure
DataStructure::DataStructure(IClock& timeSource) : timeSource_(timeSource) {}
DataStructure::DataStructure(IClock& timeSource, std::string pathToAdressesFile) : timeSource_(timeSource), pathToAdressesFile_(pathToAdressesFile) {}

bool DataStructure::settingUp() {
	if (severRunning_) return true;
	else return false;
}
bool DataStructure::waitingForConnection() {
	if (connectedToAll_) return false;
	else return true;
}
bool DataStructure::isSynchronized() { return timeSynchronized_; };

void DataStructure::updateTime() { timeSource_.getTime(time_); };
void DataStructure::synchronizeTime() { ; };

int DataStructure::getYear() { return time_.year; };
int DataStructure::getMonth() { return time_.month; };
int DataStructure::getDay() { return time_.day; };
int DataStructure::getHour() { return time_.hour; };
int DataStructure::getMin() { return time_.min; };
int DataStructure::getSec() { return time_.sec; };
int DataStructure::getuSec() { return time_.uSec; };
std::string DataStructure::getTime() { return converter_.timeToString(time_); }
//~class DataStructure

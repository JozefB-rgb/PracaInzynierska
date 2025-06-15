#include "TimeSynchronizator.h"

#include <iomanip>
#include <iostream>
#include <sstream>

//for printhing to console during project Testing
inline void PrintTo(TimeStructure& time, std::ostream* os) {
	TimeStructureStringConverter converter;
	*os << converter.timeToString(time);
};

//class TimeStructureStringConverter
//connvets time data to TimeStructure or to String
TimeStructureStringConverter::TimeStructureStringConverter() { ; }
std::string TimeStructureStringConverter::timeToString(TimeStructure& time)
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
TimeStructure TimeStructureStringConverter::stringToTime(std::string stringTime) {
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
//~class TimeStructureStringConverter


//class TimeSynchronizator
TimeSynchronizator::TimeSynchronizator(IClock& timeSource) : timeSource_(timeSource) {}
TimeSynchronizator::TimeSynchronizator(IClock& timeSource, std::string pathToAdressesFile) : timeSource_(timeSource), pathToAdressesFile_(pathToAdressesFile) {}

bool TimeSynchronizator::settingUp() {
	if (severRunning_) return true;
	else return false;
}
bool TimeSynchronizator::waitingForConnection() {
	if (connectedToAll_) return false;
	else return true;
}
bool TimeSynchronizator::isSynchronized() { return timeSynchronized_; };

void TimeSynchronizator::updateTime() { timeSource_.getTime(time_); };
void TimeSynchronizator::synchronizeTime() { ; };

int TimeSynchronizator::getYear() { return time_.year; };
int TimeSynchronizator::getMonth() { return time_.month; };
int TimeSynchronizator::getDay() { return time_.day; };
int TimeSynchronizator::getHour() { return time_.hour; };
int TimeSynchronizator::getMin() { return time_.min; };
int TimeSynchronizator::getSec() { return time_.sec; };
int TimeSynchronizator::getuSec() { return time_.uSec; };
std::string TimeSynchronizator::getTime() { return converter_.timeToString(time_); }
//~class TimeSynchronizator

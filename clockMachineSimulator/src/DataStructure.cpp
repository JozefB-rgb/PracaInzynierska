#include "DataStructure.h"

#include <iomanip>
#include <iostream>
#include <sstream>


//class TimeConverter
std::string TimeConverter::timeToString(const TimeStructure& time)
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
std::string TimeConverter::timeToString(const std::chrono::system_clock::time_point& timePoint)
{
	TimeConverter timeConverter;
	TimeStructure time;

	time = timeConverter.toTimeStructure(timePoint);
	return (timeConverter.timeToString(time));
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
TimeStructure TimeConverter::toTimeStructure(const std::chrono::system_clock::time_point& timePoint)
{
	TimeStructure result;
	time_t t_time;
	tm time_tm;

	t_time = std::chrono::system_clock::to_time_t(timePoint);
	time_tm = *std::localtime(&t_time);
	result.year = time_tm.tm_year + 1900;
	result.month = time_tm.tm_mon + 1;
	result.day = time_tm.tm_mday;
	result.hour = time_tm.tm_hour;
	result.min = time_tm.tm_min;
	result.sec = time_tm.tm_sec;
	result.uSec = std::chrono::duration_cast<std::chrono::microseconds>(timePoint.time_since_epoch()).count() % 1000000;
	return result;
}
std::chrono::system_clock::time_point TimeConverter::toTimePoint(const TimeStructure& time)
{
	std::chrono::system_clock::time_point result;
	tm tm_time = {
		.tm_sec = time.sec,
		.tm_min = time.min,
		.tm_hour = time.hour,
		.tm_mday = time.day,
		.tm_mon = time.month - 1,
		.tm_year = time.year - 1900
	};
	if (time.uSec > 999999)
		tm_time.tm_sec += (int)(time.uSec / 1000000);
	time_t t_time = std::mktime(&tm_time);
	result = std::chrono::system_clock::from_time_t(t_time);
	result += std::chrono::microseconds(time.uSec % 1000000);
	if (time.year != (tm_time.tm_year + 1900) ||
		time.month != (tm_time.tm_mon + 1) ||
		time.day != tm_time.tm_mday ||
		time.hour != tm_time.tm_hour ||
		time.min != tm_time.tm_min ||
		time.sec != tm_time.tm_sec)
	{
		TimeConverter timeConverter;
		std::cout << "Time was converted from: " << timeConverter.timeToString(time) << " to " << timeConverter.timeToString(result) << "\n";
	}
	return result;
};

//class DataStructure
void DataStructure::updateTime()
{
	std::chrono::system_clock::time_point timePoint = clock_.getTime();
	time_ = timeConverter_.toTimeStructure(timePoint);
}
int DataStructure::getYear()
{
	updateTime();
	return time_.year;
};
int DataStructure::getMonth()
{
	updateTime();
	return time_.month;
};
int DataStructure::getDay()
{
	updateTime();
	return time_.day;
};
int DataStructure::getHour()
{
	updateTime(); 
	return time_.hour;
};
int DataStructure::getMin()
{ 
	updateTime(); 
	return time_.min;
};
int DataStructure::getSec()
{ 
	updateTime(); 
	return time_.sec;
};
int DataStructure::getuSec() 
{
	updateTime();
	return time_.uSec;
};
std::string DataStructure::getTime()
{
	updateTime();
	return timeConverter_.timeToString(time_);
}
//std::string DataStructure::getTime() { return converter_.timeToString(time_); }
/*
//for printhing to console during project Testing
inline void PrintTo(TimeStructure& time, std::ostream* os) {
	TimeConverter converter;
	*os << converter.timeToString(time);
};




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
//~class DataStructure
*/
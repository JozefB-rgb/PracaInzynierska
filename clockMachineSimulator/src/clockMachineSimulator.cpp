#include <string>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <iostream>

#include "clockMachineSimulator.h"

clockMachineSimulator::clockMachineSimulator() : year(1970), month(1), day(1), hour(0), min(0), sec(0), uSec(0), offsetYear(0)
{
	;
}

std::string clockMachineSimulator::getNoUpdatedTime()
{
	return timeToString();
}

void clockMachineSimulator::updateTimeValues()
{
	//creates time point to current time
	auto now = std::chrono::system_clock::now();

	//converts time point to seconds passed since 1970-01-01
	time_t now_time_t = std::chrono::system_clock::to_time_t(now);

	//converts passed seconds to "year,month,day hour, min, sec" format
	std::tm now_tm = *std::localtime(&now_time_t);

	year = now_tm.tm_year;
	month = now_tm.tm_mon;
	day = now_tm.tm_mday;
	hour = now_tm.tm_hour;
	min = now_tm.tm_min;
	sec = now_tm.tm_sec;

	//converts time point to us and how many passed since 1970-01-01
	auto now_us_timePoint = std::chrono::time_point_cast<std::chrono::microseconds>(now);

	//converts time point to "classic" variable (here long long) and how many passed only from last second
	uSec = now_us_timePoint.time_since_epoch().count() % 1000000;
}

std::string clockMachineSimulator::timeToString()
{
	std::ostringstream oss;

	oss << std::setw(4) << std::setfill('0') << year << "-" \
		<< std::setw(2) << std::setfill('0') << month << "-" \
		<< std::setw(2) << std::setfill('0') << day << " "
		<< std::setw(2) << std::setfill('0') << hour << ":"
		<< std::setw(2) << std::setfill('0') << min << ":"
		<< std::setw(2) << std::setfill('0') << sec << "."
		<< std::setw(6) << std::setfill('0') << uSec;

	std::string result = oss.str();
	return result;
}

std::string clockMachineSimulator::getTime()
{
	updateTimeValues();
	return timeToString();
}

int clockMachineSimulator::getYear()
{
	updateTimeValues();
	return year;
}

int clockMachineSimulator::getMonth()
{
	updateTimeValues();
	return month;
}

int clockMachineSimulator::getDay()
{
	updateTimeValues();
	return day;
}

int clockMachineSimulator::getHour()
{
	updateTimeValues();
	return hour;
}

int clockMachineSimulator::getMin()
{
	updateTimeValues();
	return min;
}

int clockMachineSimulator::getSec()
{
	updateTimeValues();
	return sec;
}

int clockMachineSimulator::getuSec()
{
	updateTimeValues();
	return uSec;
}


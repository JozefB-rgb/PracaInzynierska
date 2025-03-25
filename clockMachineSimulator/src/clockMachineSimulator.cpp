#include <string>
#include <chrono>

#include "clockMachineSimulator.h"


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
}

std::string clockMachineSimulator::getTime()
{
	return "2000-01-01 12:00:00.000000";
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


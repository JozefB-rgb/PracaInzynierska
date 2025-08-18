#ifndef TIME_MENAGER_H

#define TIME_MENAGER_H

#include <gmock/gmock.h>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <chrono>



struct TimeStructure
{
	int year;
	int month;
	int day;
	int hour; //24h format
	int min;
	int sec;

	long long uSec;

	bool operator==(const TimeStructure& other) const {
		return year == other.year &&
			month == other.month &&
			day == other.day &&
			hour == other.hour &&
			min == other.min &&
			sec == other.sec &&
			uSec == other.uSec;
	}
};

//connvets time data to TimeStructure or to String
class TimeConverter
{
public:
	std::string timeToString(const TimeStructure& time);
	std::string timeToString(const std::chrono::system_clock::time_point& timePoint);
	TimeStructure stringToTime(std::string stringTime);
	TimeStructure toTimeStructure(const std::chrono::system_clock::time_point& timePoint);
	std::chrono::system_clock::time_point toTimePoint(const TimeStructure& time);
};

//the interface to get time values from clock source
class IClock
{
public:
	virtual std::chrono::system_clock::time_point getTime() = 0;
	virtual ~IClock() = default;
};

//mock for using during testing
class MockClock :public IClock
{
public:
	MOCK_METHOD(std::chrono::system_clock::time_point, getTime, (), (override));
};

class TimeMenager
{
	IClock& clock_;
	TimeStructure time_;
	TimeConverter timeConverter_;

	void updateTime();
public:
	TimeMenager(IClock& clockSource) : clock_(clockSource) { ; }
	int getYear();
	int getMonth();
	int getDay();
	int getHour();
	int getMin();
	int getSec();
	int getuSec();
	std::string getTime();
};
;/*
//for printhing to console during project Testing
inline void PrintTo(TimeStructure& time, std::ostream* os);




class TimeMenager {
	bool severRunning_ = false;
	bool connectedToAll_ = false;
	bool timeSynchronized_ = false;

	TimeStructure time_;
	IClock& timeSource_;
	TimeConverter converter_;
	std::string pathToAdressesFile_;

public:
	TimeMenager(IClock& timeSource);
	TimeMenager(IClock& timeSource, std::string pathToAdressesFile);

	bool settingUp();
	bool waitingForConnection();
	bool isSynchronized();

	//update TimeStrucure values form source clock
	void updateTime();
	//getting time form remote devices (via socket) and avrage it with its own
	void synchronizeTime();

	int getYear();
	int getMonth();
	int getDay();
	int getHour();
	int getMin();
	int getSec();
	int getuSec();
	std::string getTime();
};
*/

#endif //TIME_MENAGER_H


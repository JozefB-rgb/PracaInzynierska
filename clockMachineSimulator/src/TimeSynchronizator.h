#ifndef TIME_SYNCHRONIZATOR_H

#define TIME_SYNCHRONIZATOR_H

#include <gmock/gmock.h>
#include <iomanip>
#include <iostream>
#include <sstream>

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
//for printhing to console during project Testing
inline void PrintTo(TimeStructure& time, std::ostream* os);


//the interface to get time values from clock source
class IClock
{
public:
	virtual void getTime(TimeStructure& time) = 0;
	virtual ~IClock() = default;
};


//mock for using during testing
class MockClock :public IClock
{
public:
	MOCK_METHOD(void, getTime, (TimeStructure& time), (override));
};

//connvets time data to TimeStructure or to String
class TimeStructureStringConverter
{
public:
	TimeStructureStringConverter();
	std::string timeToString(TimeStructure& time);
	TimeStructure stringToTime(std::string stringTime);
};


class TimeSynchronizator {
	bool severRunning_ = false;
	bool connectedToAll_ = false;
	bool timeSynchronized_ = false;

	TimeStructure time_;
	IClock& timeSource_;
	TimeStructureStringConverter converter_;
	std::string pathToAdressesFile_;

public:
	TimeSynchronizator(IClock& timeSource);
	TimeSynchronizator(IClock& timeSource, std::string pathToAdressesFile);

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


#endif // !TIME_SYNCHRONIZATOR_H


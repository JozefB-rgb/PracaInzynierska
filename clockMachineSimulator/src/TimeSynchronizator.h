#ifndef TIME_SYNCHRONIZATOR_H

#define TIME_SYNCHRONIZATOR_H

#include <gmock/gmock.h>

struct TimeStructure
{
	int year;
	int month;
	int day;
	int hour; //24h format
	int min;
	int sec;

	long long uSec;
};

class IClock
{
public:
	virtual void getTime(TimeStructure& time) = 0;
	virtual ~IClock() = default;
};

class MockClock :public IClock
{
public:
	MOCK_METHOD(void, getTime, (TimeStructure& time), (override));
};

class TimeToString
{
public:
	TimeToString();
	std::string convertTime(TimeStructure& time);
};

class TimeSynchronizator {
	bool severRunning_ = false;
	bool connectedToAll_ = false;
	bool timeSynchronized_ = false;

	TimeStructure time_;
	IClock& timeSource_;
	TimeToString converter_;
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


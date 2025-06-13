#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <chrono>
#include <iostream>
#include <string>

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
	TimeToString() { ; }
	std::string convertTime(TimeStructure& time)
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
};

class TimeSynchronizator
{
	bool severRunning_ = false;
	bool connectedToAll_ = false;
	bool timeSynchronized_ = false;

	TimeStructure time_;
	IClock& timeSource_;
	TimeToString converter_;
	std::string pathToAdressesFile_;

public:
	TimeSynchronizator(IClock& timeSource) : timeSource_(timeSource) {}
	TimeSynchronizator(IClock& timeSource, std::string pathToAdressesFile) : timeSource_(timeSource), pathToAdressesFile_(pathToAdressesFile) {}

	bool settingUp() {
		if (severRunning_) return true;
		else return false;
	}
	bool waitingForConnection() {
		if (connectedToAll_) return false;
		else return true;
	}
	bool isSynchronized() { return timeSynchronized_; };

	void updateTime() { timeSource_.getTime(time_); };
	void synchronizeTime() { ; };

	int getYear() { return time_.year; };
	int getMonth() { return time_.month; };
	int getDay() { return time_.day; };
	int getHour() { return time_.hour; };
	int getMin() { return time_.min; };
	int getSec() { return time_.sec; };
	int getuSec() { return time_.uSec; };
	std::string getTime() { return converter_.convertTime(time_); }
};

class TimeSynchronizatorTest :public ::testing::Test
{
};


TEST_F(TimeSynchronizatorTest, testDataStructure)
{
	//created mockClock that will pass custom time to module
	MockClock clock;
	TimeStructure customTime = {
		.year = 2025,
		.month = 5,
		.day = 28,
		.hour = 18,
		.min = 19,
		.sec = 20,
		.uSec = 100200
	};

	TimeSynchronizator obj(clock);

	//making clock return custom time
	EXPECT_CALL(clock, getTime(testing::_))
		.WillOnce(testing::Invoke([&customTime](TimeStructure& time) {
		time = customTime;
			}));

	obj.updateTime();

	EXPECT_EQ(obj.getYear(), 2025);
	EXPECT_EQ(obj.getMonth(), 5);
	EXPECT_EQ(obj.getDay(), 28);
	EXPECT_EQ(obj.getHour(), 18);
	EXPECT_EQ(obj.getMin(), 19);
	EXPECT_EQ(obj.getSec(), 20);
	EXPECT_EQ(obj.getuSec(), 100200);

}

TEST_F(TimeSynchronizatorTest, testMakingTimeString)
{
	TimeToString converter;
	TimeStructure customTime = {
		.year = 2025,
		.month = 4,
		.day = 5,
		.hour = 20,
		.min = 21,
		.sec = 29,
		.uSec = 98
	};

	//converts data from structure to string
	std::string timeString = converter.convertTime(customTime);

	EXPECT_EQ(timeString, "2025-04-05 20:21:29.000098");
}

TEST_F(TimeSynchronizatorTest, testTimeStructureThenMakeString)
{
	//created mockClock that will pass custom time to module
	MockClock clock;
	TimeStructure customTime = {
		.year = 1996,
		.month = 12,
		.day = 8,
		.hour = 18,
		.min = 00,
		.sec = 8,
		.uSec = 14052
	};

	TimeSynchronizator obj(clock);

	//making clock return custom time
	EXPECT_CALL(clock, getTime(testing::_))
		.WillOnce(testing::Invoke([&customTime](TimeStructure& time) {
		time = customTime;
			}));

	obj.updateTime();

	EXPECT_EQ(obj.getTime(), "1996-12-08 18:00:08.014052");
}

//test almost the whole module
//creates 2 intances on the same decice, connects them to each other,
//then each one sending its time to other,
//the result time should be in this case arithmetic average form 2 time values
TEST_F(TimeSynchronizatorTest, test2ModulesInOneMachine)
{
	//set up custom MockClocks and time values for programs
	MockClock clock1,clock2;
	TimeStructure customTime1 = {
		.year = 2025,
		.month = 6,
		.day = 8,
		.hour = 17,
		.min = 8,
		.sec = 47,
		.uSec = 60731
	};
	TimeStructure customTime2 = {
		.year = 2025,
		.month = 6,
		.day = 8,
		.hour = 16,
		.min = 58,
		.sec = 3,
		.uSec = 95
	};
	EXPECT_CALL(clock1, getTime(testing::_))
		.WillOnce(testing::Invoke([&customTime1](TimeStructure& time) {
		time = customTime1;
			}));
	EXPECT_CALL(clock2, getTime(testing::_))
		.WillOnce(testing::Invoke([&customTime2](TimeStructure& time) {
		time = customTime2;
			}));

	//the know and expected value of time after synchronization
	std::string averageCustomTime = "0000-00-00 00:00:00.000000"; //to be calculated

	//inside the files there are IP and port adresses of the other program
	std::string pathToAdressesFileProgram1 = "";
	std::string pathToAdressesFileProgram2 = "";

	TimeSynchronizator program1(clock1, pathToAdressesFileProgram1);
	TimeSynchronizator program2(clock2, pathToAdressesFileProgram2);

	//wait till the servers sets up 
	int maxSetUptimeOut = 10;	//ms
	int msWaited = 0;
	while (!program1.settingUp())
	{
		if (msWaited >= maxSetUptimeOut) {
			FAIL() << "Program1 server cannont set up in " << maxSetUptimeOut << "ms" << std::endl;
			break;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		msWaited += 1;
	}
	msWaited = 0;
	while (!program2.settingUp())
	{
		if (msWaited >= maxSetUptimeOut) {
			FAIL() << "Program2 server cannont set up in " << maxSetUptimeOut << "ms" << std::endl;
			break;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		msWaited += 1;
	}

	//checks if both programs are connected
	int maxWaitConnectionTimeOut = 10;
	msWaited = 0;
	while (program1.waitingForConnection()) {
		if (msWaited >= maxWaitConnectionTimeOut) {
			FAIL() << "Program1 cannot connected to all remote devices in " << maxWaitConnectionTimeOut << std::endl;
			break;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		msWaited += 1;
	}
	msWaited = 0;
	while (program2.waitingForConnection()) {
		if (msWaited >= maxWaitConnectionTimeOut) {
			FAIL() << "Program1 cannot connected to all remote devices in " << maxWaitConnectionTimeOut << std::endl;
			break;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		msWaited += 1;
	}

	//only one synchronize command 
	program1.synchronizeTime();
	program2.synchronizeTime();

	//makes sure that the synchronization process finished and ended successfully
	EXPECT_EQ(program1.isSynchronized(), true);
	EXPECT_EQ(program2.isSynchronized(), true);

	std::string program1GlobalTime = program1.getTime();
	std::string program2GlobalTime = program1.getTime();

	EXPECT_EQ(program1GlobalTime, averageCustomTime);
	EXPECT_EQ(program2GlobalTime, averageCustomTime);
}

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
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
	std::string converTime(TimeStructure& time)
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
	TimeStructure time_;
	IClock& timeSource_;
	TimeToString converter_;

public:
	TimeSynchronizator(IClock& timeSource) : timeSource_(timeSource) {}
	void updateTime() { timeSource_.getTime(time_); };

	int getYear() {return time_.year;};
	int getMonth() { return time_.month; };
	int getDay() { return time_.day; };
	int getHour() { return time_.hour; };
	int getMin() { return time_.min; };
	int getSec() { return time_.sec; };
	int getuSec() { return time_.uSec; };
	std::string getTime() { return converter_.converTime(time_); }
};

class TimeSynchronizatorTest :public ::testing::Test
{
};


TEST_F(TimeSynchronizatorTest, testDataStructure)
{
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

	std::string timeString = converter.converTime(customTime);

	EXPECT_EQ(timeString, "2025-04-05 20:21:29.000098");
}

TEST_F(TimeSynchronizatorTest, testTimeStructureThenMakeString)
{
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

	EXPECT_CALL(clock, getTime(testing::_))
		.WillOnce(testing::Invoke([&customTime](TimeStructure& time) {
		time = customTime;
			}));

	obj.updateTime();

	EXPECT_EQ(obj.getTime(), "1996-12-08 18:00:08.014052");
}

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
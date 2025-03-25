#include <gtest/gtest.h>
#include <memory>
#include <chrono>
#include <iostream>

#include "clockMachineSimulator.h"

class clockMachineSimulatorTest : public ::testing::Test
{
protected:
	std::unique_ptr<clockMachineSimulator> obj;

	void SetUp() override
	{
		obj = std::make_unique<clockMachineSimulator>();
	}
};

TEST_F(clockMachineSimulatorTest, checkConstructor)
{
	EXPECT_EQ(obj->getNoUpdatedTime(), "1970-01-01 00:00:00.000000");
}

TEST_F(clockMachineSimulatorTest, checkProgramResponse)
{
	EXPECT_EQ(obj->getTime(), "2000-01-01 12:00:00.000000");
}

TEST_F(clockMachineSimulatorTest, checkCurrentTime)
{
	//creates time point to current time
	auto now = std::chrono::system_clock::now();

	//converts time point to seconds passed since 1970-01-01
	std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);

	//converts passed seconds to "year,month,day hour, min, sec" format
	std::tm now_tm = *std::localtime(&now_time_t);

	EXPECT_EQ(obj->getYear(), now_tm.tm_year);
	EXPECT_EQ(obj->getMonth(), now_tm.tm_mon);
	EXPECT_EQ(obj->getDay(), now_tm.tm_mday);
	EXPECT_EQ(obj->getHour(), now_tm.tm_hour);
	EXPECT_EQ(obj->getMin(), now_tm.tm_min);
	EXPECT_EQ(obj->getSec(), now_tm.tm_sec);
}

TEST_F(clockMachineSimulatorTest, checkMicroseconds)
{
	//creates time point to current time
	auto now = std::chrono::system_clock::now();

	//converts time point to us and how many passed since 1970-01-01
	auto now_us_timePoint = std::chrono::time_point_cast<std::chrono::microseconds>(now);

	//converts time point to "classic" variable (like int) and how many passed only from last second
	auto now_us = now_us_timePoint.time_since_epoch().count() % 1000000;

	//because program execution takes some time this value should be set experientally, recommend values no greater than 1000us
	const long long US_TOLERANCE = 10;
	EXPECT_GE(obj->getuSec(), now_us - US_TOLERANCE);
	EXPECT_LE(obj->getuSec(), now_us + US_TOLERANCE);
}

/*
TEST_F(clockMachineSimulatorTest, testOffsetYear)
{
	//creates time point to current time
	auto now = std::chrono::system_clock::now();

	//converts time point to seconds passed since 1970-01-01
	std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);

	//converts passed seconds to "year,month,day hour, min, sec" format
	std::tm now_tm = *std::localtime(&now_time_t);

	auto offsetYear = 1;

	obj->addOffset(offsetYear, 0, 0, 0, 0, 0);

	EXPECT_EQ(obj->getYear(), now_tm.tm_year + offsetYear);
}*/

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
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

TEST_F(clockMachineSimulatorTest, checkProgramResponse)
{
	EXPECT_NE(obj->getTime(), "2000-01-01 12:00:00.000000");
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

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
#include <gtest/gtest.h>
#include <memory>
#include <chrono>
#include <iostream>
#include <string>

#include "TimeMenager.h"

class TimeMenagerTest :public ::testing::Test
{
};

TEST_F(TimeMenagerTest, testMakingTimeString) {
	TimeStructure customTime = {
		.year = 2025,
		.month = 4,
		.day = 5,
		.hour = 20,
		.min = 21,
		.sec = 29,
		.uSec = 98
	};

	TimeConverter converter;
	std::string timeString = converter.timeToString(customTime);

	EXPECT_EQ(timeString, "2025-04-05 20:21:29.000098");
}

TEST_F(TimeMenagerTest, testStringToTimeStructure) {
	std::string timeString = "1997-11-07 04:12:09.005310";
	TimeStructure time = {
		.year = 1997,
		.month = 11,
		.day = 7,
		.hour = 4,
		.min = 12,
		.sec = 9,
		.uSec = 5310
	};

	TimeConverter converter;
	TimeStructure timeConverted = converter.stringToTime(timeString);

	EXPECT_EQ(time, timeConverted);
}

TEST_F(TimeMenagerTest, testTimeStructureToStringToTimeStructure) {
	TimeStructure time = {
		.year = 925,
		.month = 8,
		.day = 30,
		.hour = 23,
		.min = 04,
		.sec = 00,
		.uSec = 1010
	};

	TimeConverter converter;
	std::string timeString = converter.timeToString(time);
	TimeStructure timeAfterConvertion = converter.stringToTime(timeString);

	EXPECT_EQ(time, timeAfterConvertion);
}

TEST_F(TimeMenagerTest, testTimeStringToTimeStructureToTimeString) {
	//creates some custom time data
	std::string timeString = "1020-02-13 10:15:54.009041";

	//converts data from string to TimeStructure and then back to string
	TimeConverter converter;
	TimeStructure time = converter.stringToTime(timeString);
	std::string timeStringAfterConvertion = converter.timeToString(time);

	EXPECT_EQ(timeString, timeStringAfterConvertion);
}

TEST_F(TimeMenagerTest, testConvertionFromTimeStructureToTimePointAndBack)
{
	std::chrono::system_clock::time_point timePoint;
	TimeConverter timeConverter;
	TimeStructure timeAfterConversion;
	TimeStructure customTime = {
	.year = 2025,
	.month = 1,
	.day = 32,
	.hour = 0,
	.min = 1,
	.sec = 120,
	.uSec = 1000222
	};	//due to overflow data should change to 2025-02-01 00.03.01.000222

	timePoint = timeConverter.toTimePoint(customTime);
	timeAfterConversion = timeConverter.toTimeStructure(timePoint);

	EXPECT_EQ(timeAfterConversion.year, 2025);
	EXPECT_EQ(timeAfterConversion.month, 2);
	EXPECT_EQ(timeAfterConversion.day, 1);
	EXPECT_EQ(timeAfterConversion.hour, 0);
	EXPECT_EQ(timeAfterConversion.min, 3);
	EXPECT_EQ(timeAfterConversion.sec, 1);
	EXPECT_EQ(timeAfterConversion.uSec, 222);
}

TEST_F(TimeMenagerTest, testIfMockInvoceCorrectTime) {
	MockClock clock;
	TimeConverter timeConverter;
	TimeMenager timeMenager(clock);
	TimeStructure customTime = {
		.year = 1999,
		.month = 13,
		.day = 33,
		.hour = 25,
		.min = 67,
		.sec = 184,
		.uSec = 10777333
	};	//due to overflow data should change to 2000-02-03 02.10.14.777333

	EXPECT_CALL(clock, getTime)
		.WillRepeatedly(testing::Return(timeConverter.toTimePoint(customTime)));

	EXPECT_EQ(timeMenager.getYear(), 2000);
	EXPECT_EQ(timeMenager.getMonth(), 2);
	EXPECT_EQ(timeMenager.getDay(), 3);
	EXPECT_EQ(timeMenager.getHour(), 2);
	EXPECT_EQ(timeMenager.getMin(), 10);
	EXPECT_EQ(timeMenager.getSec(), 14);
	EXPECT_EQ(timeMenager.getuSec(), 777333);

}

TEST_F(TimeMenagerTest, testMockTimeThenMakeString) {
	MockClock clock;
	TimeMenager timeMenager(clock);
	TimeConverter timeConverter;
	TimeStructure customTime = {
		.year = 1996,
		.month = 12,
		.day = 8,
		.hour = 18,
		.min = 00,
		.sec = 8,
		.uSec = 14052
	};

	EXPECT_CALL(clock, getTime)
		.WillOnce(testing::Return(timeConverter.toTimePoint(customTime)));

	EXPECT_EQ(timeMenager.getTime(), "1996-12-08 18:00:08.014052");
}

/*
//test almost the whole module
//creates 2 intances on the same decice, connects them to each other,
//then each one sending its time to other,
//the result time should be in this case arithmetic average form 2 time values
TEST_F(TimeMenagerTest, test2ModulesInOneMachine)
{
	//set up custom MockClocks time values for programs
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

	//created MockClocks and set return their custom time
	MockClock clock1, clock2;
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

	//created 2 main programs with MockClocks and paths to files with adress to second program socket
	TimeMenager program1(clock1, pathToAdressesFileProgram1);
	TimeMenager program2(clock2, pathToAdressesFileProgram2);

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
*/
int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
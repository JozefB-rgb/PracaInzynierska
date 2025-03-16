#include <gtest/gtest.h>
#include <memory>
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

TEST_F(clockMachineSimulatorTest, CheckProgramResponse)
{
	EXPECT_NE(obj->getTime(), "2000-01-01 12:00:00.000000");
}

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
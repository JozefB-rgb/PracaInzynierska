#include <gtest/gtest.h>

#include "FileReader.h"

class FileReaderTest :public ::testing::Test {
};

TEST_F(FileReaderTest, testFileReaderCreation)
{
	EXPECT_NO_THROW(FileReader());
}


int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
#include <gtest/gtest.h>
//#include <gmock/gmock.h>

#include "FileReader.h"

class FileReaderTest :public ::testing::Test {
};

TEST_F(FileReaderTest, testFileReaderCreation)
{
	EXPECT_NO_THROW(FileReader());
}

TEST_F(FileReaderTest, testMockReadLine)
{
	MockFileReader fileReader;
	std::string expectedLine = "0.0.0.1,12345";

	EXPECT_CALL(fileReader, readLine)
		.WillOnce(testing::Return(expectedLine));

	EXPECT_EQ(fileReader.readLine(), expectedLine);
}

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

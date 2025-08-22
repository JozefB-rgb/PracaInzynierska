#include <gtest/gtest.h>

#include "SocketMenager.h"

class SocketMenagerTes :public ::testing::Test
{

};



int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
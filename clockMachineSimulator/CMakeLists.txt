add_executable(clockMachineSimulator src/main.cpp  src/TimeSynchronizator.h src/TimeSynchronizator.cpp)

# Find GoogleTest (installed via vcpkg)
find_package(GTest QUIET)
#if not found specify path manually
if(NOT GTest_FOUND)
	#do it here
	set(GTEST_ROOT "C:/vcpkg/vcpkg/scripts/buildsystems/vcpkg.cmake")
	set(CMAKE_PREFIX_PATH "C:/vcpkg/vcpkg/scripts/buildsystems/vcpkg.cmake")

	#refind boost package
	find(GTest REQUIRED)
endif()
include_directories(${GTEST_INCLUDE_DIRS} src/)

add_executable(testClockMachineSimulator tests/test_main.cpp src/TimeSynchronizator.h src/TimeSynchronizator.cpp)

#enables google::test
target_link_libraries(testClockMachineSimulator GTest::GTest GTest::Main)

#enables google::mock
target_link_libraries(testClockMachineSimulator gmock gmock_main)



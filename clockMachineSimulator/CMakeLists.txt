add_executable(clockMachineSimulator src/main.cpp  "src/DataStructure.h" "src/DataStructure.cpp")

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

add_executable(testDataStructure "tests/testDataStructure.cpp" "src/DataStructure.h" "src/DataStructure.cpp")
target_link_libraries(testDataStructure GTest::GTest GTest::Main gmock gmock_main)

add_executable(testIPStructures "tests/testIPStructures.cpp" "src/IPStructures.h" "src/IPStructures.cpp")
target_link_libraries(testIPStructures GTest::GTest GTest::Main)

add_executable(testFileReader "tests/testFileReader.cpp" "src/FileReader.h" "src/FileReader.cpp" "src/IPStructures.h" "src/IPStructures.cpp")
target_link_libraries(testFileReader GTest::GTest GTest::Main gmock gmock_main)

add_test(NAME DataStructure COMMAND testClockMachineSimulator)
add_test(NAME IPStructures COMMAND testIPStructures)
add_test(NAME FileReader COMMAND testFileReader)



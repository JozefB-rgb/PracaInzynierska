add_executable(clockMachineSimulator src/main.cpp  "src/TimeMenager.h" "src/TimeMenager.cpp")

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

add_executable(testTimeMenager "tests/testTimeMenager.cpp" "src/TimeMenager.h" "src/TimeMenager.cpp")
target_link_libraries(testTimeMenager GTest::GTest GTest::Main gmock gmock_main)

add_executable(testIPStructures "tests/testIPStructures.cpp" "src/IPStructures.h" "src/IPStructures.cpp")
target_link_libraries(testIPStructures GTest::GTest GTest::Main)

add_executable(testAdressFromFileLoader "tests/testAdressFormFileLoader.cpp" "src/AdressFormFileLoader.h" "src/AdressFormFileLoader.cpp" "src/IPStructures.h" "src/IPStructures.cpp")
target_link_libraries(testAdressFromFileLoader GTest::GTest GTest::Main gmock gmock_main)

add_test(NAME TimeMenager COMMAND testTimeMenager)
add_test(NAME IPStructures COMMAND testIPStructures)
add_test(NAME AdressFromFileLoader COMMAND testAdressFromFileLoader)



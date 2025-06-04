#set project name
project(Inzynierka)

#set compiltaion requirements
cmake_minimum_required(VERSION 3.29.1)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

#includes Ctest that allows make tests witch cmake
include(CTest)

#Enable testing project. I'm using Gtest.
enable_testing()

#adding subdirectories for creating multiple executable files
add_subdirectory(clockMachineSimulator)


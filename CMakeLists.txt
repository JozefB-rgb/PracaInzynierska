#set project name
project(Inzynierka)

#set compiltaion requirements
cmake_minimum_required(VERSION 3.29.1)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED true)

#adding subdirectories for creating multiple executable files
add_subdirectory(clockMachineSimulator)


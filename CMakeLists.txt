cmake_minimum_required(VERSION 3.9)
project(ex1)

set(CMAKE_CXX_STANDARD 11)

add_executable(ex1 main.cpp Terminal.cpp Terminal.h File.cpp File.h Folder.cpp Folder.h mainFunctions.cpp mainFunctions.h)
cmake_minimum_required(VERSION 3.17)
project(backpack)

set(CMAKE_CXX_STANDARD 14)

add_executable(backpack main.cpp Sequence.hpp LinkedList.hpp LinkedListSequence.hpp DynamicArray.hpp ArraySequence.hpp)
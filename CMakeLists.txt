cmake_minimum_required(VERSION 3.13)
project(BestBuddiesSimilarity)

set(CMAKE_CXX_STANDARD 14)

add_executable(${PROJECT_NAME} main.cpp BestBuddiesSimilarity.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR})
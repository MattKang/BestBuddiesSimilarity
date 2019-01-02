cmake_minimum_required(VERSION 3.13)
project(BestBuddiesSimilarity)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV REQUIRED)

add_executable(${PROJECT_NAME} main.cpp BestBuddiesSimilarity.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE ${OpenCV_LIBS})
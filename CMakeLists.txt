cmake_minimum_required(VERSION 3.27)
project(Test)

set(CMAKE_CXX_STANDARD 14)

include_directories("D:\\boost\\boost_1_84_0")
find_package(CURL)
find_package(nlohmann_json)
add_executable(Test
        Price/PriceSource.cpp
        Price/PriceSource.h
        Test.cpp
        Price/WebRequest.cpp
        Price/WebRequest.h
        Price/Price.cpp
        Price/Price.h
        Portfolio/Portfolio.cpp
        Portfolio/Portfolio.h
        Portfolio/Position.cpp
        Portfolio/Position.h
        Price/PriceSourceFactory.cpp
        Price/PriceSourceFactory.h)

target_link_libraries(Test CURL::libcurl)
target_link_libraries(Test nlohmann_json::nlohmann_json)
#target_link_libraries(Test "D:\\boost\\boost_1_84_0\\stage\\lib")

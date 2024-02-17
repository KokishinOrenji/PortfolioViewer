cmake_minimum_required(VERSION 3.27)
project(PortfolioViewer)

set(CMAKE_CXX_STANDARD 14)

include_directories("D:\\boost\\boost_1_84_0")
find_package(CURL)
find_package(nlohmann_json)
add_executable(PortfolioViewer
        Price/PriceSource.cpp
        Price/PriceSource.h
        PortfolioViewer.cpp
        Price/WebRequest.cpp
        Price/WebRequest.h
        Price/Price.cpp
        Price/Price.h
        Portfolio/Portfolio.cpp
        Portfolio/Portfolio.h
        Portfolio/Position.cpp
        Portfolio/Position.h
        Price/PriceSourceFactory.cpp
        Price/PriceSourceFactory.h
        Price/YahooPriceSource.cpp
        Price/YahooPriceSource.h
        Price/FilePriceSource.cpp
        Price/FilePriceSource.h
        Price/FilePriceRepository.cpp
        Price/FilePriceRepository.h)

target_link_libraries(PortfolioViewer CURL::libcurl)
target_link_libraries(PortfolioViewer nlohmann_json::nlohmann_json)
#target_link_libraries(PortfolioViewer "D:\\boost\\boost_1_84_0\\stage\\lib")

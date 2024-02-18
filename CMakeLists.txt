cmake_minimum_required(VERSION 3.27)
project(PortfolioViewer)

set(CMAKE_CXX_STANDARD 14)

include_directories("D:\\boost\\boost_1_84_0")
find_package(CURL)
find_package(nlohmann_json)
add_executable(PortfolioViewer
        src/Price/PriceSource.cpp
        src/Price/PriceSource.h
        src/main.cpp
        src/Price/HttpClient.cpp
        src/Price/HttpClient.h
        src/Price/Price.cpp
        src/Price/Price.h
        src/Portfolio/Portfolio.cpp
        src/Portfolio/Portfolio.h
        src/Portfolio/Position.cpp
        src/Portfolio/Position.h
        src/Price/PriceSourceFactory.cpp
        src/Price/PriceSourceFactory.h
        src/Price/YahooPriceSource.cpp
        src/Price/YahooPriceSource.h
        src/Price/FilePriceSource.cpp
        src/Price/FilePriceSource.h
        src/Price/FilePriceRepository.cpp
        src/Price/FilePriceRepository.h
        src/Price/WebPriceSource.cpp
        src/Price/WebPriceSource.h)

target_link_libraries(PortfolioViewer CURL::libcurl)
target_link_libraries(PortfolioViewer nlohmann_json::nlohmann_json)

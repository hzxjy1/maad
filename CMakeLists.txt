cmake_minimum_required(VERSION 3.10)
project(maad)

file(GLOB SOURCES "*.cpp")
add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})

set(LIB_PATHS "${CMAKE_CURRENT_SOURCE_DIR}" "/usr/lib")

# maacore
find_library(MAACORE_LIB MaaCore NAMES MaaCore PATHS ${LIB_PATH})

# jsoncpp
find_package(jsoncpp REQUIRED)

# cli11
find_package(CLI11 REQUIRED)

# spdlog
find_package(spdlog REQUIRED)

target_link_libraries(${CMAKE_PROJECT_NAME} ${MAACORE_LIB} jsoncpp_lib spdlog::spdlog_header_only)

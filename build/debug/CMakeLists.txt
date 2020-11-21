cmake_minimum_required(VERSION 3.15)
project(AoC_2020_dbg)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_SKIP_INSTALL_RULES True)
set(CMAKE_BUILD_TYPE Debug)

# Set target names
set(BIN_TARGET ${CMAKE_PROJECT_NAME})

# Add include directory and implementation files
include_directories(../../include/)
file(GLOB COMMON_SRC ../../src/common/*.cpp)

# Copy data files
file(COPY ../../data DESTINATION ${CMAKE_BINARY_DIR})

# Add bin targets
add_executable(day01_1 ../../src/day01/day01_1.cpp ${COMMON_SRC})
add_executable(day01_2 ../../src/day01/day01_2.cpp ${COMMON_SRC})


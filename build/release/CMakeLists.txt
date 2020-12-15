cmake_minimum_required(VERSION 3.15)
project(AoC_2020)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_SKIP_INSTALL_RULES True)
set(CMAKE_BUILD_TYPE Release)

# Set target names
set(BIN_TARGET ${CMAKE_PROJECT_NAME})

# Add include directory and implementation files
include_directories(../../include/)
file(GLOB COMMON_SRC ../../src/common/*.cpp)

# Copy data files
file(COPY ../../data DESTINATION ${CMAKE_BINARY_DIR})

# Add all targets (consider all source files under /src)
file(GLOB files "../../src/*.cpp")
foreach(file ${files})
  string(SUBSTRING ${file} 52 7 filename)
  add_executable(${filename} ../../src/${filename}.cpp ${COMMON_SRC})
endforeach()

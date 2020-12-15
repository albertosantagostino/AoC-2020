#!/bin/bash

# Create empty source files, data and CMake targets for the specified day
# Usage: ./newday.sh <DAY_NUMBER>
#        DAY_NUMBER     = Day to add (01-25)

touch ./src/day$1_1.cpp
touch ./src/day$1_2.cpp
touch ./data/day$1.txt
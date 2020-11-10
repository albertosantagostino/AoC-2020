#!/bin/bash

# Prepare and compile targets for specified build type
# Usage: ./build.sh <BUILD_TYPE> <TARGET>
#        BUILD_TYPE = [DBG,REL] (Debug, Release)
#        TARGET     = Target name as specified in CMakeLists.txt

build_debug() {
    mkdir -p bin/Debug
    cmake -DCMAKE_CXX_COMPILER=g++ -DCMAKE_BUILD_TYPE=Debug .
    if [ $# -eq 1 ]; then
        make $1
    else
        make
    fi
}

build_release() {
    mkdir -p bin/Release
    cmake -DCMAKE_CXX_COMPILER=g++ -DCMAKE_BUILD_TYPE=Release .
    if [ $# -eq 1 ]; then
        make $1
    else
        make
    fi
}

if [[ $# -eq 0 ]]; then
    build_debug
    build_release
    exit 0
fi

case $1 in
DBG)
    build_debug $2
    ;;
REL)
    build_release $2
    ;;
*)
    echo Usage: build.sh [type=DBG,REL] [target]
    ;;
esac

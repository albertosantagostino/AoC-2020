#!/bin/bash

# Prepare and compile targets for specified build type
# Usage: ./build.sh <BUILD_TYPE> <TARGET>
#        BUILD_TYPE = [DBG,REL] (Debug, Release)
#        TARGET     = Target name as specified in CMakeLists.txt

build_debug() {
    cd build/debug
    mkdir -p bin
    cd bin
    cmake ..
    if [ $# -eq 1 ]; then
        make $1 -j 4
    else
        make -j 4
    fi
    cd ../../../
}

build_release() {
    cd build/release
    mkdir -p bin
    cd bin
    cmake ..
    if [ $# -eq 1 ]; then
        make $1 -j 4
    else
        make -j 4
    fi
    cd ../../../
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

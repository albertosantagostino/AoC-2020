# Advent of Code 2020 (C++) 🎄

<div align="center">

| Day                                            | 1                     | 2                     |
| ---------------------------------------------- | :-------------------: | :-------------------: |
| **[01](https://adventofcode.com/2020/day/1)**  | [⭐](src/day01_1.cpp) | [⭐](src/day01_2.cpp) |
| **[02](https://adventofcode.com/2020/day/2)**  | [⭐](src/day02_1.cpp) | [⭐](src/day02_2.cpp) |

</div>

(Click on the ⭐, jump to the code)

### Build process

Every puzzle is a CMake target named using the following form: `day01_1` (puzzle day 1, part 1)
The script `build.sh` takes care of the building process. To build a target:

**Release configuration**
`./build.sh REL` or `./build.sh REL <TARGET>`

To run the built target, `./build/release/bin/day01_1`

**Debug configuration**
`./build.sh DBG` or `./build.sh DBG <TARGET>`

The debug configuration is configured to facilitate Visual Studio Code debugging. After breakpoints are set, press `F5` to build and debug interactively the source file currently opened

#### Requirements

CMake ≥ 3.15, gcc ≥ 9.3


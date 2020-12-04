# Advent of Code 2020 (C++) 🎄

<div align="center">

| Day                                            | 1                     | 2                     | Solved on time |
| ---------------------------------------------- | :-------------------: | :-------------------: | :----------: |
| **[01](https://adventofcode.com/2020/day/1)**  | [⭐](src/day01_1.cpp) | [⭐](src/day01_2.cpp) | 🟢 🟢        |
| **[02](https://adventofcode.com/2020/day/2)**  | [⭐](src/day02_1.cpp) | [⭐](src/day02_2.cpp) | 🟢 🟢        |
| **[03](https://adventofcode.com/2020/day/3)**  | [⭐](src/day03_1.cpp) | [⭐](src/day03_2.cpp) | 🟢 🟢        |
| **[04](https://adventofcode.com/2020/day/4)**  | [⭐](src/day04_1.cpp) | [⭐](src/day04_2.cpp) | 🟢 🟢        |

</div>

Click on the ⭐, go to the code  
Solved on time column: 🟢 = same day, 🟡 = within 3 days, 🔴 = more than 3 days

### Build process

Every puzzle is a CMake target named using the following form: `day01_1` (puzzle day 1, part 1)
The script `build.sh` takes care of the building process. To build a target:

**Release configuration: run and build a target**  
`./build.sh REL` or `./build.sh REL <TARGET>`

To run the built target, `./build/release/bin/day01_1`

**Debug configuration**  
The script is used to facilitate Visual Studio Code debugging. Everything works out-of-the-box if the `AoC-2020 folder` is opened in VSCode  
After breakpoints are set, press `F5` to build and debug interactively the source file currently displayed

### Dependencies / Requirements

This year I'm using a "primitive" header-only library I wrote from scratch: **[commonlib](https://github.com/albertosantagostino/commonlib-cpp)**  
It's linked as a submodule under `include/commonlib`

For building, CMake ≥ 3.15 and gcc ≥ 9.3 are required

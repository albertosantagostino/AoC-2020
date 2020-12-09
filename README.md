# Advent of Code 2020 (C++) 🎄

<div align="center">

| Day                                            | 1                     | 2                     | Solved on time |
| ---------------------------------------------- | :-------------------: | :-------------------: | :------------: |
| **[01](https://adventofcode.com/2020/day/1)**  | [⭐](src/day01_1.cpp) | [⭐](src/day01_2.cpp) | 🟢 🟢          |
| **[02](https://adventofcode.com/2020/day/2)**  | [⭐](src/day02_1.cpp) | [⭐](src/day02_2.cpp) | 🟢 🟢          |
| **[03](https://adventofcode.com/2020/day/3)**  | [⭐](src/day03_1.cpp) | [⭐](src/day03_2.cpp) | 🟢 🟢          |
| **[04](https://adventofcode.com/2020/day/4)**  | [⭐](src/day04_1.cpp) | [⭐](src/day04_2.cpp) | 🟢 🟢          |
| **[05](https://adventofcode.com/2020/day/5)**  | [⭐](src/day05_1.cpp) | [⭐](src/day05_2.cpp) | 🟢 🟢          |
| **[06](https://adventofcode.com/2020/day/6)**  | [⭐](src/day06_1.cpp) | [⭐](src/day06_2.cpp) | 🟢 🟢          |
| **[07](https://adventofcode.com/2020/day/7)**  |                       |                       |                |
| **[08](https://adventofcode.com/2020/day/8)**  | [⭐](src/day08_1.cpp) | [⭐](src/day08_2.cpp) | 🟢 🟢          |
| **[09](https://adventofcode.com/2020/day/9)**  | [⭐](src/day09_1.cpp) | [⭐](src/day09_2.cpp) | 🟢 🟢          |

</div>

Click on the ⭐, go to the code  
"Solved on time" column: 🟢 = same day, 🟡 = within 3 days, 🔴 = within 1 week, ⚫ = more than 1 week

### Build process

Every puzzle is a CMake target named using the form: `day01_1` (as an example, for the puzzle of day 1, part 1)
The script `build.sh` takes care of the building process. To build a target:

**Release configuration: build/run**  
Build all targets: `./build.sh REL`  
Build a specific target: (for example `day01_1`): `./build.sh REL day01_1`  
Run a target, `./build/release/bin/day01_1`

**Debug configuration**  
The script is used to facilitate Visual Studio Code debugging. Everything works out-of-the-box opening the `AoC-2020` folder in VSCode  
After breakpoints are set, press `F5` to build and debug interactively the source file currently displayed

### Dependencies / Requirements

This year I'm using a "primitive" header-only library I wrote from scratch: **[commonlib](https://github.com/albertosantagostino/commonlib-cpp)**  
It's linked as a submodule under `include/commonlib`

For building, CMake ≥ 3.15 and gcc ≥ 9.3 are required

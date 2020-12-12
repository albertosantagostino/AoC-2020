#include <fstream>
#include <iostream>
#include <map>
#include <vector>

#include <commonlib/include/primitives/position.h>

typedef commonlib::Position<int> Position;

typedef std::pair<int, int> Direction;

constexpr Direction kDirection_East{1, 0};
constexpr Direction kDirection_North{0, 1};
constexpr Direction kDirection_West{-1, 0};
constexpr Direction kDirection_South{0, -1};

std::map<int, Direction> DirectionsMap{{0, kDirection_East},
                                       {90, kDirection_North},
                                       {180, kDirection_West},
                                       {270, kDirection_South}};

void WrapDirection(int& orientation)
{
    if (orientation < 0)
    {
        orientation += 360;
    }
    else if (orientation >= 360)
    {
        orientation -= 360;
    }
}

int main()
{
    // Load data
    std::ifstream fp("data/day12.txt");

    // Until the grid is updated at every step, create a new grid and update the layout
    Position pos{0, 0};
    int deg{0};
    std::string str;
    // For each action, apply it and if needed wrap the orientation to 360
    while (std::getline(fp, str))
    {
        const char action{str[0]};
        const int value{std::stoi(str.substr(1))};
        switch (action)
        {
            case 'N':
                pos += Position(kDirection_North) * value;
                break;
            case 'S':
                pos += Position(kDirection_South) * value;
                break;
            case 'E':
                pos += Position(kDirection_East) * value;
                break;
            case 'W':
                pos += Position(kDirection_West) * value;
                break;
            case 'L':
                deg += value;
                WrapDirection(deg);
                break;
            case 'R':
                deg -= value;
                WrapDirection(deg);
                break;
            case 'F':
                pos += Position(DirectionsMap[deg]) * value;
                break;
            default:
                break;
        }
    }
    std::cout << abs(pos.x) + abs(pos.y) << std::endl;

    return EXIT_SUCCESS;
}

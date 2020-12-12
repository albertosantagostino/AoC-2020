#include <fstream>
#include <iostream>
#include <vector>

#include <commonlib/include/data_structures/grid.h>

using commonlib::Grid;

void StepGrid(Grid& previous_grid, Grid& new_grid)
{
    constexpr char kEmptySeat{'L'};
    constexpr char kOccupiedSeat{'#'};
    constexpr char kFloor{'.'};

    for (std::size_t i{0U}; i < previous_grid.NRows(); ++i)
    {
        for (std::size_t j{0U}; j < previous_grid.NRows(); ++j)
        {
            const char curr{previous_grid(i, j)};
            if (curr != kFloor)
            {
                // Obtain the grid neighbours
                auto neighbours = previous_grid.CutWindow(i, j, 3U, kFloor);
                const char current_seat{neighbours(1, 1)};
                neighbours(1, 1) = kFloor;
                const std::size_t empty_seats = neighbours.CountElements(kEmptySeat);
                const std::size_t occupied_seats = neighbours.CountElements(kOccupiedSeat);
                new_grid(i, j) = curr;
                switch (current_seat)
                {
                    case kEmptySeat:
                        if (occupied_seats == 0U)
                        {
                            new_grid(i, j) = kOccupiedSeat;
                        }
                        break;
                    case kOccupiedSeat:
                        if (occupied_seats >= 4U)
                        {
                            new_grid(i, j) = kEmptySeat;
                        }
                        break;
                    default:
                        break;
                }
            }
        }
    }
}

int main()
{
    // Load data
    std::ifstream fp("data/day11.txt");
    Grid previous_grid{fp, '\0'};

    // Until the grid is updated at every step, create a new grid and update the layout
    std::size_t occupied_seats{0U};
    while (true)
    {
        Grid new_grid(previous_grid.NRows(), previous_grid.NCols());
        StepGrid(previous_grid, new_grid);
        if (new_grid == previous_grid)
        {
            occupied_seats = new_grid.CountElements('#');
            break;
        }
        previous_grid = new_grid;
    }

    std::cout << occupied_seats << std::endl;

    return EXIT_SUCCESS;
}

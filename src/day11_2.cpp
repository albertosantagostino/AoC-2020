#include <fstream>
#include <iostream>
#include <vector>

#include <commonlib/include/data_structures/grid.h>

using commonlib::Grid;

std::size_t CastStarRays(Grid& grid, const std::size_t row, const std::size_t col)
{
    std::size_t nrows = grid.NRows();
    std::size_t ncols = grid.NCols();
    std::size_t occupied_seats{0U};
    // Use two values to store x,y and cover all possible 8 cases (directions)
    for (int ray_i{1}; ray_i >= -1; --ray_i)
    {
        for (int ray_j{1}; ray_j >= -1; --ray_j)
        {
            if ((ray_i != 0) || (ray_j != 0))
            {
                int curr_row = row + ray_i;
                int curr_col = col + ray_j;
                // While we are inside the grid, continue to cast the ray
                while ((curr_row >= 0) && (curr_row < nrows) && (curr_col >= 0) && (curr_col < ncols))
                {
                    const char grid_entry = grid(curr_row, curr_col);
                    if (grid_entry == 'L')
                    {
                        break;
                    }
                    else if (grid_entry == '#')
                    {
                        occupied_seats++;
                        break;
                    }
                    curr_row += ray_i;
                    curr_col += ray_j;
                }
            }
        }
    }
    return occupied_seats;
}

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
                // Obtain the visible seats casting rays in all direction
                const std::size_t occupied_seats = CastStarRays(previous_grid, i, j);
                new_grid(i, j) = curr;
                switch (curr)
                {
                    case kEmptySeat:
                        if (occupied_seats == 0U)
                        {
                            new_grid(i, j) = kOccupiedSeat;
                        }
                        break;
                    case kOccupiedSeat:
                        if (occupied_seats >= 5U)
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

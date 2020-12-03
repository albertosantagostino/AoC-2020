#include <fstream>
#include <iostream>

#include <commonlib/include/data_structures/grid.h>
#include <commonlib/include/data_structures/matrix.h>
#include <commonlib/include/primitives/position.h>

using commonlib::Grid;
using commonlib::Position;
using commonlib::TileType;

typedef Position<std::size_t> GridPosition;

int main()
{
    // Load data
    std::ifstream fp;
    fp.open("data/day03.txt", std::ifstream::in);
    // Initialize the grid (no separator), set tree tiles and make the grid infinite (repeat pattern)
    Grid grid(fp, '\0');
    grid.AddTileTypeDefinition(TileType::kTileType_Tree, '#');
    grid.MakeInfinite(true);

    // Define the slope to traverse
    const GridPosition slope(1U, 3U);
    // Search for trees until the bottom of the grid is reached
    GridPosition pos{0U, 0U};
    std::size_t trees{0U};
    while ((pos.x < grid.NRows() - 1U))
    {
        pos += slope;
        if (grid.GetTileType(pos.x, pos.y) == TileType::kTileType_Tree)
        {
            trees++;
        }
    }

    std::cout << trees << std::endl;

    return EXIT_SUCCESS;
}

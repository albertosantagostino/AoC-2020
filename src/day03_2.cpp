#include <fstream>
#include <iostream>
#include <vector>

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

    // Define the slopes to traverse
    std::vector<GridPosition> slopes({{1U, 1U}, {1U, 3U}, {1U, 5U}, {1U, 7U}, {2U, 1U}});
    std::size_t mul_trees{1U};
    // For each slope search for trees until the bottom of the grid is reached
    for (auto slope : slopes)
    {
        GridPosition pos{0U, 0U};
        std::size_t trees{0U};
        while (pos.x < grid.NRows() - 1U)
        {
            pos += slope;
            if (grid.GetTileType(pos.x, pos.y) == TileType::kTileType_Tree)
            {
                trees++;
            }
        }
        // Multiply together the trees for each slope
        mul_trees *= trees;
    }

    std::cout << mul_trees << std::endl;

    return EXIT_SUCCESS;
}

#include <fstream>
#include <iostream>
#include <set>
#include <vector>

int main()
{
    // Populate a vector of pairs with all possible seats positions
    std::set<std::pair<std::size_t, std::size_t>> seats;
    for (std::size_t i = 0U; i < 128U; ++i)
    {
        for (std::size_t j = 0U; j < 8U; ++j)
        {
            seats.insert(std::make_pair(i, j));
        }
    }

    // Load data and compute seat position and ID while reading
    std::ifstream fp("data/day05.txt");
    std::string seat_str;
    while (std::getline(fp, seat_str))
    {
        // Use reduced rows
        std::pair<std::size_t, std::size_t> rows{1U, 127U};
        std::pair<std::size_t, std::size_t> cols{0U, 7U};

        for (char rc : seat_str)
        {
            switch (rc)
            {
                case 'F':
                    rows.second = (rows.first + rows.second) / 2;
                    break;
                case 'B':
                    rows.first = (rows.first + rows.second) / 2;
                    break;
                case 'L':
                    cols.second = (cols.first + cols.second) / 2;
                    break;
                case 'R':
                    cols.first = (cols.first + cols.second) / 2;
                    break;
                default:
                    break;
            }
        }
        // Remove from the set the reserved seats
        seats.erase(std::make_pair(rows.second, cols.second));
    }

    // Remove all front and back seats
    std::erase_if(seats, [](auto const& e) { return ((e.first == 0U) || (e.first == 125U)); });

    // Populate a vector of possible IDs
    std::vector<std::size_t> ids;
    for (auto el : seats)
    {
        ids.push_back((el.first * 8) + el.second);
    }

    // Find the "discontinuous" ID
    for (std::size_t i = 0; i < ids.size(); ++i)
    {
        if (ids[i] + 1 != ids[i + 1])
        {
            std::cout << ids[i + 1] << std::endl;
            break;
        }
    }

    return EXIT_SUCCESS;
}

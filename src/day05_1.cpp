#include <fstream>
#include <iostream>
#include <set>
#include <vector>

int main()
{
    // Load data and compute seat position and ID while reading
    std::ifstream fp("data/day05.txt");
    std::string seat_str;
    std::size_t max_seat_id{0U};
    while (std::getline(fp, seat_str))
    {
        std::pair<std::size_t, std::size_t> rows{0U, 127U};
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
        std::size_t seat_id = (rows.second * 8) + cols.second;
        if (seat_id > max_seat_id)
        {
            max_seat_id = seat_id;
        }
    }

    std::cout << max_seat_id << std::endl;

    return EXIT_SUCCESS;
}

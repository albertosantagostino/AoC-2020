#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

bool SumGivesDesiredNumber(std::vector<int> sub_vec, const int desired_number)
{
    if (std::accumulate(sub_vec.begin(), sub_vec.end(), decltype(sub_vec)::value_type(0)) == desired_number)
    {
        return true;
    }
    return false;
}

int main()
{
    // Load data
    std::ifstream fp("data/day09.txt");
    std::istream_iterator<int> start(fp), end;
    std::vector<int> numbers(start, end);

    // Search a growing window where all numbers summed give the desired one
    const int desired_number{18272118};
    bool found{false};
    for (std::size_t i{0U}; ((i < numbers.size()) && !found); ++i)
    {
        std::size_t width{1U};
        while ((i + width) < numbers.size() && !found)
        {
            std::vector<int> sub_vec(&numbers[i], &numbers[i + width]);
            if (SumGivesDesiredNumber(sub_vec, desired_number))
            {
                const int min{*std::min_element(sub_vec.begin(), sub_vec.end())};
                const int max{*std::max_element(sub_vec.begin(), sub_vec.end())};
                std::cout << min + max << std::endl;
                found = true;
            }
            width++;
        }
    }

    return EXIT_SUCCESS;
}

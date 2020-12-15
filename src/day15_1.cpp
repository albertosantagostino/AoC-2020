#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <sstream>
#include <vector>

void UpdateSpokenNumbers(const std::size_t new_num, std::map<std::size_t, std::size_t>& spoken_numbers)
{
    auto it = spoken_numbers.find(new_num);
    if (it != spoken_numbers.end())
    {
        it->second++;
    }
    else
    {
        spoken_numbers.insert({new_num, 1U});
    }
}

int main()
{
    // Load data
    std::ifstream fp("data/day15.txt");
    std::istream_iterator<int> start(fp), end;
    std::vector<std::size_t> nums(start, end);
    std::size_t j{0U};
    std::map<std::size_t, std::size_t> spoken_numbers;
    for (auto num : nums)
    {
        UpdateSpokenNumbers(num, spoken_numbers);
        j++;
    }
    for (j - 1U; j < 2020U; ++j)
    {
        auto it = spoken_numbers.find(nums[j - 1U]);
        if (it->second != 1U)
        {
            const auto found = std::find(nums.rbegin() + 1U, nums.rend(), nums[j - 1U]);
            const std::size_t num = std::distance(nums.rbegin() + 1U, found) + 1U;
            nums.push_back(num);
            UpdateSpokenNumbers(num, spoken_numbers);
        }
        else
        {
            nums.push_back(0U);
            UpdateSpokenNumbers(0U, spoken_numbers);
        }
    }

    std::cout << nums.back() << std::endl;

    return EXIT_SUCCESS;
}
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <numeric>
#include <vector>

int main()
{
    // Load data
    std::ifstream fp("data/day10.txt");
    std::istream_iterator<int> start(fp), end;
    std::vector<int> adapters(start, end);

    // Sort the vector and prepare a map to store the used adapters
    std::sort(adapters.begin(), adapters.end());
    std::size_t current_jolts{0U};
    std::map<std::size_t, std::size_t> used_adapters{{1U, 0U}, {2U, 0U}, {3U, 0U}};

    // Loop through the adapters, check which ones are compatible and use the one with the min difference
    while (true)
    {
        std::vector<std::size_t> candidates;
        std::for_each(adapters.begin(), adapters.end(), [&current_jolts, &candidates](auto& adapter) {
            const size_t jolts_diff{adapter - current_jolts};
            if ((jolts_diff > 0U) && (jolts_diff <= 3U))
            {
                candidates.push_back(adapter);
            }
        });
        if (!candidates.empty())
        {
            const std::size_t min{*std::min_element(candidates.begin(), candidates.end())};
            used_adapters[min - current_jolts]++;
            current_jolts = min;
            std::remove(adapters.begin(), adapters.end(), min);
            continue;
        }
        break;
    }

    // Add the final 3 jolts adapter
    current_jolts += 3U;
    used_adapters[3U]++;

    std::cout << used_adapters[1U] * used_adapters[3U] << std::endl;

    return EXIT_SUCCESS;
}

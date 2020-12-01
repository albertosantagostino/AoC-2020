#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

int main()
{
    // Load data
    std::ifstream fp("data/day01.txt");
    std::vector<int> expenses;
    std::string str;
    while (std::getline(fp, str))
    {
        expenses.push_back(std::stoi(str));
    }

    std::sort(expenses.begin(), expenses.end());

    // For each value, look (in reverse order) for its complement to 2020
    for (const auto& value : expenses)
    {
        auto it = std::find(expenses.rbegin(), expenses.rend(), 2020 - value);
        if (it != expenses.rend())
        {
            std::cout << 2020 - value << " x " << value << " = " << value * (*it) << std::endl;
            break;
        }
    }

    return EXIT_SUCCESS;
}

#include <algorithm>
#include <fstream>
#include <iostream>
#include <unordered_set>
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

    // Sort the expenses vector
    std::sort(expenses.begin(), expenses.end());

    // Double iterate on the vector and use a set to find the third element to complete the triplet
    for (auto it1 = expenses.begin(); it1 != expenses.end(); ++it1)
    {
        std::unordered_set<int> uset;
        for (auto it2 = it1 + 1; it2 != expenses.end(); ++it2)
        {
            if (uset.find(2020 - (*it1) - (*it2)) != uset.end())
            {
                const int third = 2020 - (*it1) - (*it2);
                std::cout << (third * (*it1) * (*it2)) << std::endl;
                break;
            }
            uset.insert(*it2);
        }
    }

    return EXIT_SUCCESS;
}

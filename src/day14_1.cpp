#include <bitset>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <numeric>
#include <regex>
#include <sstream>
#include <vector>

std::string ApplyBitmask(const std::string& binary_number, const std::string& bitmask)
{
    std::string res{"000000000000000000000000000000000000"};
    for (int i{35U}; i >= 0; --i)
    {
        if (bitmask[i] == 'X')
        {
            res[i] = binary_number[i];
        }
        else
        {
            res[i] = bitmask[i];
        }
    }
    return res;
}

int main()
{
    // Load data
    std::ifstream fp("data/day14.txt");
    std::map<std::size_t, unsigned long> memory;
    // For each line, store the mask or compute the memory value and store it
    std::string str;
    std::string mask;
    const std::regex re("\\[(.*?)\\]");
    while (std::getline(fp, str))
    {
        std::istringstream iss(str);
        std::vector<std::string> words{std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{}};
        if (words[0] == "mask")
        {
            mask = words[2];
        }
        else
        {
            std::smatch sm;
            regex_search(words[0], sm, re);
            std::size_t mem_address = std::stoi(sm[1]);
            std::string bin_num = std::bitset<36U>(std::stoi(words[2])).to_string();
            bin_num = std::string(36U - bin_num.length(), '0') + bin_num;
            std::string mem_value = ApplyBitmask(bin_num, mask);
            // If the value is already stored, overwrite it
            auto it = memory.find(mem_address);
            if (it != memory.end())
            {
                it->second = std::stoul(mem_value, nullptr, 2);
            }
            else
            {
                memory.insert({mem_address, std::stoul(mem_value, nullptr, 2)});
            }
        }
    }

    // Sum all the values in memory
    unsigned long res =
        std::accumulate(memory.begin(), memory.end(), 0UL, [](unsigned long res, const auto& mem_entry) {
            return mem_entry.second + res;
        });

    std::cout << res << std::endl;

    return EXIT_SUCCESS;
}
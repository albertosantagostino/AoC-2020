#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <sstream>
#include <vector>

typedef std::pair<std::string, std::vector<std::string>> Bag;
typedef std::map<std::string, std::vector<std::string>> Bags;

void CountBags(Bag bag, std::size_t& contained_bags, Bags& bags)
{
    for (auto sub_bag : bag.second)
    {
        contained_bags++;
        auto contained_bag = std::make_pair(sub_bag, bags[sub_bag]);
        CountBags(contained_bag, contained_bags, bags);
    }
}

int main()
{
    // Bag to search
    const std::string desired_bag{"shiny gold"};
    // Load data
    std::ifstream fp("data/day07.txt");
    std::string str;
    Bags bags;
    while (std::getline(fp, str))
    {
        std::istringstream iss(str);
        std::vector<std::string> words{std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{}};

        if (words[4] != "no")
        {
            std::stringstream bag;
            bag << words[0] << " " << words[1];
            std::vector<std::string> sub_bags;
            for (std::size_t i{4U}; i <= words.size() - 1U; i += 4U)
            {
                std::stringstream sub_bag_color;
                sub_bag_color << words[i + 1U] << " " << words[i + 2U];
                // Add the "effective" number of bags as vector elements
                for (std::size_t j{0U}; j < std::stoi(words[i]); ++j)
                {
                    sub_bags.push_back(sub_bag_color.str());
                }
            }
            bags.insert({bag.str(), sub_bags});
        }
    }

    // For each bag, iterate over it and recursively count all the contained bags
    std::size_t contained_bags{0U};
    CountBags(std::make_pair(desired_bag, bags[desired_bag]), contained_bags, bags);

    std::cout << contained_bags << std::endl;

    return EXIT_SUCCESS;
}

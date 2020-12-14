
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <sstream>
#include <vector>

typedef std::pair<std::string, std::vector<std::string>> Bag;
typedef std::map<std::string, std::vector<std::string>> Bags;

bool SearchBag(Bag bag, const std::string& desired_bag, Bags& bags)
{
    bool found{false};
    if (bag.first == desired_bag)
    {
        return true;
    }
    else
    {
        for (auto sub_bag : bag.second)
        {
            auto contained_bag = std::make_pair(sub_bag, bags[sub_bag]);
            found = SearchBag(contained_bag, desired_bag, bags);
            if (found)
            {
                break;
            }
        }
    }

    return found;
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
            for (std::size_t i = 4U; i <= words.size() - 1U; i += 4U)
            {
                std::stringstream sub_bag_color;
                sub_bag_color << words[i + 1U] << " " << words[i + 2U];
                sub_bags.push_back(sub_bag_color.str());
            }
            bags.insert({bag.str(), sub_bags});
        }
    }

    // For each bag, iterate over it and recursively explore all the contained bags
    std::size_t possible_colors{0U};
    std::for_each(bags.begin(), bags.end(), [&possible_colors, &bags, &desired_bag](auto& bag) {
        possible_colors += SearchBag(bag, desired_bag, bags);
    });

    std::cout << possible_colors - 1U << std::endl;

    return EXIT_SUCCESS;
}

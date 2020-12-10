
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>

// Disclaimer: I really dislike this solution. I will hopefully come back later on and rewrite it from scratch

struct Bag
{
    Bag(std::string c) : color(c) {}
    const std::string color;
    std::vector<Bag> contained_bags;
};

typedef std::vector<Bag> Bags;

void FillBag(Bag& bag, Bags bag_rules)
{
    auto it = std::find_if(
        bag_rules.begin(), bag_rules.end(), [&bag](const auto& bag_rule) { return bag_rule.color == bag.color; });

    if (it != bag_rules.end())
    {
        for (auto bag_to_add : it->contained_bags)
        {
            FillBag(bag_to_add, bag_rules);
            bag.contained_bags.push_back(bag_to_add);
        }
    }
}

bool SearchBag(const Bag bag, const std::string desired_bag)
{
    if (bag.color == desired_bag)
    {
        return true;
    }
    else
    {
        bool overall_res{false};
        std::for_each(
            bag.contained_bags.begin(), bag.contained_bags.end(), [&overall_res, desired_bag](const auto& inner_bag) {
                bool res = SearchBag(inner_bag, desired_bag);
                if (res)
                {
                    overall_res = true;
                }
            });
        return overall_res;
    }
    return false;
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
            std::stringstream curr_bag_color;
            curr_bag_color << words[0] << " " << words[1];
            Bag curr_bag(curr_bag_color.str());

            for (std::size_t i = 4U; i <= words.size() - 1U; i += 4U)
            {
                std::stringstream sub_bag_color;
                sub_bag_color << words[i + 1U] << " " << words[i + 2U];
                Bag new_bag(sub_bag_color.str());
                curr_bag.contained_bags.push_back(new_bag);
            }
            bags.push_back(curr_bag);
        }
    }

    // Fill all the bags recursively
    std::for_each(bags.begin(), bags.end(), [bags](auto& bag) { FillBag(bag, bags); });

    // Check which bags contain the desired one
    std::size_t possible_colors{0U};
    std::for_each(bags.begin(), bags.end(), [&possible_colors, desired_bag](const auto& bag) {
        possible_colors += SearchBag(bag, desired_bag);
    });

    // Remove the bag considered in the rule (match at upper level) and print the result
    std::cout << possible_colors - 1U << std::endl;

    return EXIT_SUCCESS;
}

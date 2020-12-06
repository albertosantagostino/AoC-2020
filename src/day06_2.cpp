
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <vector>

typedef std::vector<std::string> Group;
typedef std::vector<Group> Groups;

int main()
{
    // Load data
    std::ifstream fp("data/day06.txt");
    Groups groups;
    Group group;
    std::string str;
    while (std::getline(fp, str))
    {
        if (str == "")
        {
            groups.push_back(group);
            group.clear();
        }
        else
        {
            group.push_back(str);
        }
    }
    // Handle entry at the end of file
    if (group.size())
    {
        groups.push_back(group);
    }

    // Use a map to store character occurrences
    std::size_t overall_sum{0U};
    for (const auto group : groups)
    {
        std::map<char, std::size_t> answers;
        for (const auto person_answers : group)
        {
            std::for_each(person_answers.begin(), person_answers.end(), [&answers](const char c) {
                auto it = answers.find(c);
                if (it != answers.end())
                {
                    it->second++;
                }
                else
                {
                    answers.insert({c, 1U});
                }
            });
        }
        for (const auto answer : answers)
        {
            if (answer.second >= group.size())
            {
                overall_sum++;
            }
        }
    }

    std::cout << overall_sum << std::endl;

    return EXIT_SUCCESS;
}

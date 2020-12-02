#include <algorithm>
#include <fstream>
#include <iostream>
#include <regex>
#include <tuple>
#include <vector>

typedef std::tuple<std::size_t, std::size_t, unsigned char, std::string> Policy;

int main()
{
    // Load data
    std::ifstream fp("data/day02.txt");
    std::vector<Policy> policies;
    std::string str;
    while (std::getline(fp, str))
    {
        std::vector<std::string> toks;
        // Regex to match all possible delimiters
        const std::regex ws_re("\\s+|: |-");
        std::copy(std::sregex_token_iterator(str.begin(), str.end(), ws_re, -1),
                  std::sregex_token_iterator(),
                  std::back_inserter(toks));
        // Each policy is represented as a tuple (min_count, max_count, character, password)
        Policy p{std::size_t(std::stoi(toks[0])), std::size_t(std::stoi(toks[1])), toks[2][0], toks[3]};
        policies.push_back(p);
    }

    // Remove all policies that are not satisfying the condition
    policies.erase(std::remove_if(policies.begin(),
                                  policies.end(),
                                  [](Policy p) {
                                      const std::size_t occu =
                                          std::count(std::get<3>(p).begin(), std::get<3>(p).end(), std::get<2>(p));
                                      return !((occu >= std::get<0>(p)) && (occu <= std::get<1>(p)));
                                  }),
                   policies.end());

    std::cout << policies.size() << std::endl;

    return EXIT_SUCCESS;
}

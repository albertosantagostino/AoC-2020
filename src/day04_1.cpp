#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <unordered_map>
#include <vector>

typedef std::unordered_map<std::string, std::string> Passport;
typedef std::vector<Passport> PassportsBatch;

int main()
{
    // Load data
    std::ifstream fp("data/day04.txt");
    PassportsBatch passport_batch{};
    Passport passport{};
    std::string str;
    while (std::getline(fp, str))
    {
        if (str == "")
        {
            passport_batch.push_back(passport);
            passport.clear();
        }
        else
        {
            std::istringstream iss(str);
            std::vector<std::string> toks{std::istream_iterator<std::string>{iss},
                                          std::istream_iterator<std::string>{}};
            for (auto field_txt : toks)
            {
                const std::size_t sep_idx = field_txt.find_first_of(":");
                const std::string key = field_txt.substr(0U, sep_idx);
                const std::string val = field_txt.substr(sep_idx + 1U, str.size());
                passport.insert({key, val});
            }
        }
    }

    const std::vector<std::string> mandatory_fields{"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"};

    std::size_t valid_count{0U};
    std::for_each(passport_batch.begin(), passport_batch.end(), [&valid_count, mandatory_fields](Passport const& p) {
        std::size_t valid_fields{0U};
        std::for_each(mandatory_fields.begin(), mandatory_fields.end(), [&valid_fields, &p](auto const& f) {
            valid_fields += (p.find(f) != p.end());
        });
        valid_count += valid_fields / 7;
    });

    std::cout << valid_count << std::endl;

    return EXIT_SUCCESS;
}

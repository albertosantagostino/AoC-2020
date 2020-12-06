#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <regex>
#include <sstream>
#include <unordered_map>
#include <vector>

typedef std::unordered_map<std::string, std::string> Passport;
typedef std::vector<Passport> PassportsBatch;

enum class PassportField
{
    kPassportField_BirthYear,
    kPassportField_IssueYear,
    kPassportField_ExpirationYear,
    kPassportField_Height,
    kPassportField_HairColor,
    kPassportField_EyeColor,
    kPassportField_PassportId,
    kPassportField_CountryId,
    kPassportField_Invalid
};

const PassportField GetPassportFieldEnum(std::string field_key)
{
    if (field_key == "byr")
        return PassportField::kPassportField_BirthYear;
    else if (field_key == "iyr")
        return PassportField::kPassportField_IssueYear;
    else if (field_key == "eyr")
        return PassportField::kPassportField_ExpirationYear;
    else if (field_key == "hgt")
        return PassportField::kPassportField_Height;
    else if (field_key == "hcl")
        return PassportField::kPassportField_HairColor;
    else if (field_key == "ecl")
        return PassportField::kPassportField_EyeColor;
    else if (field_key == "pid")
        return PassportField::kPassportField_PassportId;
    else if (field_key == "cid")
        return PassportField::kPassportField_CountryId;
    else
        return PassportField::kPassportField_Invalid;
}

bool ValidateYear(const std::string year, const int min, const int max)
{
    return (!((year.size() != 4U) || (std::stoi(year) < min) || (std::stoi(year) > max)));
}

bool ValidateHeight(const std::string height)
{
    std::string num = height.substr(0U, height.size() - 2);
    std::string unit = height.substr(height.size() - 2, height.size());
    if (((unit == "cm") && ((std::stoi(num) >= 150) && (std::stoi(num) <= 193))) ||
        ((unit == "in") && ((std::stoi(num) >= 59) && (std::stoi(num) <= 76))))
    {
        return true;
    }
    return false;
}

bool ValidateWithRegex(const std::string str, const std::string regex_str)
{
    const std::regex re(regex_str);
    return std::regex_match(str, re);
}

int main()
{
    // Load data
    std::ifstream fp("data/day04.txt");
    PassportsBatch passport_batch;
    Passport passport;
    std::string str;
    while (std::getline(fp, str))
    {
        if (!str.size())
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
    // Iterate over all passports in the batch
    std::size_t valid_count{0U};
    std::for_each(passport_batch.begin(), passport_batch.end(), [&valid_count, mandatory_fields](Passport const& p) {
        std::size_t valid_fields{0U};
        // Iterate over all the mandatory fields to validate
        std::for_each(mandatory_fields.begin(), mandatory_fields.end(), [&valid_fields, &p](auto const& f) {
            Passport::const_iterator it = p.find(f);
            if (it != p.end())
            {
                switch (GetPassportFieldEnum(it->first))
                {
                    case PassportField::kPassportField_BirthYear:
                        valid_fields += ValidateYear(it->second, 1920, 2002);
                        break;
                    case PassportField::kPassportField_IssueYear:
                        valid_fields += ValidateYear(it->second, 2010, 2020);
                        break;
                    case PassportField::kPassportField_ExpirationYear:
                        valid_fields += ValidateYear(it->second, 2020, 2030);
                        break;
                    case PassportField::kPassportField_Height:
                        valid_fields += ValidateHeight(it->second);
                        break;
                    case PassportField::kPassportField_HairColor:
                        valid_fields += ValidateWithRegex(it->second, "#([a-f0-9]{6})");
                        break;
                    case PassportField::kPassportField_EyeColor:
                        valid_fields += ValidateWithRegex(it->second, "[(amb|blu|brn|gry|grn|hzl|oth)]{3}");
                        break;
                    case PassportField::kPassportField_PassportId:
                        valid_fields += ValidateWithRegex(it->second, "([0-9]{9})");
                        break;
                    default:
                        break;
                }
            }
        });
        valid_count += valid_fields / 7;
    });

    std::cout << valid_count << std::endl;

    return EXIT_SUCCESS;
}

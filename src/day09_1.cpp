#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

bool IsComposable(const std::size_t num, std::vector<int> subvector)
{
    std::sort(subvector.begin(), subvector.end());
    for (const auto& value : subvector)
    {
        auto it = std::find(subvector.rbegin(), subvector.rend(), num - value);
        if (it != subvector.rend())
        {
            return true;
            break;
        }
    }
    return false;
}

int main()
{
    // Load data
    std::ifstream fp("data/day09.txt");
    std::istream_iterator<int> start(fp), end;
    std::vector<int> numbers(start, end);

    // Shift the window and check if the number can be composed by the element in sub_vec
    const std::size_t preamble_size{25U};
    std::size_t i{preamble_size};
    for (i; i < numbers.size(); ++i)
    {
        std::vector<int> sub_vec(&numbers[i - preamble_size], &numbers[i]);

        if (!IsComposable(numbers[i], sub_vec))
        {
            break;
        }
    }

    std::cout << numbers[i] << std::endl;

    return EXIT_SUCCESS;
}

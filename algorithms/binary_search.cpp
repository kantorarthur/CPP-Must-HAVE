#include <vector>
#include <cstdint>
#include <iostream>
#include <optional>


std::optional<std::size_t> binary_search(const std::vector<int>& arr, uint32_t low,
                                    uint32_t high, int target)
{
    if(high > arr.size())
        return std::nullopt;
    size_t mid{};
    while(low < high)
    {
        mid = low + (high - low) / 2;
        if(arr[mid] == target)
            return mid;
        else if(arr[mid] < target)
            low = mid + 1;
        else
            high = mid;
    }
    return std::nullopt;
}

int main()
{
    std::vector<int> arr{-1, 2, 3, 4, 5, 6, 7};

    if(auto b_search = binary_search(arr, 0, arr.size(), 15) )
        std::cout << *b_search;
    else
        std::cout << "Not found";
    return 0;
}


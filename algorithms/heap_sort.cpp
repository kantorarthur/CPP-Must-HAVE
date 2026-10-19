#include <vector>
#include <iostream>
#include <algorithm>
#include <cstdint>
#include <cstddef>

void heapify(std::vector<int>& arr, std::size_t i, const std::size_t n)
{
    while(true)
    {
        if(i >= n)
            break;
        std::size_t max = i;
        std::size_t left = 2 * i + 1;
        std::size_t right = 2 * i + 2;
        if(left < n && arr[left] > arr[max])
            max = left;
        if(right < n && arr[right] > arr[max])
            max = right;
        if(i == max)
            break;
        std::swap(arr[i], arr[max]);
        i = max;
    }
}

void heap_sort(std::vector<int>& arr, const std::size_t n)
{
    if(n < 2)
        return;
    for(auto i{n / 2}; i-- > 0;)
        heapify(arr, i, n);
    for(auto i{n - 1uz}; i > 0; --i)
    {
        std::swap(arr[i], arr[0]);
        heapify(arr, 0, i);
    }
}

int main()
{
    std::vector<int> arr{-2, 3, 42 ,512, 885 ,3222, 3, 3, 2, 1, 955, 32, 23};

    heap_sort(arr, arr.size());
    for(const auto& a : arr)
        std::cout << a << " ";
    return 0;
}

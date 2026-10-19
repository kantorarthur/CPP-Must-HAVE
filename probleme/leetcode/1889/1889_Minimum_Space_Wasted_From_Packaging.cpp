#include <vector>
#include <cstdint>
#include <algorithm>

using namespace std;

class Solution {
public:
    void heapify(vector<int>& arr, int32_t i, int32_t n)
    {
        int max{};
        int left{};
        int right{};
        while(true)
        {
            if(i < 0 || i >= n)
                break;
            max = i;
            left = 2 * i + 1;
            right = 2 * i + 2;
            if(left < n && arr[left] > arr[max])
                max = left;
            if(right < n && arr[right] > arr[max])
                max = right;
            if(max == i)
                break;
            else
            {
                swap(arr[i], arr[max]);
                i = max;
            }
        }
    }
    void heap_sort(vector<int>& arr, int32_t n)
    {
        if(n < 2)
            return;
        int32_t i = n / 2 - 1;
        for(; i >= 0; --i)
            heapify(arr, i, n);
        i = n - 1;
        for(; i > 0; --i)
        {
            swap(arr[i], arr[0]);
            heapify(arr, 0, i);
        }
    }

    size_t binary_search(const vector<int>& arr, uint32_t low, uint32_t high, int val)
    {
        size_t mid{};
        while(low < high)
        {
            mid = low + (high - low) / 2;
            if(arr[mid] <= val)
                low = mid + 1;
            else
                high = mid;
        }
        return low;
    }

    int minWastedSpace(vector<int>& packages, vector<vector<int>>& boxes) {

        //We will binary search to search HOW MANY PACKAGES CAN BE COVERED BY THE CURRENT BOX
        constexpr uint64_t ret_mod{1000000007};
        sort(packages.begin(), packages.end());

        uint64_t used{};
        uint32_t covered{};
        uint64_t minn{numeric_limits<uint64_t>::max()};

        uint32_t next{};

        uint64_t sum_p{};
        for(const auto& p : packages)
            sum_p += p;
        for(auto& box : boxes)
        {
            sort(box.begin(), box.end());
            if(box[box.size() - 1] < packages[packages.size() - 1])
                continue;
            used = 0;
            covered = 0;
            for(int b : box)
            {
                next = binary_search(packages, covered, packages.size(), b);
                used += static_cast<uint64_t>(next - covered) * b;
                covered = next;
                if(covered == packages.size())
                    break;
            }
            if(covered == packages.size())
            {
                minn = min(minn, used - sum_p);
            }
        }
        if(minn == numeric_limits<uint64_t>::max())
            return -1;
        return static_cast<int>(minn % ret_mod);
    }
};

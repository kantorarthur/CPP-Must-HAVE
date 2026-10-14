#include <vector>
#include <cstdint>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> map;
        size_t n{nums.size()};
        int32_t i{0};
        for(i = 0; i < n; ++i)
        {
            int32_t second_num = target - nums[i];
            if( map.count(second_num) )
            {
                return { map[second_num], i };
            }
            map[ nums[i] ] = i;
        }
        return {};
    }
};

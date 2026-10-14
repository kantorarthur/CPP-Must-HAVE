#include <vector>
#include <cstdint>
using namespace std;

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if(nums.size() == 1)
            return 1;
        
        //We use 2 pointers: 
        //
        //1. First pointer should follow the last position of "good array"
        //2. Second pointer iterates through the entire array
        uint16_t good_array_ind{};
        for(auto i{1uz}; i < nums.size(); ++i)
        {
            if(nums[good_array_ind] != nums[i])
            {
                nums[++good_array_ind] = nums[i];
            }
            else
            {
                while( ( i + 1 < nums.size() ) && nums[i] == nums[good_array_ind] )
                    ++i;
                if(nums[i] != nums[good_array_ind])
                    nums[++good_array_ind] = nums[i];
                else
                    return good_array_ind + 1;
            }
        }
        return good_array_ind + 1;
        
    }
};

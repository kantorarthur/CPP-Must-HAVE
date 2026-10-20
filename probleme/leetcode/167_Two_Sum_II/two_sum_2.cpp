#include <vector>

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) 
    {
        int i{};
        int j = numbers.size() - 1;
        while(i >= 0 && i < numbers.size() && j >= 0 && j < numbers.size())
        {
            if(i == j)
            {
                if(numbers[i] + numbers[j] > target)
                    --j;
                else
                    ++i;
            }
            else if(numbers[i] + numbers[j] == target)
                return{min(i + 1, j + 1), max(j + 1, i + 1)};
            else if(numbers[i] + numbers[j] > target)
                --j;
            else if(numbers[i] + numbers[j] < target)
                ++i;
        }
        return {2, 2};
    }
};

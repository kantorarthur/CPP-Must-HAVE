#include <vector>

using namespace std;

class Solution {
public:
    int maxArea(vector<int>& height) {
        if(height.size() == 2)
            return min(height[0], height[1]);
        int max_sum{0};

        int i = 0;
        int j = height.size() - 1;

        while(i >= 0 && i < height.size() && i < j && j >= 0 && j > i && j < height.size())
        {
            int current = (j - i) * min(height[i], height[j]);
            if(current > max_sum)
                max_sum = current;
            if(height[i] <= height[j])
                ++i;
            else
                --j;
        }
        return max_sum;      
    }
};

#include <vector>
#include <string>
#include <cstdint>
#include <limits>

using namespace std;

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {

        string longest_prefix{};
        uint8_t least_size{numeric_limits<uint8_t>::max()};

        for(auto i{0uz}; i < strs.size(); ++i)
        {
            if(strs[i].size() < least_size)
                least_size = strs[i].size();
        }

        for(auto i{0uz}; i < least_size; ++i)
        {
            for(auto j{0uz}; j < strs.size() - 1; ++j)
            {
                if(strs[j][i] != strs[j + 1][i])
                    return longest_prefix;
            }
            longest_prefix.push_back(strs[0][i]);
        }

        return longest_prefix;

    }
};

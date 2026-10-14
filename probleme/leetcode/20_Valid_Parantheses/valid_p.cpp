#include <string>
#include <cstdint>
#include <deque>

using namespace std;

class Solution {
public:
    bool isValid(string s) {
        //We insert into the stack the opening parantheses until we find
        //An closing paranthes. If the closing paranthes doesn't match the
        //the last added openning paranthes from the stack, we return null.
        if(s.size() == 1 || s.size() % 2 == 1)
            return false;
        deque<char> stack;
        uint16_t cnt{};
        for(auto i{0uz}; i < s.size(); ++i)
        {
            if(s[i] == '(' || s[i] == '{' || s[i] == '[')
                stack.push_back(s[i]);
            else if(stack.empty())
                return false;
            else
            {
                if(stack.back() == '[' && s[i] != ']')
                    return false;
                else if(stack.back() == '{' && s[i] != '}')
                    return false;
                else if(stack.back() == '(' && s[i] != ')')
                    return false;
                stack.pop_back();
                ++cnt;
            }
        }
        if(cnt == s.size() / 2)
            return true;
        return false;
    }
};

#include <vector>
using namespace std;

void dfs(vector<vector<int>> list, int i, int destination, bool& check)
{
    for(auto j{0uz}; j < list[i].size(); ++j)
    {
        if(check == true)
            break;
        if(list[i][j] == destination)
        {
            check = true;
            break;
        }
        else
            dfs(list, list[i][j], destination, check);
    }
}

class Solution {
public:
    bool validPath(int n, vector<vector<int>>& edges, int source, int destination) {
        
        vector<vector<int>> adj_list(n);

        for(auto i{0uz}; i < edges.size(); ++i)
        {
            adj_list[edges[i][0]].push_back(edges[i][1]); 
        }

        bool check{false};
        dfs(adj_list, source, destination, check);
        return check;
    }
};

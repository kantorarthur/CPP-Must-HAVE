#include <vector>

using namespace std;

class Solution {
public:
    bool validPath(int n, vector<vector<int>>& edges, int source, int destination) {
        
        //We will use an adjaency list
        //We also have to take into consideration that is an undirected graph
        vector<vector<int>> adj(n);

        for(const auto& cur : edges)
        {
            adj[cur[0]].push_back(cur[1]);
            adj[cur[1]].push_back(cur[0]);
        }

        //Now we iterate through every connected graph with "source"
        //And check wether we do have an path to dest

        vector<bool> visited(n, false);
        vector<int> to_visit{source};

        for(auto i{0uz}; i < to_visit.size(); ++i)
        {
            int current_vert = to_visit[i];
            if(current_vert == destination)
                return true;
            for(auto& el : adj[current_vert])
            {
                if(!visited[el])
                {
                    visited[el] = true;
                    to_visit.push_back(el);
                }
            }
        }
        return false;
        //Time complexity: O(E + V) -- Because firstly we iterate through every
        //Edge to construct the adj list
        //Also takes O(V) time to construct both visited and adj lists
        //
        //And then we iterate through the connected vertex
        //
        //Memory Complexity: O(E + V) -- Because the adj list holds every
        //connected vertices of the edges
    }
};

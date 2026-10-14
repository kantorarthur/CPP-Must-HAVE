#include <vector>
#include <queue>;
using namespace std;

class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        
        //I create an adjaceny list that is basically a graph
        //
        //adjlist[prereq[1]].push_back(prerequesites[0]) - 
        //  - that means that prereq[0] depends on prereq[1] in order to finish
        //
        //while completing the adj list I also complete the in_degree of each
        //course
        //in degree means: the number of courses that needs to be done before
        //that course can be done
        //
        //after that, I check which courses dont depend on any other courses
        //I add those to the result vec and then I check which courses can be
        //also finished because those courses were finished
        //
        //at the end, if all the courses couldn't be finished I return an empty list

        vector<vector<int>> adj_list(numCourses);
        vector<int> in_degree(numCourses, 0);

        for(auto const& courses : prerequisites)
        {
            adj_list[ courses[1] ].push_back(courses[0]);
            ++in_degree[ courses[0] ];
        }
        
        queue<int> que;
        for(auto i{0uz}; i < numCourses; ++i)
        {
            if(in_degree[i] == 0)
                que.push(i);
        }

        vector<int> result_vec;
        while(!que.empty())
        {
            int16_t cur_course = que.front();
            result_vec.push_back(cur_course);
            que.pop();
            for(auto i{0uz}; i < adj_list[cur_course].size(); ++i)
            {
                --in_degree[adj_list[cur_course][i]];
                if(in_degree[adj_list[cur_course][i]] == 0)
                    que.push(adj_list[cur_course][i]);
            }
        }

        for(auto i{0uz}; i < numCourses; ++i)
        {
            if(in_degree[i] != 0)
                return {};
        }

        return result_vec;
    }
};

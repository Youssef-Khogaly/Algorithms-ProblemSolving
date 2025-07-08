#include <bits/stdc++.h>



namespace leetcode207{
    using namespace std;

// solve using detect a cycle in directed graph
class Solution {
private:
    int time{0};
public:
typedef vector<vector<int>> graph_t;

    void addDirectedEdge(graph_t& graph , int from , int to){
        graph[from].push_back(to);
    }
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        graph_t graph (numCourses);
        vector<int>startTime(numCourses,-1);
        vector<int>finishedTime(numCourses,-1);

        for(auto& edge : prerequisites){
            addDirectedEdge(graph,edge[0],edge[1]);
        }

        for(int i = 0 ; i < numCourses ; ++i)
        {
            if(graph[i].size() != 0 && startTime[i] == -1)
            {
                if(dfs(graph,i,startTime,finishedTime) == false)
                    return false;
            }
        }

        return true;
    }
    /*
        simply apply dfs to detect a cycle on directed graph
    */
    bool dfs(graph_t& graph , int curr ,vector<int>&start , vector<int>& finished)
    {
        start[curr] = (++time); // mark visited

        for(auto& neigh : graph[curr])
        {
            if(neigh == curr) // self loop
                return false;
            if(start[neigh] != -1)
            {
                if(finished[neigh] == -1)// back loop
                    return false;
                // forward edge case and cross edge case we don't care about them here

            }
            else{ // tree edge case . not visited before
                if(false == dfs(graph,neigh,start,finished)){
                    return false;
                }
            }
        } 

        finished[curr] = (++time);

        return true;
    }
};


// solved using topo sort

class Solution2 {
private:
public:
typedef vector<vector<int>> graph_t;

    void addDirectedEdge(graph_t& graph , int from , int to , vector<int>& InDegree){
        graph[from].push_back(to);
        ++InDegree[to];
        if(InDegree[from] == -1)
            InDegree[from] = 0;
    }
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        graph_t graph(numCourses);
        vector<int>InDegree(numCourses,-1); // -1 mean there this course doesnot exist
        vector<int> ans;
        ans.reserve(numCourses);
        
        for(int i = 0 ; i < numCourses ; ++i)
        {
            if(InDegree[i] == 0){
                dfs(graph,i,InDegree,ans);
            }
        }

        return (ans.size() == numCourses);
    }

    void dfs(graph_t& graph ,int curr ,vector<int>& inDegree , vector<int>& ans)
    {
        --inDegree[curr];
        ans.push_back(curr);

        for(auto & edge : graph[curr])
        {
            inDegree[edge]--;
            if(inDegree[edge] == 0)
            {
                dfs(graph,edge,inDegree,ans);
            }
        }

        return;
    }
};


class sol2{
private:
public:
typedef vector<vector<int>> graph_t;

    void addDirectedEdge(graph_t& graph , int from , int to , vector<int>& InDegree){
        graph[from].push_back(to);
        InDegree[to]++;
    }
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {

        if(prerequisites.size() == 0)
            return true;
        graph_t graph(numCourses);
        vector<int>InDegree(numCourses,0);
        vector<int> ans;
        ans.reserve(numCourses);
        for(auto& edge : prerequisites)
            addDirectedEdge(graph,edge[0], edge[1],InDegree);

        for(int i = 0 ; i < numCourses ; ++i)
        {
            if(InDegree[i] == 0){
                dfs(graph,i,InDegree,ans);
            }
        }

        return (ans.size() == numCourses);
    }

    void dfs(graph_t& graph ,int curr ,vector<int>& inDegree , vector<int>& ans)
    {
        --inDegree[curr];
        ans.push_back(curr);

        for(auto & edge : graph[curr])
        {
            inDegree[edge]--;
            if(inDegree[edge] == 0) // indegree == 0 that's mean there is no pre for this course and can take it now
            {
                dfs(graph,edge,inDegree,ans);
            }
        }

        return;
    }
};

}



namespace HW_1
{
    namespace loxicographicalOrdering{
        using namespace std;
        typedef vector<vector<int>> graph_t;

            void addDirectedEdge(graph_t& graph , int from , int to ){
                graph[from].push_back(to);
            }

        vector<int> topoSort(graph_t& graph)
        {

            // build indegree
            priority_queue<int,vector<int>,greater<int>>que; // use min heap instead of normal que to apply loxicographical ordering
            vector<int>inDegree(graph.size() , 0);
            vector<int>ans{};
            ans.reserve(graph.size());
            int curr;
            for(auto& v : graph)
            {
                for(auto& e : v)
                    ++inDegree[e];
            }
            for(int i = 0 ; i < inDegree.size() ; ++i){
                if(inDegree[i] == 0){
                    que.push(i);
                }
            }

            while(!que.empty())
            {
                curr = que.top();
                que.pop();
                ans.push_back(curr);
                for(auto& neigh : graph[curr])
                {
                    --inDegree[neigh];
                    if(inDegree[neigh] == 0)
                        que.push(neigh);
                }
            }


            return ans;
        }
    }

    using namespace std;
    namespace leetcode1136
    {
        typedef vector<vector<int>> graph_t;

            void addDirectedEdge(graph_t& graph , int from , int to ){
                graph[from].push_back(to);
            }

        int minimumSemesters(int n , vector<vector<int>>& relations){

            vector<int>inDegree(n,0);
            int countCourses = 0;
            int countSemesters = 0;
            queue<int>que{};
            int SemSize = 0;
            graph_t graph(n);
            int course;
            for(auto& edges : relations)
            {
                addDirectedEdge(graph,edges[0]-1,edges[1]-1); // -1 to convert to 0 base idices
                inDegree[edges[1]]++;
            }

            for(int i = 0 ; i < n ; ++i){
                if(inDegree[i] == 0)
                    que.push(i);
            }

            while(!que.empty()){
                SemSize = que.size();

                while(SemSize--){
                    course = que.front();
                    ++countCourses;
                    que.pop();

                    for(auto& i : graph[course]){
                        --inDegree[i];
                        if(inDegree[i] == 0){
                            que.push(i);
                        }
                    }
                }
                countSemesters++;
            }

            if(countCourses != n) // there is a cycle
                return -1;

            return countSemesters;
        }
    }
}

namespace HW_2
{

    namespace leetcode444
    {
        using namespace std;
        typedef unordered_map<int,set<int>> graph_t; // set to avoid multiple edges
        void addDirectedEdge(graph_t& graph , unordered_map<int,int>& inDegree , int from , int to)
        {
                
            auto[it , isInserted] = graph[from].insert(to);
            if(isInserted)
                ++inDegree[to];
        }
        bool sequenceReconstruction(vector<int>& org , vector<vector<int>>& seqs)
        {
            if(org.size() == 0)
                return seqs.empty(); // edge case

            // build graph and in degree
            unordered_map<int,int>indegree{};
            graph_t graph;
            queue<int>que{};
            vector<int>validSeq{};

            // fill indegree and graph
            for(int& n: org)
            {
                indegree.insert({n,0});
                graph.insert({n,{}});
            }
            // make sure every element in the seqs is in the org
            for(auto& seq : seqs)
            {
                for(int& n : seq)
                {
                    if(graph.count(n) == 0)
                        return false;
                }
            }

            for(auto& seq : seqs)
            {
                for(int i = 0 ; i+1 < (int)seq.size() ; i++)
                {
                    if(graph.count(seq[i]) == 0 || graph.count(seq[i+1]) == 0)
                        return false; // there is an element in the sequence not in the org

                    addDirectedEdge(graph,indegree,seq[i],seq[i+1]);
                }
                
            }
                

            for(auto& [v,degree] : indegree)
            {
                if(degree == 0)
                {
                    que.push(v);
                }
            }
            if(que.size() != 1) // there is multiple start that's mean there is more than 1 valid sequence
                return false;

            int curr;
            while(!que.empty())
            {
                curr = que.front();
                validSeq.push_back(curr);
                que.pop();

                for(auto& neigh : graph[curr])
                {
                    indegree[neigh]--;
                    if(indegree[neigh] == 0)
                        que.push(neigh);
                }
                if(que.size() > 1) // that's mean we can generate more than 1 valid sequence 
                    return false;
            }

            return (org.size() == validSeq.size() && validSeq == org);
        }
    }

    namespace leetcode310
    {
        using namespace std;
class Solution {

private:

    typedef vector<vector<int>> graph_t;
    int MinHeight = 100000000;
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        graph_t graph(n);
        vector<int>degree(n);
        vector<int>ans{};
        ans.reserve(n);
        priority_queue<pair<int,int>> que{}; // degree , root
        // build graph
        for(auto& edge : edges)
        {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
            degree[edge[0]]++;
            degree[edge[1]]++;
        }
        for(int i = 0 ; i < n ;++i)
        {
            que.push({degree[i],i});
        }
        MinHeight = getHeight(graph,que.top().second);
        ans.push_back(que.top().second);
        que.pop();

        while(!que.empty())
        {
            auto [deg,root] = que.top();
            que.pop();

            int h = getHeight(graph,root);
            if(h == MinHeight)
            {
                ans.push_back(root);
            }else
                break;

        }
        return ans;
    }
    int getHeight(graph_t& graph , int curr ,int pr = -1)
    {

        int h = 0;

        for(auto& n : graph[curr])
        {
            if(n != pr)
            {
                h = std::max(1+getHeight(graph,n,curr),h);
            }
        }
        return h; // parent height;
    }
};
    }


    namespace leetcode329
    {

        using namespace std;
 class SolutionDFS_DP {
        private:
            int rd[4] = {-1,1,0,0};
            int cd[4] = {0,0,-1,1};
            int ans{};
        public:
            int longestIncreasingPath(vector<vector<int>>& matrix) {
                
                vector<vector<int>> vis(matrix.size() , vector<int>(matrix[0].size() , 0));
                for(int i = 0 ; i < matrix.size() ; ++i)
                {
                    for(int j = 0 ; j < matrix[0].size(); ++j)
                    {
                        if(vis[i][j] == 0)
                            ans = std::max(ans,dfs(matrix,i,j,vis));
                    }
                }

                return ans;
            }
            int dfs(vector<vector<int>>& mat , int r , int c , vector<vector<int>>& vis)
            {
                if(vis[r][c] != 0)
                    return vis[r][c]; // result calculated before
                int length = 1;
                int nc;
                int nr;
                for(int i = 0 ; i < 4 ; ++i)
                {
                    nr = r + rd[i];
                    nc = c + cd[i];
                    if(nr > -1 && nc > -1 && nr < mat.size() && nc < mat[0].size() && mat[nr][nc] > mat[r][c])
                    {
                        length = std::max(length , 1+dfs(mat,nr,nc,vis));
                    }
                }
                vis[r][c] = length;
                return length;
            }
        };
    
        
    // topo sort
    class Solution
    {
        private:
            int rd[4] = {-1,1,0,0};
            int cd[4] = {0,0,-1,1};
            int ROWS;
            int COLS;
            pair<int,vector<pair<int,int>>> inDegree[201][201]{};
        public:

        bool isValidRange(int r , int c)
        {
            return (r> -1 && c > -1 && r < ROWS && c < COLS);
        }
        pair<int,vector<pair<int,int>>> getDegreeAndNeighbours(vector<vector<int>>& mat , int r , int c)
        {
            int nr , nc;
            int degree = 0;
            vector<pair<int,int>> neigh{};
                    for(int i = 0 ; i < 4 ; ++i)
                    {
                        nr = r + rd[i];
                        nc = c + cd[i];
                        if(isValidRange(nr,nc) )
                        {
                            if(mat[r][c] > mat[nr][nc]) // incoming edge
                                degree++;
                            else if (mat[r][c] < mat[nr][nc]) // outgoing edge
                                neigh.push_back({nr,nc});
                        } 
                    }

            return {degree,neigh};
        }
        int longestIncreasingPath(vector<vector<int>>& mat) {
            
            ROWS = mat.size();
            COLS = mat[0].size();
            int nr , nc;
            queue<pair<int,int>> que{};
            int LevelSize = 0;
            int CurrLevel = 0;
            for(int r = 0 ; r < ROWS ; ++r)
            {
                for(int c = 0 ; c < COLS ; ++c)
                {
                    inDegree[r][c] = getDegreeAndNeighbours(mat,r,c);
                    if(inDegree[r][c].first == 0) // start
                        que.push({r,c});
                }
            }

            while(!que.empty())
            {
                LevelSize = que.size();

                while(LevelSize--)
                {
                    auto[r,c] = que.front();
                    que.pop();
                    for(auto& n : inDegree[r][c].second)
                    {
                        inDegree[n.first][n.second].first--;
                        if( inDegree[n.first][n.second].first == 0)
                        {
                            que.push({n.first,n.second});
                        }
                    }
                }
                ++CurrLevel;
            }


            return CurrLevel;
          }
    };
    }
}

namespace HW_3
{
    namespace leetcode2050
    {
        using namespace std;
                class Solution {
        private:
        typedef vector<vector<int>> graph_t;
        void addDirectedEdge(graph_t& graph , int from , int to)
        {
            graph[--from].push_back(--to);
        }
        public:
            int minimumTime(int n, vector<vector<int>>& relations, vector<int>& time) {
                
                //build graph
                graph_t graph(n);
                vector<int>InDegree(n);
                vector<int>MinTime(n,0);
                int ans{0};
                int CurrentLevelTime{};
                queue<int>que{};
                int LevelSize{};
                int curr;
                for(auto& edge : relations)
                {
                    addDirectedEdge(graph,edge[0],edge[1]);
                    ++InDegree[edge[1]-1];
                }
                for(int i = 0 ; i < n ; ++i)
                {
                    if(InDegree[i] == 0)
                    {
                        que.push(i);
                        MinTime[i] = time[i];
                    }
                }

                while(!que.empty())
                {
                    CurrentLevelTime = 0;
                    LevelSize = que.size();
                    while(LevelSize--)
                    {
                        curr = que.front();
                        que.pop();

                        for(auto & neigh : graph[curr])
                        {
                            /*
                                min time required is the max of the prev course time + the neightbour time
                            */
                            MinTime[neigh] = std::max(MinTime[neigh] , MinTime[curr]+time[neigh]);
                            --InDegree[neigh];
                            if(InDegree[neigh] == 0)
                            {
                                que.push(neigh);
                            }
                        }
                    }

                }

                return *max_element(begin(MinTime) ,end(MinTime));
            }
        };
    }

    namespace leetcode1857
    {
        using namespace std;
        class Solution {
        public:
            typedef vector<vector<int>> graph_t;
            void addDirectedEdge(graph_t& graph , int from , int to)
            {
                graph[from].push_back(to);
            }
            int largestPathValue(string colors, vector<vector<int>>& edges) {
                
                int  n = colors.size();
                graph_t graph(n);
                /*
                    dpColor[i][j]
                    the maxCount of color j of any path end at i node
                */
                vector<vector<int>>dpColor(n,vector<int>(26,0));
                vector<int>inDegree(n,0);
                queue<int>que{};
                // build graph
                for(auto& edge : edges)
                {
                    if(edge[0] == edge[1]) // self cycle early return
                        return -1;
                    addDirectedEdge(graph,edge[0],edge[1]);
                    inDegree[edge[1]]++;
                }
                for(int i = 0 ; i < n ; ++i)
                {
                    if(inDegree[i] == 0)
                    {
                        que.push(i);
                    }
                }
                int ans{0};
                int levelSize;
                int nodesCount = 0; // if all nodes are visited then there is no cycles
                while(!que.empty())
                {
                    levelSize = que.size();

                    while(levelSize--)
                    {
                        auto curr = que.front();
                        que.pop();
                        int currColor = colors[curr]-'a';
                        dpColor[curr][currColor]++;
                        ++nodesCount;
                        if(dpColor[curr][currColor] > ans)
                            ans = dpColor[curr][currColor];
                        for(auto& neigh : graph[curr])
                        {
                            // merge the parent and child colors by chosing the max
                            for(int j = 0 ; j < 26 ; ++j)
                            {
                                dpColor[neigh][j] = std::max(dpColor[neigh][j] , dpColor[curr][j]);
                            }
                            --inDegree[neigh];
                            if(inDegree[neigh] == 0)
                            {
                                que.push(neigh);
                            }
                        }
                    }
                }
                if(nodesCount < n)
                    return -1;
                return ans;
            }
        };


        
    }

    // https://leetcode.com/problems/strange-printer-ii/description/
    namespace leetcode1591
    {
        // to do later
    }
}


namespace leetcode210
{
    using namespace std;
class Solution {

private:

    vector<int>ans{};
    int visited[2000]{};
public:
            typedef vector<vector<int>> graph_t;
            void addDirectedEdge(graph_t& graph , int from , int to)
            {
                graph[from].push_back(to);
            }
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        graph_t graph(numCourses);

        ans.reserve(numCourses);
        // build graph
        for(auto& edge : prerequisites)
            addDirectedEdge(graph,edge[0],edge[1]);

        for(int i = 0 ; i < numCourses ; ++i)
        {
            if(visited[i] == 0)
            {
                if(dfs(graph,i))
                    return {}; // there is a cycle no valid answer
            }
                
                
        }
        return ans;
    }

    // return true if detect cycle
    bool dfs(graph_t& graph, int curr)
    {
        visited[curr] = 1;

        for(auto& n : graph[curr])
        {
            if(visited[n] == 0)
            {
                if(dfs(graph,n))
                    return true; // detect cycle
            }
            else if (visited[n] == 1)
                return true; // detect cycle
            
        }
        visited[curr]=2;
        ans.push_back(curr);

        return false;
    }
};
}
int main()
{

}
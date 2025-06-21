#include<bits/stdc++.h>





    using namespace std;
    typedef vector<vector<int>> graph_t;


    void add_DirectedEdge(graph_t& graph , int from , int to)
    {
        graph[from].push_back(to);
    }
    void add_UnDirecctedEdge(graph_t& graph , int from , int to)
    {
        add_DirectedEdge(graph,from,to);
        add_DirectedEdge(graph,to,from);
    }
    vector<int> bfs(graph_t& graph  , int start)
    {
        queue<int>nodes;
        vector<int>len(graph.size() , -1);
        nodes.push(start);
        len[start] = 0;
        int level = 1;
        while(!nodes.empty()){
            // push neighbours
            int currLevelNodes = nodes.size();
            while(currLevelNodes--)
            {
                int curr = nodes.front();
                nodes.pop();
                
                for(auto& neighbour : graph[curr]){
                    if(len[neighbour] == -1){
                        nodes.push(neighbour);
                        len[neighbour] = level;
                    }
                }
            }
            ++level;
        }
        return len;
    }

    vector<int>bfs_2(graph_t& graph , int curr) // return shortest path from start to all nodes
    {
        queue<int>nodes;
        vector<int>parents(graph.size() , -1); // parents[curr] = the parent node of curr
        nodes.push(curr);
        parents[curr] = -1;
        int currLevelSize;
        while(!nodes.empty()){
            currLevelSize = nodes.size();
            while(currLevelSize--){
                curr = nodes.front();
                nodes.pop();
                
                for(auto& neigh : graph[curr]){
                    if(parents[neigh] == -1) // not visited before
                    {
                        parents[neigh] = curr;
                        nodes.push(neigh);
                    }
                }
            }
        }
        return parents;
    }
    /*
        print shortest path from start to curr node if exists
    */
    void printPaths(vector<int>& parents,int curr_node)
    {
        if(-1 == parents[curr_node])
            return;

        printPaths(parents,parents[curr_node]);
        cout << curr_node<< " ";
        return;
    }

    namespace leetcode261
    {

        bool has_cycle(graph_t& graph)
        {
            vector<bool>visited(graph.size(),false);
            queue<pair<int,int>>nodes; // node,parent

            for(int start = 0 ; start < graph.size() ; ++start)
            {
                if(graph[start].size() == 0 || visited[start] == true)
                    continue;
                nodes.push({start , -1});
                visited[start]=true;
                while(!nodes.empty())
                {

                    auto [curr,parent] = nodes.front();
                    nodes.pop();
                    for(auto& neigh : graph[curr])
                    {
                        if(neigh == parent) // fake cycle
                            continue;
                        if(visited[neigh] == true) // if there is 2 paths to the same node and neighbour is not the parent 
                        {
                            return true;
                        }
                        nodes.push({neigh,curr});
                        visited[neigh] = true;
                    }
                }
            }

            return false;
        }
        void buildGraph(graph_t& graph , vector<vector<int>>&edges)
        {
            for(auto& edge : edges){
                add_UnDirecctedEdge(graph,edge[0],edge[1]);
            }
        }
        bool bfs(graph_t& graph);
        bool validTree(int nodes , vector<vector<int>>& edges){
            if(edges.size() != nodes-1)
                return false; // tree must have nodes-1 edges 
            graph_t graph(nodes);
            buildGraph(graph,edges);


            return !has_cycle(graph);
        }



        void main_1()
        {
            int testCases;
            int n;
            int edgesSize;
            int from ,to;
            cin >> testCases;
            while(testCases--)
            {
                
                cin >> n;
                cin >> edgesSize;
                vector<vector<int>>edges{};
                while(edgesSize--)
                {
                    cin >> from >> to;
                    edges.push_back({from,to});
                }
                cout << validTree(n,edges) << endl;
            }
        }
    }



namespace leetcode1730
{
    int getFood(vector<vector<char>>& mat)
    {
        
        int r , c;
        // directions array
        int rd[4] = {-1,1,0,0}; // up , down , left , right
        int cd[4] = {0,0,-1,1};
        // get your location 
        for(int i = 0 ; i < mat.size() ; ++i)
        {
            for(int j = 0 ; j < mat[i].size() ; ++j)
            {
                if(mat[i][j] == '*')
                {
                    r = i;
                    c = j;
                }
            }
        }
        queue<pair<int,int>>nodes;
        int level = 1;
        nodes.push({r,c});
        mat[r][c]= 'X'; // use matrix it self to mark visited
        int nr , nc;
        int LevelSize;
        // bfs
        while(!nodes.empty())
        {

            LevelSize = nodes.size();
            while(LevelSize--)
            {
                r = nodes.front().first;
                c = nodes.front().second;
                nodes.pop();
                for(int i = 0 ; i < 4 ; ++i)
                {
                    nr = r + rd[i];
                    nc = c + cd[i];
                    // is valid idx and there is no obstcale
                    if(nr > -1 && nc > -1 && nr < mat.size() && nc < mat.size() && mat[nr][nc] != 'X')
                    {
                        if(mat[nr][nc] == '#')
                            return level; // level == shortest distance

                        nodes.push({nr,nc});
                        mat[nr][nc] = 'X'; // mark visited
                    }
                }                
            }

            ++level;
        }

        return -1;
    }
}



/************** HW2******************** */


namespace leetcode1306
{
class Solution {
    private:
    int SIZE;
public:
    inline bool isValidIdx(int i) const noexcept 
    {
        return (i > -1 && i < SIZE);
    }
    bool canReach(vector<int>& arr, int start) {
        
        SIZE = arr.size();
        queue<int>childs{};
        childs.push(start);
        int curr;
        int fchild;
        int schild;
        while(!childs.empty())
        {
            curr = childs.front();
            childs.pop();
            if(arr[curr] == 0)
                return true;
            fchild = curr + arr[curr];
            schild = curr - arr[curr];

            // mark current as visited
            arr[curr] = -1;
            // if fchild is valid idx and not visited
            if(isValidIdx(fchild) && arr[fchild] != -1 )
                childs.push(fchild);
            if(isValidIdx(schild) && arr[schild] != -1 )
                childs.push(schild);
        }

        return false;
    }
};
}


namespace leetcode2059
{
class Solution {
public:

/*
    o(n*v) n number of elements in nums and v number of verticies
    but since v is bounded by 0~1000 -> 1001 value
    o(1001*n)-> o(n)

    memory
    o(1001) for visited , o(1001) for queue
    so overall o(1)space
*/
    inline int minimumOperations(vector<int>& nums, int start, int goal) noexcept {
        vector<bool>visited(1001);
        queue<int>childs{};
        int currLevel = 0;
        int currLevelSize;
        int curr;
        childs.push(start);
        visited[start] = true; // mark visited;
        int temp[3];
        for(curr = childs.front() , currLevelSize = childs.size() ; !childs.empty() ; ++currLevel 
                                                                            , currLevelSize = childs.size())
        {
            while(currLevelSize--)
            {
                curr = childs.front();
                childs.pop();
                if(curr == goal)
                    return currLevel;

                for(auto& num : nums) 
                {
                    temp[0] = curr + num;
                    temp[1] = curr - num;
                    temp[2] = curr ^ num;
                    for(int i = 0 ; i < 3 ; ++i)
                    {
                        if((temp[i] < 0 || temp[i] >1000) && temp[i] == goal)
                            return currLevel+1;
                        if( temp[i] > -1 && temp[i] <1001 && visited[temp[i]] == false){
                            childs.push(temp[i]);
                            visited[temp[i]] = true;
                        }
                    }
                }
            }

        }
        return -1;
    }
};
}


namespace leetcode752
{
class Solution {
private:
    unordered_set<string>Deadends{};
    unordered_set<string>Visited{};
public:
    int openLock(vector<string>& deadends, string target) {
        for(auto& str : deadends)
            Deadends.insert(str);
        if(Deadends.count(target) || Deadends.count("0000"))
            return -1;
        queue<string>childs{};
        string curr = "0000";
        int currLevel = 0;
        int currLevelSize = 0;
        childs.push(curr);
        // bfs
        for(curr = childs.front() , currLevelSize = childs.size(); !childs.empty() ; currLevelSize = childs.size() 
                                                                                    , ++currLevel)
        {
            while(currLevelSize--)
            {
                curr = childs.front();
                childs.pop();
                Visited.insert(curr);
                if(curr == target)
                    return currLevel;
                
                for(int i = 0 ; i < 4 ; ++i)
                {
                    int n = curr[i] - '0';
                    int n1 = (n + 1)%10;
                    int n2 = (n == 0) ? 9 : n-1;
                    string str1 = curr;
                    string str2 = curr;
                    str1[i] = n1 + '0';
                    str2[i] = n2 + '0';
                    if(str1 == target || str2 == target)
                        return currLevel+1;
                    
                    if(Visited.count(str1) == 0 && Deadends.count(str1) == 0)
                    {
                        childs.push(str1);
                        Visited.insert(str1);
                    }
                    if(Visited.count(str2) == 0 && Deadends.count(str2) == 0)
                    {
                        childs.push(str2);
                        Visited.insert(str2);
                    }
                }
                
            }
        }
        return -1;
    }
};
}


namespace leetcode286
{

    struct cell{
        int row;
        int col;
        cell(int row , int col) : row(row) , col(col){}
    };

    void bfs(vector<vector<int>>& rooms , cell curr)
    {
        int rd[4] = {0,0,-1,1}; // left , right , top ,down
        int cd[4] = {-1,1,0,0};
        int nr;
        int nc;
        int ROWS = rooms.size();
        int COLS = rooms[0].size();
        queue<cell>childs;
        int currLevel = 0;
        int currLevelSize = 0;
        childs.push(curr);
        while(!childs.empty())
        {
            currLevelSize = childs.size();

            while(currLevelSize--)
            {
                curr = childs.front();
                rooms[curr.row][curr.col] = currLevel;
                childs.pop();

                for(int i = 0 ; i < 4 ; ++i)
                {
                    nr = curr.row + rd[i];
                    nc = curr.col + cd[i];
                    /*
                        if its in valid range
                        and not a wall
                        and its level from this gate is lower than its level from other gate
                        push it to the queue

                        no need to mark visited
                        since if its level from this gate is higher that its level from other gate
                        will not be added to the queue :)
                    
                    */
                    if(nr > -1 && nc > -1 &&  nr < ROWS && nc < COLS && rooms[nr][nc] != -1 && rooms[nr][nc] > currLevel+1)
                    {
                        childs.push({nr,nc});
                    }
                }

            }
            ++currLevel;
        }
    }
    void wallsAndGates(vector<vector<int>>& rooms)
    { 
        for(int r = 0 ; r < rooms.size(); ++r)
        {
            for(int c = 0 ; c < rooms[r].size() ; ++c)
            {
                if(rooms[r][c] == 0)
                {
                    /*
                        reverse thinking
                        apply bfs on gates only :)
                    */

                    bfs(rooms,cell{r,c});
                }
            }
        }
    }

    /******* move optimized version start by all gates in the queue
     * and apply bfs once
     */
    void bfs(vector<vector<int>>& rooms , queue<cell>&childs)
    {
        int rd[4] = {0,0,-1,1}; // left , right , top ,down
        int cd[4] = {-1,1,0,0};
        int nr;
        int nc;
        int ROWS = rooms.size();
        int COLS = rooms[0].size();
        cell curr{-1,-1};
        
        int currLevel = 0;
        int currLevelSize = 0;
        childs.push(curr);
        while(!childs.empty())
        {
            currLevelSize = childs.size();

            while(currLevelSize--)
            {
                curr = childs.front();
                rooms[curr.row][curr.col] = currLevel;
                childs.pop();

                for(int i = 0 ; i < 4 ; ++i)
                {
                    nr = curr.row + rd[i];
                    nc = curr.col + cd[i];
                    /*
                        if its in valid range
                        and not a wall
                        and its not an empty space that's mean its reached from other gate first
                        
                        no need to visited array
                        
                    
                    */
                    if(nr > -1 && nc > -1 &&  nr < ROWS && nc < COLS && rooms[nr][nc] != -1 && rooms[nr][nc] != INT_MAX)
                    {
                        childs.push({nr,nc});
                    }
                }

            }
            ++currLevel;
        }
    }
    void wallsAndGates2(vector<vector<int>>& rooms)
    { 
        queue<cell>childs;
        /*
            multiple starting points
            so add them all to the queue
        */
        for(int r = 0 ; r < rooms.size(); ++r)
        {
            for(int c = 0 ; c < rooms[r].size() ; ++c)
            {
                if(rooms[r][c] == 0)
                {
                    /*
                        reverse thinking
                        apply bfs on gates only :)
                    */

                    childs.push({r,c});
                }
            }
        }

        return bfs(rooms,childs);
    }
}

namespace leetcode417
{
class Solution {
    private:
    int rd[4] = {0,0,-1,1}; // left , right , top ,down
    int cd[4] = {-1,1,0,0};
    int ROWS;
    int COLS;
    struct myHash{

        size_t operator ()(const vector<int>& vec) const{
            return hash<int>()(vec[0])*31 + hash<int>()(vec[1]);
        }
    };

    struct cell{
        int row;
        int col;
        cell(int row , int col) : row(row) , col(col){}
    };
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        unordered_set<vector<int>,myHash>pacVisited;
        unordered_set<vector<int>,myHash>atlVisited;
        vector<vector<int>>res{};
        ROWS = heights.size();
        COLS = heights[0].size();
        // pacificOcean first col
        for(int r = 0 ,  c = 0; r < ROWS ; ++r)
        {
           if(pacVisited.count({r,c}) == 0){
                bfs(heights,pacVisited,{r,c});
            }         
        }
       // pacificOcean first row
        for(int c = 0  ,  r = 0; c < COLS ; ++c)
        {
           if(pacVisited.count({r,c}) == 0){
                bfs(heights,pacVisited,{r,c});
            }         
        }
        // atlantic last col
        for(int r = 0 ,  c = COLS-1; r < ROWS ; ++r)
        {
           if(atlVisited.count({r,c}) == 0){
                bfs(heights,atlVisited,{r,c});
            }         
        }
       // atlantic last row
        for(int c = 0  ,  r = ROWS-1; c < COLS ; ++c)
        {
           if(atlVisited.count({r,c}) == 0){
                bfs(heights,atlVisited,{r,c});
            }         
        }
        res.reserve(pacVisited.size());
        for(auto& v : pacVisited)
        {
            if(atlVisited.count(v) != 0)
            {
                res.push_back(v);
            }
        }
        return res;
    }
    void bfs(vector<vector<int>>& heights ,  unordered_set<vector<int>,myHash>& visited , cell curr)
    {
        queue<cell>childs{};
        childs.push(curr);
        visited.insert({curr.row,curr.col});
        int nr;
        int nc;
        while(!childs.empty())
        {
            curr = childs.front();
            childs.pop();
            for(int i = 0 ; i < 4 ; ++i)
            {
                nr = curr.row + rd[i];
                nc = curr.col + cd[i];
                if(nr > -1 && nc > -1 && nr < ROWS && nc < COLS && heights[nr][nc] >= heights[curr.row][curr.col]
                                                                                    &&visited.count({nr,nc}) == 0)
                {
                    childs.push({nr,nc});
                    visited.insert({nr,nc});
                }
            }
        }
    }
};
}


namespace leetcode1215
{

    void bfs(graph_t& graph , int low , int high , int curr , vector<int>&res)
    {
        if(curr < low || curr > high)
            return;

        queue<int>childs;
        int parent = -1;
        int front;
        childs.push(curr);

        while(!childs.empty())
        {
            front = childs.front();
            curr = front % 10; /*actuly the current is last added digit*/
            for(auto& next : graph[curr])
            {
                /*
                skip going back to the parent in undirected graph
                since we sure 100% there is no cycles
                only fake cycle to the parent
                */
                if(parent == next)
                    continue;

                int num = front*10+next; // add neighbour digit to the whole number

                if(num >= low && num <= high)
                {
                    // its always sorted so lets use binary search log(n)
                    // it consume less memory than unsorted set and log(n) still fast enough
                    auto it = std::lower_bound(begin(res),end(res),num);
                    if(it != end(res) && *it == num)
                        res.push_back(num);
                    
                    childs.push(num);
  
                }
                else
                {
                    break; // because if current number is not in rage
                           // then no need to check other neighbours they all will be bigger
                }

            }
            parent = curr;
            childs.pop();
        }
    }
    vector<int>countingSteppingNumbers(int low , int high)
    {
        vector<int>res;
        graph_t graph(10,vector<int>{});
        /*
            all singel digit numbers are stepping
        */
        if(low <= 9)
        {
            for(int i = low ; i < 10 ; ++i)
            {
                res.push_back(i);
            }
        }
        /*
            build undireted graph
            between digits

            0 - 1 - 2 - 3 -4 -5 -6 -7 -8 -9

            we can skip building the graph btw
            since every digit can go +1 or -1 only
            it will save memory
        */
        for(int i = 0 ; i < 10 ; ++i)
        {
            if(i+1 < 10)
                add_UnDirecctedEdge(graph,i,i+1);
            if(i-1 > -1)
                add_UnDirecctedEdge(graph,i,i-1);
        }

        /*
            o(9xV+E) , V= 10 , E = 9 always
            o(9x V+V-1)
            o(V) overall
        */
        for(int i = 1 ; i < 10 ; ++i)
        {
            bfs(graph,low,high,i,res);
        }

        return res;
    }


    void main_3()
    {
        auto res = countingSteppingNumbers( 0 ,  100);

        cout <<"[";
        for(auto num : res)
            cout << num <<",";
        cout <<"]";
    }
}


namespace leetcode1129
{
    class Solution {
    private:
    typedef vector<vector<pair<int,bool>>> graph_t; // red= true , false = blue
    void addUnDirectedEdge(graph_t& graph , int from , int to , bool isRedColor)
    {
            graph[from].push_back({to,isRedColor});
    }
    inline void markVisitedColor(vector<uint8_t>& visited , int node , uint8_t color)
    {
        visited[node] |= (1<<color);
    }
    inline bool isVisitedWithColor(vector<uint8_t>& visited,int node , uint8_t color)
    {
        return (visited[node] & (1<<color)) != 0;
    }
    public:
        vector<int> shortestAlternatingPaths(int n, vector<vector<int>>& redEdges, vector<vector<int>>& blueEdges) {
            
            graph_t graph(n);
            vector<int>ans(n,-1);
            vector<uint8_t>visited(n,0);
            for(auto& redEdge : redEdges)
            {
                addUnDirectedEdge(graph,redEdge[0],redEdge[1],true);
            }
            for(auto& blueEdge : blueEdges)
            {
                addUnDirectedEdge(graph,blueEdge[0],blueEdge[1],false);
            }

            bfs(graph,visited,ans);

            return ans;
        }

        void bfs(graph_t& graph , vector<uint8_t>&visited ,vector<int>&ans)
        {
            queue<pair<int,uint8_t>>que{};
            int parentColor = -1;
            int LevelSize = -1;
            pair<int,uint8_t> curr; // node idx , parentColor
            int CurrLevel = 1;
            ans[0] = 0;
            for(auto& edge : graph[0])
            {
                if(!isVisitedWithColor(visited,edge.first,edge.second))
                {
                    que.push({edge.first,edge.second});
                    // mark this node as visited with this color
                    markVisitedColor(visited,edge.first,edge.second);
                }
            }
                
            while(!que.empty())
            {
                LevelSize = que.size();
                while(LevelSize--)
                {
                    curr = que.front();
                    parentColor = (int)curr.second;
                    que.pop();

                    for(auto& edge : graph[curr.first])
                    {
                        if((edge.second != parentColor && !isVisitedWithColor(visited,edge.first,edge.second)))
                        {
                            que.push({edge.first,edge.second});
                            markVisitedColor(visited,edge.first,edge.second);
                        }
                    }
                    if(ans[curr.first] == -1)
                        ans[curr.first] = CurrLevel;
                }
                ++CurrLevel;
            }
        }
    };
}

namespace leetcode365
{
    class Solution {

    private:
        
        int CAP1;
        int CAP2;
        inline void process(int x , int y , pair<int,int> res[6]) noexcept
        {
            // fill first
            res[0].first = CAP1;
            res[0].second = y;

            // fill second
            res[1].second = CAP2;
            res[1].first = x;

            // empty first
            res[2].first = 0;
            res[2].second = y;

            // empty second
            res[3].first = x;
            res[3].second = 0;

            /*
                CAP1 = 6 , CAP2 = 7
                x = 2   y = 5

                CAP2 - y = 2 >= x? yes
                x = 0

                y = 5 + (2-0) = 7

            */
            // pour from first to second
            res[4].first = (CAP2 - y  >= x) ? 0 : x-(CAP2 - y);
            res[4].second = y + (x-res[4].first);
            /*
                CAP1 = 6 , CAP2 = 7
                x = 2   y = 5

                CAP1 - x = 6-2 = 4 >= x ?no 
                y = 5 - 4 = 1

                x = 2 + (5-1) = 6
                res
                x = 6 , y = 1

            */
            // pour from second to first
            res[5].second = (CAP1 - x >= y) ? 0 : y - (CAP1-x);
            res[5].first = x + (y-res[5].second);

        }
    public:

        // its not required to hash the two idicies just to pass the leetcode timelimit
        static inline int hash(int x , int y) noexcept 
        {
            return (x + y*31)%1001;
        }
        bool canMeasureWater(int cap1, int cap2, int target) noexcept {
            if(cap1+cap2 < target)
                return false;
            else if (cap1+cap2 == target)
                return true;
            
            CAP1 = cap1;
            CAP2 = cap2;
            queue<pair<int,int>> que{};
            set<int>visited{}; // use set because the the range is too big
            int x{};
            int y{};
            que.push({0,0});
            visited.insert(hash(0,0));
            pair<int,int> processResult[6];
            int hashTemp;
            while(!que.empty())
            {
                x = que.front().first;
                y = que.front().second;
                que.pop();
                process(x,y,processResult);

                for(auto&[nx,ny] : processResult)
                {
                    if(nx + ny == target)
                        return true;
                    hashTemp = hash(nx,ny);
                    if(visited.count(hashTemp) == 0)
                    {
                        que.push({nx,ny});
                        visited.insert(hashTemp);
                    }
                }
            }

            return false;
        }
    };
}


namespace leetcode773
{
class Solution {

    private:
    inline const static int rd[4] = {-1,1,0,0};
    inline const static int cd[4] = {0,0,-1,1};
public:
    /*hashing for the visited set*/
    struct VectorHash {
        size_t operator()(const std::vector<int>& v) const {
            size_t hash = v.size();
            for (auto& i : v)
                hash ^= std::hash<int>{}(i) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
            return hash;
        }
    };

    struct NestedVectorHash {
        size_t operator()(const std::vector<std::vector<int>>& vv) const {
            size_t hash = vv.size();
            VectorHash vector_hash;
            for (const auto& v : vv)
                hash ^= vector_hash(v) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
            return hash;
        }
    };
    bool isAns(vector<vector<int>>& curr)
    {

        int c = 1;
        int i;
        int j;
        for( i = 0 ; i < curr.size() ; ++i)
        {
            
            for( j = 0 ; j < curr[i].size() ; ++j)
            {
                if(i == 1 && j ==2 )
                    return true;
                if(curr[i][j] != c)
                    return false;
                ++c;
            }
        }

        return true;
    } 
    inline static bool isValidRange(int r , int c)  noexcept
    {
        return (r > -1 && r < 2 && c > -1 && c <3);
    }
    int slidingPuzzle(vector<vector<int>>& board) {
        if(isAns(board))
            return 0;
        unordered_set<vector<vector<int>> , NestedVectorHash> visited{};

        int r , c;
        bool b = true;
        // search for 0;
        for(int i = 0 ; i < board.size() && b ; ++i)
        {
            for(int j = 0 ; j < board[j].size() ; ++j)
            {
                if(board[i][j] == 0)
                {
                    r = i;
                    c = j;
                    b = false;
                    break;
                }
            }
        }

        queue<vector<vector<int>>> que{};
        queue<pair<int,int>>queLocation{}; // to store the location of zero
        que.push(board);
        queLocation.push({r,c});
        visited.insert(board);
        int LevelSize = -1;
        int CurrLevel = 0;
        int i;
        int nr , nc;
        while(!que.empty())
        {
            LevelSize = que.size();

            while(LevelSize--)
            {
                auto currBoard = que.front();
                auto[r,c] = queLocation.front();
                
                for(i = 0 ; i < 4 ; ++i)
                {
                    nr = r + rd[i];
                    nc = c + cd[i];
                    if(isValidRange(nr,nc))
                    {
                        swap(currBoard[r][c] , currBoard[nr][nc]);

                        if(visited.count(currBoard) == 0)
                        {
                            if(isAns(currBoard))
                                return CurrLevel+1;
                            
                            que.push(currBoard);
                            queLocation.push({nr,nc});
                            // mark visited
                            visited.insert(currBoard);
                        }
                        swap(currBoard[r][c] , currBoard[nr][nc]);
                    }
                }
                que.pop();
                queLocation.pop();
            }
            ++CurrLevel;
        }


        return -1;
    }
};





    /* better implementation  */

    class Solution2 {
    private:
    // direction of allowed swappes for every location of zero
    //012345
    inline static constexpr int directions[6][3] = {
        {1, 4, -1},      // 0: can swap with 1, 4
        {0, 3, 4},       // 1: can swap with 0, 3, 4
        {2, 5, -1},      // 2: can swap with 2, 5
        {0, 4, -1},      // 3: can swap with 0, 4
        {1, 3, 5},       // 4: can swap with 1, 3, 5
        {4,2,-1}        // 5: no swaps
    };
    inline static const string ans = "123450";
    public:
        int slidingPuzzle(vector<vector<int>>& board) const noexcept {
            // flattern the 2d board to string
            string curr;
            curr.reserve(6);
            int currZero;
            int i,j;
            for( i = 0 ; i < 2 ; ++i)
            {
                for(j = 0 ; j <3 ;++j)
                {
                    curr += (board[i][j] + '0');
                    if(board[i][j] == 0)
                        currZero = i*3+j; // flattern equation
                }
            }
            if(ans == curr)
                return 0;

            unordered_set<string>visited{};
            queue<pair<string,int>>que{};
            que.push({curr,currZero});
            int currLevel = 0;
            int CurrLevelSize = -1;
            int nidx;
            while(!que.empty())
            {

                CurrLevelSize = que.size();

                while(CurrLevelSize--)
                {
                    auto& [curr,idx] = que.front();
                    for(i = 0 ; i < 3 ; ++i)
                    {
                        nidx = directions[idx][i];
                        if(nidx == -1)
                            continue;

                        swap(curr[idx],curr[nidx]);

                        if(curr == ans)
                            return currLevel+1;

                        if(visited.count(curr) == 0)
                        {
                            visited.insert(curr); // mark visited
                            que.push({curr,nidx});
                        }
                        swap(curr[idx],curr[nidx]);
                    }
                    que.pop();
                }
                ++currLevel;
            }


            return -1;
        }   
    };


}



namespace leetcode1298
{
class Solution {
public:
    int maxCandies(vector<int>& status, vector<int>& candies, vector<vector<int>>& keys, vector<vector<int>>& containedBoxes, vector<int>& initialBoxes) {

        int ret = 0;
        queue<int>que;

        /*
            boxes that i got but i couldnot open
        */
        vector<bool>AcquiredBoxes(status.size(),false);
        for (int box : initialBoxes) {
            if(status[box] == 1)
                que.push(box);
            else
                AcquiredBoxes[box] = 1;
        }
        int currBox;
        while(!que.empty())
        {
            // queue will conatin only boxes that i have and i can open
            currBox = que.front();
            que.pop();
            ret += candies[currBox];
            for(int& k : keys[currBox])
            {
                status[k] = 1; // mark that i can open this box if i have it
                //check if i can open  prev box
                if(AcquiredBoxes[k] == 1) // check if iam already had this box before and couldnot open
                {
                    que.push(k);
                    AcquiredBoxes[k] = 0;
                }
                
            }
            // add contained boxes to the queue 
            for(int& box : containedBoxes[currBox])
            {
                // add to the queue if i can open it
                if(status[box] == 1 )
                {
                    // add to the queue
                    que.push(box);
                }
                else
                {
                    AcquiredBoxes[box] = 1; // mark acquired but i cant open
                }
            }
        }

        return ret;
    }
};
}


namespace leetcode934
{
class Solution {

private:
    inline static constexpr int rd[4] = {-1,1,0,0};
    inline static constexpr int cd[4] = {0,0,-1,1};
    int ROWS;
    int COLS;
    queue<pair<int,int>>waters;
    inline  bool validRange(int r ,int c) const noexcept 
    {
        return (r > -1 && c > -1 && r < ROWS && c < COLS);
    }
public:
    int shortestBridge(vector<vector<int>>& grid) {
        ROWS = grid.size();
        COLS = grid[0].size();
        int i , j ;
        bool firstIslandFound = false;
        for(i = 0 ; i < ROWS && !firstIslandFound ; ++i)
        {
            for(j = 0 ; j < COLS ; ++j)
            {
                if(grid[i][j] == 1)
                {
                    dfs(grid,i,j);
                    firstIslandFound = true;
                    break;
                }
            }
        }
        return bfs(grid);
    }

    void dfs(vector<vector<int>>& grid , int r , int c)
    {
        grid[r][c] = 2; // mark visited

        int i , nr , nc;
        for(i = 0 ; i < 4 ; ++i)
        {
            nr = r + rd[i];
            nc = c + cd[i];
            
            if(validRange(nr,nc) )
            {
                if(grid[nr][nc] == 1)
                    dfs(grid,nr,nc);
                else if (grid[nr][nc] == 0)
                {
                    grid[nr][nc] = -1; // mark water visited boundries of the first island
                    waters.push({nr,nc});
                }
            }
        }
    }

    int bfs(vector<vector<int>>& grid)
    {

        int levelSize;
        int currLevel = 1;

        int nr , nc, i;
        while(!waters.empty())
        {

            levelSize = waters.size();

            while(levelSize--)
            {
                auto&[r,c] = waters.front();

                for(i = 0 ; i < 4 ; ++i)
                {
                    nr = r + rd[i];
                    nc = c + cd[i];
                    
                    if(validRange(nr,nc) && grid[nr][nc] != 2 && grid[nr][nc] != -1)
                    {
                        if(grid[nr][nc] == 0)
                        {
                            grid[nr][nc] = -1;
                            waters.push({nr,nc});
                        }
                        else
                        {
                            return currLevel;
                        }
                    }
                }
                waters.pop();
            }
            ++currLevel;
        }

        return -1;
    }
};
}



namespace SPOJ_PT07Z
{
    
}
int main()
{
    leetcode1215::main_3();
}
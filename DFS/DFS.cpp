#include <bits/stdc++.h>


using namespace std;




typedef vector<vector<int>> graph_t;
void addEdge(graph_t& graph , int from , int to)
{
    ++graph[from][to];
}
void GraphPrint(const graph_t & graph)
{
    for(const auto & node : graph)
    {
        for(const auto & edge : node)
            {
                cout <<edge <<" ";
            }
        cout << endl;
    }
}


void Rechable(const graph_t& graph , int node ,unordered_set<int> &Visited , int CurrNode = -1)
{
    if(CurrNode == -1)
        CurrNode = node;
    else
        Visited.insert(CurrNode);
    for(int i = 0 ; i < graph.size() ; ++i)
    {
        if(i != node && i != CurrNode && graph[CurrNode][i] != 0 && Visited.count(i) == 0)
        {
            Rechable(graph,node,Visited,i);
        }
    }
}

namespace HW_1
{

    namespace Q1
    {
        typedef unordered_map<int,list<int>> graph_t;
        void addEdge(graph_t& graph , int from , int to)
        {
            graph[from].push_back(to);
        }
        void GraphPrint2(const graph_t & graph)
        {
            for(int i = 0 ; i < graph.size() ; ++i)
            {
                cout <<i <<": ";
                for(const auto & edge : graph.at(i))
                    {
                        cout <<edge <<" ";
                    }
                cout << endl;
            }
        }
        graph_t GenerateGraph(const vector<int>& pid , const vector<int>& ppid)
        {
            graph_t graph;


            for(int i = 0 ; i < ppid.size() ; ++i)
                addEdge(graph,ppid[i],pid[i]);

            return graph;
        }

        void RechableFrom(const graph_t& graph , int currNode , unordered_set<int>& VisitedNodes)
        {
            VisitedNodes.insert(currNode);
            for(const int& neighbour : graph.at(currNode))
            {
                if(VisitedNodes.count(neighbour) == 0)
                    RechableFrom(graph,neighbour,VisitedNodes);
            }
        }

        vector<int> killProcess(const vector<int> &pid , const vector<int>& ppid ,int kill)
        {
            auto graph = GenerateGraph(pid,ppid);
            unordered_set<int> Rechables{};    
            RechableFrom(graph,kill,Rechables); 
            vector<int>ret(Rechables.size());
            copy(begin(Rechables) , end(Rechables) , begin(ret));
            return ret; 
        }

        void main_Q1()
        {
            int kill;

            while(true)
            {
                cin >> kill;
                vector<int>ret = killProcess({2,0,1,6,3,4},{5,5,5,2,2,1},kill);

                for(int n : ret)
                    cout << n << " ";

                cout << '\n';
            }

        }
    }

    namespace Q2 // leetcode 690
    {
        class Employee {
        public:
            int id;
            int importance;
            vector<int> subordinates;
        };
        class Solution {

        public:
        // One employee has at most one direct leader and may have several subordinates.
        // no multible edges and all nodes indegree = 1 at most
            int getImportance(const vector<Employee*>& employees, int id) {
                unordered_map<int,Employee*>idMap{};
                for(const auto & e : employees)
                {
                    idMap.insert({e->id,e});
                }
                return GetSumOfNeighbour(idMap,id);
            }

            int GetSumOfNeighbour(unordered_map<int,Employee*>idMap , int currId)
            {
                Employee& curr = *idMap[currId];
                int sum = curr.importance;
                for(const int & neighbour : curr.subordinates)
                {
                    sum += GetSumOfNeighbour(idMap,neighbour);
                }
                return sum;
            }
        };
    }

    namespace Q3
    {
        typedef vector<vector<int>> graph_t;
        void addEdge(graph_t& graph , int from , int to)
        {
            graph[from].push_back(to);
        }
        // you can also build the graph and apply DFS and mark visited node
        // and every time you reeach a new node increment the count
        int countComponents(int n , const vector<vector<int>>& edges)
        {
            unordered_set<int>visited{};
            int count = 0;
            for(auto& edge : edges)
            {
                if(visited.count(edge[0]) == 0 && visited.count(edge[1]) == 0)
                {
                    ++count;
                }
                if(visited.count(edge[0]) == 0)
                    visited.insert(edge[0]);
                if(visited.count(edge[1]) == 0)
                    visited.insert(edge[1]);
            }

            return count;
        }

        void main_Q3()
        {
            cout << countComponents(5, {{0,1},{1,2},{2,3},{3,4}});
        }
    }
}
/*
int main()
{
    int nodes , edges;
    cin >> nodes >> edges;
    graph_t graph(nodes,vector<int>(nodes));
    while(edges--)
    {
        int from , to;
        cin >> from >> to;
        addEdge(graph,from,to);
    }
   GraphPrint(graph);
   cout <<"---------------------------------------\n";
   unordered_set<int> Visited{};
   int node;
   cin >> node;
   Rechable(graph,node,Visited);
   cout <<"Rechable(" << node << "):{";
   for(auto& n : Visited)
   {
        cout <<n<<",";
   }
   cout <<"}";

}
*/

namespace // leetcode733 floodfill
{
  using namespace std;
class Solution {
    private:
        int rd[4] = {1,-1,0,0}; // right , left , up , down , upright,upleft,downright,downleft
        int cd[4] = {0,0,-1,1};
        int orgColor = 0;
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
            if(image[sr][sc] == color )
                return image; // pervent infite loop
            orgColor = image[sr][sc];
            // we don't need to mark visited nodes
            // since visited node will not have  same org color
            dfs(image,sr,sc,color);
            return image;
        }

        
    
    void dfs(vector<vector<int>>& image, int sr, int sc, int color)
    {
        image[sr][sc] = color;
        int nr , nc;
        int ROWS = image.size();
        int COLS = image.at(0).size();
        for(int i = 0 ; i < 4 ; ++i)
        {
            nr = sr + rd[i];
            nc = sc + cd[i];
            if(nr > -1 && nr < ROWS && nc > -1 && nc < COLS && image[nr][nc] == orgColor)
            {
                dfs(image,nr,nc,color);
            }
        }        
    }
    
};
}

namespace HW_2
{
    // leetcode 1905
    namespace Q1
    {
        class Solution {
        private:
            // left , right , up , down
            int rd[4] = {0,0,-1,1};
            int cd[4] = {-1,1,0,0};
            int ROWS;
            int COLS;
            int count = 0;
        public:
            int countSubIslands(vector<vector<int>>& grid1, vector<vector<int>>& grid2) {
                ROWS = grid1.size();
                COLS = grid1[0].size();
                bool isSub;
                for(int i = 0 ; i < ROWS ; ++i)
                {
                    for(int j = 0 ; j < COLS ; ++j)
                    {
                        if(grid2[i][j] == 1)
                        {
                            isSub = true;
                            dfs(grid1,grid2,i,j , isSub);
                            if(isSub)
                            {
                                ++count;
                            }
                        }

                    }
                }

                return count;
            }
            inline bool isValidIdx(int r , int c)
            {
                return (r > -1 && r < ROWS && c >-1 && c<COLS);
            }
            void dfs(vector<vector<int>>& grid1, vector<vector<int>>& grid2 , int r  , int c , bool& isSub ) // o (|V|) , o(|V|)
            {
                /*
                    if grid2[r][c] == 1 & grid1[r][c] != 1
                    that's mean that current island is not sub island
                */   
                if(grid1[r][c] == 0)
                    isSub = false;
                // mark visited
                grid2[r][c] = 0;
                int nr,nc;

                for(int i = 0 ; i <4 ; ++i)
                {
                    nr = r + rd[i];
                    nc = c + cd[i];
                    if(isValidIdx(nr,nc) && grid2[nr][nc] == 1)
                        dfs(grid1,grid2,nr,nc , isSub);
                }

            }
        };
    }

    // leetcode 1034
    namespace Q2
    {
        class Solution {
        private:

        class Point
        {
            public:
            int x;
            int y;

            Point(int x = 0 , int y = 0) noexcept : x(x) , y(y){}

            bool operator == (const Point& another) const
            {
                return (x == another.x) && (y == another.y);
            } 
        };
        struct PointHash{
            size_t operator ()(const Point& p)const
            {
                return std::hash<int>()(p.x) ^ (std::hash<int>()(p.y) << 1);
            }
        };
            int orgColour;
            int rd[4] = {0,0,-1,1};
            int cd[4] = {-1,1,0,0};
            int ROWS;
            int COLS;
            unordered_set<Point,PointHash>Visited{};

        inline bool isValidIdx(int r , int c)
        {
            return (r > -1 && r < ROWS && c >-1 && c<COLS);
        }                
        public:
            vector<vector<int>> colorBorder(vector<vector<int>>& grid, int row, int col, int color) {
                ROWS = grid.size();
                COLS = grid[0].size();
                orgColour = grid[row][col];

                dfs(grid,row,col,color);

                return grid;
            }

            /*
                1 1
                1 2

            */
            void dfs(vector<vector<int>>& grid, int row, int col, int color)
            {
                Visited.insert(Point{row,col});
                int i , nc , nr;
                for(i = 0 ; i < 4 ; ++i)
                {
                    nr = row + rd[i];
                    nc = col + cd[i];

                    if(!isValidIdx(nr,nc) || (grid[nr][nc] != orgColour && Visited.count(Point{nr,nc}) == 0))
                    {
                        grid[row][col] = color;   
                    }
                    else if (isValidIdx(nr,nc) && Visited.count(Point{nr,nc}) == 0 && grid[nr][nc] == orgColour)
                    {
                        dfs(grid,nr,nc,color);
                    }
                }
            }

        };
    }

    // leetcode 1254
    namespace Q3
    {
        class Solution {

        private:

            int rd[4] = {0,0,-1,1};
            int cd[4] = {-1,1,0,0};
            int ROWS;
            int COLS;
        public:
            int closedIsland(vector<vector<int>>& grid) {
                ROWS = grid.size();
                COLS = grid[0].size();
                int r ,c;
                bool isClosed = true;
                int count = 0;
                for(r = 0 ; r< ROWS ; ++r)
                {
                    for(c = 0 ; c < COLS ; ++c)
                    {
                        if(grid[r][c] == 0)
                        {
                            isClosed =  true;
                            dfs(grid,r,c,isClosed);
                            if(isClosed)
                                ++count;
                        }
                    }
                }

                return count;
            }
            inline bool isValidIdx(int r , int c)
            {
                return (r > -1 && r < ROWS && c >-1 && c<COLS);
            }
            void dfs(vector<vector<int>>& grid , int r , int c , bool& isClosed)
            {
                //mark visited
                grid[r][c] = 1;
                int i , nr,nc;

                for(i = 0 ; i < 4 ;++i)
                {
                    nr = r + rd[i];
                    nc = c + cd[i];
                    if(false == isValidIdx(nr,nc))
                    {
                        isClosed = false;
                    }
                    else if (grid[nr][nc] == 0)
                        dfs(grid,nr,nc,isClosed);
                }
            } 
        };
    }

    // leedcode 1559
    namespace Q4
    {
class Solution {

/*
c a d
a a a
a a d
a c d
a b c




a b b
b z b
b b a
*/
private:
            int rd[4] = {0,0,-1,1};
            int cd[4] = {-1,1,0,0};
            int ROWS;
            int COLS;
            inline bool isValidIdx(int r , int c)
            {
                return (r > -1 && r < ROWS && c >-1 && c<COLS);
            }

public:
    bool containsCycle(vector<vector<char>>& grid) {
        ROWS = grid.size();
        COLS = grid[0].size();
        vector<vector<bool>> visited(ROWS , vector<bool>(COLS));
        int r ,c;

        for(r = 0 ; r < ROWS ; ++r)
        {
            for(c = 0 ; c < COLS ; ++c)
            {
                if(visited[r][c] == 0)
                {
                    if(dfs(grid,r,c,-1,-1 , visited) == true)
                        return true; // cycle detected
                    
                    // else continue looping
                }


                    
                
            }
        }

        return false;
    }

    bool dfs(vector<vector<char>>& grid , int r , int c ,int pr , int pc ,vector<vector<bool>>& visited , int length = 0)
    {
        ++length;
        // mark visited
        visited[r][c] = 1;
        int i , nc , nr;
        for(i = 0 ; i < 4 ;++i)
        {
            nr = r + rd[i];
            nc = c + cd[i];
            // apply dfs  if neighbour is same value and not visited before
            if(isValidIdx(nr,nc) && grid[nr][nc] == grid[r][c] && visited[nr][nc] == 0)
            {
                if(dfs(grid,nr,nc,r,c , visited) == true)
                    return true; // cycle detected
            }
            // if neighbour is visited and not the parent 100% its a cycle with length bigger or equal 4
            // we can't make a cycle with length < 4 without return to the parent
            else if (isValidIdx(nr,nc) && grid[nr][nc] == grid[r][c] && visited[nr][nc] == 1 && !(nr == pr && nc == pc))
                return true;
        }

        return  false;
    }
    
};
    }
}

namespace HW2
{
    // leetcode 1743
    namespace Q1
    {
        using namespace std;
class Solution {
            
        private:
        typedef unordered_map<int , vector<int>> graph_t;
            int n;
            graph_t graph{};
            int firstElementIdx = -1;
            vector<int>ans{};
        public:
            void GenerateGraph(vector<vector<int>>& adjacentPairs)
            {
                for(auto & pairs : adjacentPairs)
                {
                    add_undirectedEdge(pairs[0],pairs[1]);
                }
            }   
            void add_undirectedEdge(int from , int to)
            {
                graph[from].push_back(to);
                graph[to].push_back(from);
            }
            vector<int> restoreArray(vector<vector<int>>& adjacentPairs) { // o(n) , o(n+E), E number of edges  is n-1 so over all is o(n) memory
                n = adjacentPairs.size()+1;
                GenerateGraph(adjacentPairs);
                ans.reserve(n);

                for(const auto & r : graph)
                {
                    // the start point of the valid path
                    // must be have only 1 neighbour
                    if(r.second.size() == 1) // o(n)
                    {
                        dfs(r.first);
                        break;
                    }
                    
                }
                return ans;
            }
            void dfs(int r  , int pr = -1)
            {
                ans.push_back(r);
                
                for(const auto& next : graph[r])
                {
                    if(next == pr)
                        continue;

                    // don't need to visit all neighbours
                    // only 1 neighbour that is not the parent
                    // so we don't need to mark visited anyway
                    return dfs(next,r);
                }

            }
        };
    }

    namespace Q2
    {
class Solution {

private:

    typedef unordered_map<int,vector<int>> graph_t;
    graph_t graph;
    unordered_set<int>visited{};
    int top = -1;
public:
    void addUnDirected(int from , int to)
    {
        graph[from].push_back(to);
        graph[to].push_back(from);
    }
    string smallestStringWithSwaps(string s, vector<vector<int>>& pairs) {
        if(pairs.size() == 0)
            return s;
      vector<pair<multiset<char>, set<int>>> ccs(pairs.size());
        for(auto& pair : pairs)
            addUnDirected(pair[0],pair[1]);

        for(auto& pair : pairs)
        {
            if(visited.count(pair[0]) == 0)
            {
                ++top;
                dfs(pair[0],ccs,s);
            }
            
        }
            

        
        for(int i = 0 ; i <= top ; ++i )
        {
            auto  chars = ccs[i].first.begin();
            auto  idx = ccs[i].second.begin();

            while(chars != ccs[i].first.end())
            {
                s[*idx] = *chars;
                chars++;
                idx++;
            }
            
        }
        return s;
    }

    void dfs(int r , vector<pair<multiset<char>, set<int>>>& ccs , string& s)
    {
        visited.insert(r);
        ccs[top].first.insert(s[r]);
        ccs[top].second.insert(r);
        for(auto& neighbour : graph[r])
        {
            if(visited.count(neighbour) == 0)
            {
                dfs(neighbour , ccs,s);
            }
        }
    }
};
    }

    // leetcode 128
    namespace Q3
    {
class Solution {

private:
    typedef unordered_map<int,vector<int>> graph_t;
    
    graph_t graph{};
    unordered_set<int> visited;
public:
    int longestConsecutive(vector<int>& nums) {

        if(nums.size() <= 1)
            return nums.size();
        for(int i = 0 ; i < nums.size() ; ++i)
        {
            graph.insert({nums[i],{}});
        }
        for(auto & [key,val] : graph)
        {
            if(graph.count(key+1) != 0)
            {
                val.push_back(key+1);
            }
            if(graph.count(key-1) != 0)
            {
                val.push_back(key-1);
            }
        }
        int MaxLength = 1;
        int Length;
        int size = (int)nums.size();
        for(auto & [key,val] : graph) // o(n) we visit each element only once
        {
            // if not visited before and its a start of the chain
            // apply dfs else no need since its not the start of the chain
            if(visited.count(key) == 0 && val.size() == 1)
                Length = dfs(graph , key);

            if(Length > MaxLength)
                MaxLength = Length;


            if(MaxLength == size)
                break;
        }   

        return MaxLength;
    }
    int dfs(graph_t& graph ,int v ,int length = 0)
    {
        ++length;
        visited.insert(v);
        for(int& next : graph[v])
        {
            if(visited.count(next) == 0)
                length = dfs(graph,next,length);
        }

        return length;
    }
};
    }
}


namespace HW4
{
    namespace Q1 // leetcode785
    {
        class Solution {
        public:
            bool isBipartite(vector<vector<int>>& graph) {
                char colors[101];
                memset(colors,-1,101*sizeof(char));
                int color = 1;
                for(int i = 0 ; i < graph.size() ; ++i)
                {
                    if(colors[i] == -1)
                    {
                        if(!dfs(graph,i,!color,colors))
                            return false;
                    }
                }
                return true;
            }

            bool dfs(vector<vector<int>>& graph , int v ,int color,char* colors)
            {
                // mark color
                colors[v] = color;

                for(int& n : graph[v])
                {
                    if(colors[n] == -1)
                    {
                        if(!dfs(graph,n,!color,colors))
                            return false;
                    }
                    else if (colors[n] == colors[v])
                        return false;
                }

                return true;
            }
        };
    }


    namespace Q2{ // leetcode 1466
class Solution {
    private:
    int count = 0;
    

    struct edge{
        int to;
        bool isBuiltIn ;
    };
public:
    int minReorder(int n, vector<vector<int>>& connections) {
        vector<vector<edge>>graph(n , vector<edge>());
        vector<bool> visited(n,false);
        int from;
        int to;
        int i;
        for(i = 0 ; i < connections.size() ; ++i)
        {
            from = connections[i][0];
            to = connections[i][1];
            graph[from].push_back(edge{to,true});
            graph[to].push_back(edge{from,false});
        }
        dfs(graph , 0,visited); // o(n) , o(n) stack memory since i need to visit all nodes
        return count;
    }
    void dfs(vector<vector<edge>>&graph ,int r , vector<bool>& visited)
    {
        visited[r] = true;
        for(auto& next : graph[r])
        {
            if(visited[next.to] == false)
            {
                /*
                    if next edge is not fake
                    that's mean node goes away from zero
                    so we need to flip it
                */
                count += next.isBuiltIn;
                dfs(graph,next.to,visited);
            }
        }
    }
};
    }

    // leetcode 1631
    namespace Q3
    {
class Solution {
    private:

            // up , down , left , right
    int rd[4]{-1,1,0,0};
    int cd[4]{0,0,-1,1};
    int ROWS;
    int COLS;

    inline bool isValidIdx(int r , int c)
    {
        return (r>-1 && c > -1 && r < ROWS && c < COLS);
    }
    inline int computeAbs(vector<vector<int>>& heights , int r, int c , int nr,int nc)
    {
        return std::abs(heights[r][c] - heights[nr][nc]);
    }
    #define MAT_TO_ARR(_r , _c)     (((_r)*COLS)+(_c))
public:
    int minimumEffortPath(vector<vector<int>>& heights) {
        ROWS = heights.size();
        COLS = heights[0].size();
        vector<bool>visited(ROWS*COLS);
        int low = 0 , high = 1000001;
        int mid;
        int lowerBound = -1;
        bool isPossible;
        while(low <= high)
        {
            mid = low + (high-low)/2;
            std::fill(visited.begin(),visited.end() , 0);
            isPossible = dfs(heights,visited,mid);
            if(isPossible)
            {
                lowerBound = mid;
                high = mid-1;
            }else{
                low = mid+1;
            }
        }
        return lowerBound;
    }

    bool dfs(vector<vector<int>>& heights , vector<bool>&visited , int k , int r = 0, int c = 0)
    {
        if(r == ROWS -1 && c == COLS-1)
            return true;

        visited[MAT_TO_ARR(r,c)] = true;
        int i , nr , nc;
        for(i = 0 ; i < 4 ; ++i)
        {
            nr = r + rd[i];
            nc = c + cd[i];

            if(isValidIdx(nr,nc) && computeAbs(heights,r,c,nr,nc) <= k && visited[MAT_TO_ARR(nr,nc)] == false)
            {
                if(dfs(heights,visited,k,nr,nc))
                {
                    return true;
                }
               
            }
        }


        return false;
    }
};
    }

    //leetcode 
    namespace Q4
    {
        typedef vector<vector<int>> graph_t;

        void addUnDirected(graph_t& graph , int from , int to)
        {
            graph[from][to]++;
            graph[to][from]++;
        }
        bool dfs(graph_t& graph , vector<bool>&visited , int v , int pv = -1)
        {
            visited[v] = true;
            



            for(int i = 0 ; i < graph.size() ; ++i)
            {
                if(graph[v][i] != 0)
                {
                    if(visited[i] == true && pv != i)
                        return true;

                    if(visited[i] == false && dfs(graph,visited,i,v))
                        return true;
                }
            }

            return false;
        }
        bool hasCycle(graph_t& graph)
        {
            vector<bool>visited(graph.size());

            /*
            
            
                just apply dfs on every ccs
                and if you can revisit a node that is not the parent
                then 100% its a cycle

                usually dfs is o(V+E)
                but for undirected graph to have no cycle is must be a forest tree with V nodes and  at most V-1 edges

                but since after V-1 edges the dfs will stop
                because if there is an edge after V-1 edges it 100% a cycle  so the dfs will not continue exploring the whole tree
                so overall time is o(V + V-1)-> O(V) 

                memory is V*V for Visited tracking array
                and stack depth is o(V+V-1)-> o(V) since
            
            
            */
            for(int i = 0 ; i < (int)graph.size() ; ++i)
            {
                if(visited[i] == false)
                {
                    if(dfs(graph,visited,i)){
                        return true;
                    }
                }
            }

            return false;
        }

        void main_q4()
        {
            int testCases;

            cin >> testCases;

            while(testCases--)
            {
                int nodes , edges;
                cin >> nodes >> edges;
                graph_t graph(nodes,vector<int>(nodes));
                while(edges--)
                {
                    int from ,to;
                    cin >> from >> to;
                    addUnDirected(graph, from,to);
                }

                if(hasCycle(graph))
                {
                    cout <<"Yes"<<endl;
                }else{
                    cout << "NO" << endl;
                }
                cout <<flush;
            }
        }
    }
}

namespace DirectedGraphCycleDetection
{

    typedef vector<vector<int>> graph_t;
    int time = -1;
void addUnDirected(graph_t& graph , int from , int to)
        {
            graph[from].push_back(to);
        }
        bool dfs(graph_t& graph , vector<bool>&visited , vector<int>& started , vector<int>&finished,int v)
        {
            visited[v] = true;
            
            started[v] = ++time;


            for(auto& neighbour : graph[v])
            {
                if(visited[neighbour] == false) // not visited tree edge
                {
                    dfs(graph,visited,started,finished,neighbour);
                }
                else
                {

                    // forward edge
                    if(started[v] < started[neighbour])
                    {
                        continue; // no cycle 
                    }

                    // backedge cycle !!
                    // node is visited but didnot finished that's mean its in the active stack
                    // cycle
                    else if(finished[neighbour] == -1)
                    {
                        cout << "Cycle " << v << "->" <<neighbour<<endl;
                        continue;
                    }

                    // cross edge
                    else
                    {
                        cout << "Cross edge " << v << "->" <<neighbour<<endl;
                    }
                }
            }   


            finished[v] = ++time;

            return false;
        }
        bool hasCycle(graph_t& graph)
        {
            vector<bool>visited(graph.size());
            vector<int>started(graph.size(),-1);
            vector<int>finished(graph.size(),-1);
            for(int i = 0 ; i < (int)graph.size() ; ++i)
            {
                if(visited[i] == false)
                {
                    dfs(graph,visited,started,finished,i);
                }
            }

            return false;
        }

        void main_q4()
        {
            int testCases;

            cin >> testCases;

            while(testCases--)
            {
                int nodes , edges;
                cin >> nodes >> edges;
                graph_t graph(nodes);
                while(edges--)
                {
                    int from ,to;
                    cin >> from >> to;
                    addUnDirected(graph, from,to);
                }

                if(hasCycle(graph))
                {
                    cout <<"Yes"<<endl;
                }else{
                    cout << "NO" << endl;
                }
                cout <<flush;
            }
        }
}
int main()
{
    DirectedGraphCycleDetection::main_q4();
}

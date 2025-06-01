#include <bits/stdc++.h>


using namespace std;











/*

namespace HW_1
{

namespace Q1
{

    class edge
    {
        public:
        int to;
        int weight;
        edge(int to , int weight) : to(to) , weight(weight){

        } 

        bool operator < (edge another){
            return weight < another.weight;
        }
        bool operator > (edge another){
            return weight > another.weight;
        }
        bool operator == (edge another){
            return !((*this < another) || (*this > another));
        }
        bool operator <= (edge another){
            return (*this < another) || (*this == another);
        }
        bool operator >= (edge another){
            return (*this > another) || (*this == another);
        }
        string toString() const {
            stringstream ss;
            ss << " to "<<to << " cost is " << weight << endl; 
            return ss.str();
        }

    };


    class edges
    {
        public:
        std::set<edge> neighbours;

        edges(){

        }

        void add_edge(int to , int weight){
            neighbours.insert({to,weight});
        }
        void add_edge(edge& e){
            neighbours.insert(e);
        }
    };

typedef vector<edges> GRAPH;

void add_edge(GRAPH& graph , int from , int to , int cost){ // o(log Degree) , space o(V+Degree)
 
    graph[from].add_edge(to,cost);

}

void print_adjaceny_mat(const GRAPH& graph){

    for(int i = 0 ; i < graph.size() ;++i){ // o(V+Degree)
        cout << "from " << i << " \n";
        for(const auto& e : graph[i].neighbours){
            cout << e.toString();
        }
        cout <<"----------------------------\n";
    }
}

}

namespace Q3
{

    class edge
    {
        public:
        int to;
        int weight;
        edge(int to , int weight) : to(to) , weight(weight){

        } 

        bool operator < (edge another){
            return weight < another.weight;
        }
        bool operator > (edge another){
            return weight > another.weight;
        }
        bool operator == (edge another){
            return !((*this < another) || (*this > another));
        }
        bool operator <= (edge another){
            return (*this < another) || (*this == another);
        }
        bool operator >= (edge another){
            return (*this > another) || (*this == another);
        }
        string toString() const {
            stringstream ss;
            ss << " to "<<to << " cost is " << weight << endl; 
            return ss.str();
        }

    };


    class edges
    {
        public:
        std::deque<int> neighbours;

        edges() = default;

        void add_edge(int weight){
            neighbours.push_back(weight);
        }
    };

typedef vector<vector<edges>> GRAPH;

void add_edge(GRAPH& graph , int from , int to , int cost){ // o(1) , space o(V^2 + E)
 
    graph[from][to].add_edge(cost);

}

void print_adjaceny_mat(const GRAPH& graph){

    for(int i = 0 ; i < graph.size() ;++i){ //time o(V^2 +E)
        cout << "from " << i << " \n";
        for(int j = 0 ; j < graph[i].size() ; ++i){
            for(const auto & e : graph[i][j].neighbours){
                cout << "From " << i <<" to " << j << " weight is " << e << '\n';
            }
        }
        cout <<"----------------------------\n";
    }
}

}

}
*/

namespace HW_2
{

    
    namespace Q1
    {
        class edge
        {
            public:
            string to;
            int cost;

            edge(string to , int cost) : to (move(to)) , cost(cost){

            }
            bool operator < (const edge & another) const noexcept
            {
                return make_pair(to,cost) < make_pair(another.to,another.cost);
            }

        };
        typedef map<string,multiset<edge>> GRAPH;
        void add_edge(GRAPH& graph , string from , string to , int cost){ // time (L + logE) l length of string from , space o(L)
            graph[from].insert({to,cost});
        }

        void print_adjaceny_mat(const GRAPH& graph){

            for(auto& [from , edges] : graph){
                cout << "Flights from "<< from <<'\n';
                for(auto& e : edges){
                    cout << "\t\tto " << e.to <<" cost is " << e.cost<<'\n';
                }
                cout <<"---------------------------------------------------------\n";

            }
        }
    }

    namespace Q2
    {
        class edge
        {
            public:
            string to;
            int cost;

            edge(string to , int cost) : to (move(to)) , cost(cost){

            }
            bool operator < (const edge & another) const noexcept
            {
                return make_pair(to,cost) < make_pair(another.to,another.cost);
            }

        };
        class Cities
        {
            public:

            enum 
            {
                California,
                Florida,
                Pennsylvania,
                Texas,
                NewYork,
            };

            static int toInt(const string & city)
            {
                if(city == "California")
                    return static_cast<int>(California);
                else if (city == "Florida")
                {
                    return static_cast<int>(Florida); 
                }
                else if (city == "Pennsylvania")
                {
                    return static_cast<int>(Pennsylvania); 
                }
                else if (city == "Texas")
                {
                    return static_cast<int>(Texas); 
                }
                else if (city == "NewYork")
                {
                    return static_cast<int>(NewYork); 
                }

            }
            static string toString(int id)
            {
                switch(id)
                {
                    case static_cast<int>(California):
                        return "California";
                    case static_cast<int>(Florida):
                        return "Florida";
                    case static_cast<int>(Pennsylvania):
                        return "Pennsylvania";
                    case static_cast<int>(Texas):
                        return "Texas";
                    case static_cast<int>(NewYork):
                        return "NewYork";

                }
                return "";
            }
        };
        typedef vector<edge> edges;
        typedef vector<edges> GRAPH;

        void add_edge(GRAPH& graph , string from , string to , int cost){
            
            graph[Cities::toInt(from)].push_back({to,cost});
        }

        void print_adjaceny_mat(const GRAPH& graph){

            for(int i = 0 ; i < (int)graph.size() ; ++i)
            {
                if(graph[i].size() == 0)
                    continue;
                cout << "Flights from "<< Cities::toString(i) <<'\n';
                for(auto& e : graph[i]){
                    cout << "\t\tto " << e.to <<" cost is " << e.cost<<'\n';
                }
                cout <<"---------------------------------------------------------\n";
            }
        }
    }



    namespace Q3
    {

        typedef vector<vector<int>>GRAPH;
        GRAPH createImageGraph(int rows , int cols)
        {
            GRAPH graph(rows , vector<int>(cols));
            int count = 0;
           /* for(int i = 0 ; i < graph.size() ; ++i)
            {
                for(int j = 0 ; j < graph[i].size() ; ++j)
                {
                    graph[i][j] = count++;
                }
            }*/

            return graph;
        }

        void addEdge(GRAPH& graph , int from , int to)
        {
            graph[from][to] +=1;
        }
        void printPath(GRAPH graph , int from , int next = -1)
        {
            if(next >= (int)graph.size())
                return;
            if(next == -1)
            {
                cout << from << " ";
                next = 0;
            }
            if(graph[from][next] != 0)
            {
                cout << next << " ";
                printPath(graph,next,0);
            }
            else
            {
                printPath(graph,from,next+1);
            }
        }
        void printNeighbours(const GRAPH & graph)
        {
            int rdirection[4] = {-1 , 1 , 0 , 0};
            int cdirection[4] = {0 , 0 ,  -1 , 1};


            for(int i = 0 ; i < (int)graph.size() ; ++i)
            {
                for(int j = 0 ; j < (int)graph[i].size() ; ++j)
                {
                    cout << "Node " << graph[i][j] <<" Neighbors: ";
                    for(int k = 0 ; k < 4 ; ++k)
                    {
                        int newRow = i + rdirection[k];
                        int newCol = j + cdirection[k];

                        if(newRow >= 0 && newRow < (int)graph.size() && newCol >= 0 && newCol < (int)graph[newRow].size())
                        {
                            cout << graph[newRow][newCol] <<" ";
                        }
                    }
                    cout << "\n";
                }
            }
        }
        
    }
    namespace Q5
    {
        typedef vector<vector<int>>GRAPH;
        GRAPH createImageGraph(int rows , int cols)
        {
            GRAPH graph(rows , vector<int>(cols));
            int count = 0;
           /* for(int i = 0 ; i < graph.size() ; ++i)
            {
                for(int j = 0 ; j < graph[i].size() ; ++j)
                {
                    graph[i][j] = count++;
                }
            }*/

            return graph;
        }

        void addEdge(GRAPH& graph , int from , int to)
        {
            ++graph[from][to];
        }
        void PrintPathsOfLength_2(const GRAPH& graph)
        {
            vector<vector<int>> paths;
            for(int curr = 0 ; curr < (int)graph.size() ; ++curr)
            {
                int next = -1;
                for(int first = 0 ; first < (int)graph[curr].size() ; ++first)
                {
                    if(graph[curr][first] != 0)
                    {
                        for(int second  = 0 ; second < (int)graph[first].size() ; ++second)
                        {
                            if(graph[first][second] != 0)
                            {
                                paths.push_back({curr,first,second});
                            }
                        }
                    }
                }
            }

            // print paths
            for(auto& path : paths)
            {
                cout << path[0] << " " << path[1] << " " << path[2] << endl;
            }

        }
    }
}



namespace HW_3
{

    namespace Q1
    {
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

        /* 0 1 2 3 4 5
        0    1 1 1
        1    1   0
        2        1
        3        0
        4        1
        5        1
        
        
        */
        int GetUniversalSink(const graph_t& graph) // o(N^2)
        {
            int size = (int)graph.size();
            int i , j;
            int inDegreeCount;
            bool ZeroOutDegree = true;
            for(i = 0 ; i < size ; ++i)
            {
                ZeroOutDegree = true;
                inDegreeCount = 0;
                for(j = 0 ; j < size ; ++j)
                {
                    if(graph[i][j] != 0)
                    {
                        ZeroOutDegree = false;
                        break;
                    }
                }
                if(ZeroOutDegree)
                {
                    
                    for(j = 0 ; j < size ; ++j)
                    {
                        if(j == i)
                            continue;
                        else
                        {
                            inDegreeCount += graph[j][i];
                        }
                    }
                    if(inDegreeCount == size-1)
                        return i;
                }
            }

            return -1;
        }
        int GetUniversalSink_2(const graph_t& graph) // o(N)
        {
            int size = (int)graph.size();
            int PotenialSink = 0;
            /*
            just loop on every node
            and if node have outdegree that's mean that is not a sink
            move potentialSink pointer to the i maybe its a sink since previous node point to it
            and continue  don't start from i = 0 again becasue if previous node didn't have a outdegree to the previous i
            then its must be not the sink
            example
              0 1 2 
            0 0 0 1
            1 0 0 1
            2 0 0 0

            we start as potenialSink = 0 and i = 1
            we continue looping till potenitalSink = 0 , i = 2
            since node 0 have a outDegree then its must not be sink
            and since node 0 doesn't have outDegree to node 0, 1 then node 0,1 not the sink too
            so we set potential sink = 2 and keep check from i = 2 not from the start
            after loop finish we need to make sure that potenial sink have 0 outDegree and and inDegree From All other nodes and doesn't have a self loop
            */
            for(int i = 1 ; i < size ; ++i)
            {
                if(graph[PotenialSink][i] != 0)
                {
                    PotenialSink = i;
                }
            }
            for(int i = 0 ; i < size ; ++i)
            {
                if(i == PotenialSink)
                {
                    // self loop
                    if(graph[i][i] != 0)
                        return -1;
                    
                }
                // must have indegree from every node and 0 out degree
                else if(graph[PotenialSink][i] != 0 || graph[i][PotenialSink] == 0){
                    return -1;
                }
                    
            }

            return PotenialSink;
        }
    }
}
typedef std::pair<int,int> neighbour;
typedef vector<vector<neighbour>>GRAPH;






/*


space E+V

o(E)

o(E)

o(V+E)

o(V+E) need to traverse all nodes now to check if it connect to target node or not

now using list is better for sparse graph since it save memory

*/

void add_directed_graph(GRAPH& graph , int from , int to , int weight){

    graph[from].push_back({to,weight});
}
void add_undirected_graph(GRAPH& graph , int from , int to){
    graph.at(from).push_back({to,0});
    graph.at(to).push_back({from,0});
}
void print_adjancy_mat(const GRAPH& graph){

    for(int i = 0 ; i < graph.size() ; ++i){
        for(int j = 0 ; j < graph[i].size() ; ++j){

            cout << "From " << i <<" to " << graph[i][j].first <<" weight is "<< graph[i][j].second <<" nodes\n";
            
        }
    }
}
int main()
{
    using namespace HW_3::Q1;
    int nodes , edges;
    cin >> nodes >> edges;
    //auto graph = HW_2::Q3::createImageGraph(nodes,nodes);
    HW_3::Q1::graph_t graph(nodes,vector<int>(nodes));
    while(edges--)
    {
        int from , to;
        cin >> from >> to;
        HW_3::Q1::addEdge(graph,from,to);
    }
    cout << HW_3::Q1::GetUniversalSink_2(graph) << endl;
    HW_3::Q1::GraphPrint(graph);

}
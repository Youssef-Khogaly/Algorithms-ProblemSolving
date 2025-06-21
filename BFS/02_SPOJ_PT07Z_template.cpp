// https://leetcode.com/problems/tree-diameter/
// https://www.spoj.com/problems/PT07Z/

#include<iostream>
#include<vector>
#include<queue>
using namespace std;


typedef vector<vector<int>> GRAPH;
int result;
void add_undirected_edge(GRAPH &graph, int from, int to) {
	graph[from].push_back(to);
	graph[to].push_back(from);
}

int dfs(GRAPH& graph ,int curr ,int pr = -1)
{
	int max = 0; // largest
	int max2 = 0; // second largest
	int h;
	for(auto& neigh : graph[curr])
	{
		if(neigh == pr)
			continue;

		h = dfs(graph,neigh,curr);
		if(h > max)
		{
			max2 = max;
			max = h;
		}
		else if (h > max2)
		{
			max2 = h;
		}
	}
	// update the diamaeter with the sum of max and max2 sum
	// they represent the largest distance between two children of this node
	result = std::max(result,max+max2);

	return max+1; // parent hight
}
int treeDiam(GRAPH &adjList) {

	result = 0;
	dfs(adjList,0);

	return result;
}

int main() {
	// This 2 lines can speed the reading with cin
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int nodes;
	cin >> nodes;

	GRAPH graph(nodes + 1);

	for (int i = 0; i < nodes - 1; i++) {
		int x, y;
		cin >> x >> y;
		add_undirected_edge(graph, x - 1, y - 1);
	}
	cout << treeDiam(graph) << "\n";

	return 0;
}

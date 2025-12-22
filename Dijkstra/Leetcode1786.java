package com;

import java.util.Arrays;

public class Leetcode1786 {
    class Solution {
        private ArrayList<int[]>[] graph;
        private long[]dist;
        private final long OO = Long.MAX_VALUE;
        private PriorityQueue<int[]>queue;
        private  int N;
        private long[]countPaths;
        private final long MOD = 1000000007;
        private void init(int n , int[][] edges) {
            graph = new ArrayList[n];
            dist = new long[n];
            queue = new PriorityQueue<>(n , Comparator.comparingInt(e -> e[1]));
            for(int i = 0 ; i < n ; ++i)
                dist[i] = OO;
            for(int[] edge : edges)
            {
                int from = edge[0]-1;
                int to = edge[1]-1;
                int w = edge[2];
                if(graph[from] == null)
                    graph[from] = new ArrayList<>();
                if(graph[to] == null)
                    graph[to] = new ArrayList<>();
                graph[from].add(new int[]{to,w});
                graph[to].add(new int[]{from,w});
            }
        }
        private void dijkstra() {
            dist[N-1] = 0;
            queue.add(new int[]{N-1,0});
            int currNode;
            int currW;
            int neighNode;
            int neighW;
            while(!queue.isEmpty()) {
                int[] curr = queue.remove();
                currNode = curr[0];
                currW = curr[1];
                if(currW > dist[currNode])
                    continue;
                // try to relax neighbour with this node
                for(int[] neigh : graph[currNode]) {
                    neighW = neigh[1];
                    neighNode = neigh[0];
                    if(neighW + currW < dist[neighNode]) {
                        dist[neighNode] = neighW + currW;
                        queue.add(new int[]{neighNode,(int)(dist[neighNode])});
                    }
                }
            }
        }
        private long dfs(int node) {
            if(node == N-1) {
                return 1;
            }
            int neighNode;
            long c = 0;
            for(int[] neigh : graph[node]) {
                if(neigh == null)
                    continue;
                neighNode = neigh[0];
                if(countPaths[neighNode] != -1L && dist[node] > dist[neighNode]){
                    c  = (c + countPaths[neighNode]) % MOD;
                }
                else if(dist[node] > dist[neighNode]) {
                    c =  (c + dfs(neighNode)) % MOD;
                }
            }
            countPaths[node] = c;
            return c;
        }
        public int countRestrictedPaths(int n, int[][] edges) {
            N = n;
            init(n,edges);

            // just run dijkstra to compute the shortest path
            // from N-1 node to all nodes
            //O(E log V)
            dijkstra();
            countPaths = new long[N];

            Arrays.fill(countPaths,-1);
            // memo dfs to  count paths
            // O(E+V) with memoization
            dfs(0);
            return (int)countPaths[0];
        }
    }
}

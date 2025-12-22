package com;

import java.util.ArrayList;
import java.util.Comparator;
import java.util.PriorityQueue;

class Leetcode1976 {
    private class Edge{
        public int from;
        public int to;
        public long w;
        public Edge(int from , int to , long w){
            this.from = from;
            this.to = to;
            this.w = w;
        }
    }
    private ArrayList<ArrayList<Edge>>graph;
    private long[] shortestPath;
    private final long OO = Long.MAX_VALUE;
    private final long MOD = 1000000007;
    private void buildGraph(int[][]roads , int n)
    {
        graph = new ArrayList<>(n);
        for(int i = 0 ; i < n ;++i)
            graph.add(new ArrayList<>(n));
        for(int[] edge : roads)
        {
            graph.get(edge[0]).add(new Edge(edge[0],edge[1],edge[2]));
            graph.get(edge[1]).add(new Edge(edge[1],edge[0],edge[2]));
        }
    }
    public int countPaths(int n, int[][] roads){
        if(n == 1)
            return 1;
        buildGraph(roads,n);
        shortestPath = new long[n];
        Arrays.fill(shortestPath,OO);

        PriorityQueue<Edge> queue = new PriorityQueue<>(n , Comparator.comparingLong(a -> a.w));
        queue.add(new Edge(0,0,0));
        shortestPath[0] = 0;
        Edge curr;
        long[] ways = new long[n];
        ways[0] = 1;
        while (!queue.isEmpty())
        {
            curr = queue.remove();
            if(curr.w > shortestPath[curr.to])
                continue;
            shortestPath[curr.to] = curr.w;
            // try to relax neighbours
            for(Edge neighbour : graph.get(curr.to))
            {
                if(neighbour.w + curr.w < shortestPath[neighbour.to])
                {
                    shortestPath[neighbour.to] = curr.w + neighbour.w ;
                    // new shortest path
                    // ways = number of ways to the prev node
                    ways[neighbour.to] = ways[curr.to];
                    queue.add(new Edge(0,neighbour.to , neighbour.w + curr.w ));
                }else if(neighbour.w + curr.w == shortestPath[neighbour.to]){
                    // we found another optimal path
                    ways[neighbour.to] = ((ways[neighbour.to]+ways[curr.to])%MOD);
                }
            }
        }
        return (int)ways[n-1];
    }
}
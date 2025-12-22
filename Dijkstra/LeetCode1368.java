package com;

public class LeetCode1368 {
    class Solution {
        private class State
        {
            public int node;
            public int w;
            public State(int node , int w){
                this.node = node;
                this.w = w;
            }
        }
        private int ROWS;
        private int COLS;
        private final int[] rd = new int[]{0,0,1,-1};
        private final int[] cd = new int[]{1,-1,0,0};
        private ArrayList<ArrayList<State>> graph;
        private int dist[];
        private int toArrayIndex(int r , int c)
        {

            return (r*COLS + c);
        }
        private ArrayList<State> getNeighbours(int[][] grid , int r , int c)
        {
            ArrayList<State> ret = new ArrayList<>(4);
            int cost = 0;
            int nr ,  nc;
            for(int i = 0 ; i < 4 ; ++i)
            {
                nr = r + rd[i];
                nc = c + cd[i];
                if(nr > -1 && nc > -1 && nr < ROWS && nc < COLS)
                {
                    cost = i == grid[r][c]-1 ? 0 : 1;
                    ret.add(new State(toArrayIndex(nr,nc) , cost));
                }
            }
            return ret;
        }
        private void build_graph(int[][]grid)
        {
            graph = new ArrayList<>(ROWS*COLS);
            int r , c;
            int idx;

            for( r = 0 ; r < ROWS ; ++r)
            {
                for(c = 0 ; c < COLS ; ++c)
                {
                    idx = toArrayIndex(r,c);
                    graph.add(getNeighbours(grid,r,c));
                }
            }
        }

        private int dijkstra()
        {
            dist = new int[ROWS*COLS];
            for(int i = 0 ; i < ROWS*COLS ; ++i)
                dist[i] = Integer.MAX_VALUE;

            Deque<State> queue = new ArrayDeque<>(ROWS*COLS);
            queue.add(new State(0,0));
            State curr = null;
            while (!queue.isEmpty()) {
                curr = queue.remove();
                // old node we already found better path
                if (curr.w > dist[curr.node])
                    continue;

                // try to relax neighbours with this node
                for (State neighbour : graph.get(curr.node)) {

                    if (neighbour.w + curr.w < dist[neighbour.node]) {
                        dist[neighbour.node] = curr.w + neighbour.w;
                        State toAdd = new State(neighbour.node,curr.w + neighbour.w);
                        // explore 0 path first
                        if(toAdd.w == 0 || curr.w == 0) {
                            queue.addFirst(toAdd);
                        }
                        else
                            queue.addLast(toAdd);
                    }
                }
            }

            return dist[ROWS*COLS - 1];
        }
        public int minCost(int[][] grid) {
            ROWS = grid.length;
            COLS = grid[0].length;
            if(ROWS == 1 && COLS == 1)
                return 0;
            // build graph
            // if current node can move to its neighbour without changing arrow
            // then edge cost = 0
            // else edge cost = 1
            // we can avoid build the graph but this way its more clear
            build_graph(grid);
            // run  modified dijkstra version
            // using only queue not priority queue
            // since edges cost 0 or 1 only
            // if edge = 0 add it to the start of queue
            // if not add it in the last
            // this make it O(E+V)time
            return dijkstra();
        }
    }

}

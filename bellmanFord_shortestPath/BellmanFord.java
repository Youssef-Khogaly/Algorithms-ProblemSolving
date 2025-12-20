import java.io.File;
import java.io.FileNotFoundException;
import java.lang.reflect.Array;
import java.util.Arrays;
import java.util.Scanner;

public class BellmanFord {
    private int[][] mat = null;
    private int V;
    private int E;
    private int[][]shortestPathMat = null;
    private int[]desShortestPath = null;
    private final String inputPath = "/home/khogaly/yossef/Mastering_critical_SKILLS_in_Algorithms_using C++:Part1/Algorithms-ProblemSolving/bellmanFord_shortestPath/input.txt";
    private int src = 0;
    private final int OO = Integer.MAX_VALUE;
    private  Edge[] edges = null;
    private int[] path = null; // to save the prev node to print paths
    private  void fillInput()
    {

        try
        {
            File inputFile = new File(inputPath);
            Scanner scanner = new Scanner(inputFile);
            V = scanner.nextInt();
            E = scanner.nextInt();
            mat= new int[V][V];

            int i =  E;
            int from , to , weight;
            while(i!=0)
            {
                --i;
                from = scanner.nextInt();
                to = scanner.nextInt();
                weight = scanner.nextInt();
                mat[from][to] = weight;
            }
            for(int k = 0 ; k < V ; ++k)
            {
                for(int j = 0 ; j < V ; ++j)
                {
                    if(mat[k][j] == 0)
                        mat[k][j] = OO;

                }
            }
        } catch (FileNotFoundException e) {
            throw new RuntimeException(e);
        }
    }


    private static class Edge
    {
        public int from;
        public int to;
        public int weight;

        public Edge(int from, int to, int weight) {
            this.from = from;
            this.to = to;
            this.weight = weight;
        }
    }
    private void fillEdges()
    {
        try
        {
            File inputFile = new File(inputPath);
            Scanner scanner = new Scanner(inputFile);
            V = scanner.nextInt();
            E = scanner.nextInt();
            edges = new Edge[E];

            int i =  0;
            int from , to , weight;

            for(;i < E; ++i)
            {
                from = scanner.nextInt();
                to = scanner.nextInt();
                weight = scanner.nextInt();
                edges[i] = new Edge(from,to,weight);
            }
        } catch (FileNotFoundException e) {
            throw new RuntimeException(e);
        }
    }
    private int shortestPath(int dest , int edges){
        if(edges == 1)
            return mat[src][dest];

        if(shortestPathMat[dest][edges] != 0)
            return shortestPathMat[dest][edges];
        // try with  edges -1
        int ans = shortestPath(dest,edges-1);

        // try every indegree node of the destination
        // then get the shortest path to the prev node
        int tmp;
        for(int i = 0 ; i < V ; ++i)
        {
            if(mat[i][dest] != OO)
            {
                tmp = shortestPath(i,edges-1);
                if(tmp == OO)
                    continue;
                // get the shortest path to the prev node
                ans = Math.min(ans, tmp+ mat[i][dest]);
            }
        }
        return shortestPathMat[dest][edges] = ans;
    }
    /*
         Bellman–Ford time complexity:
            - O(V * E) using edge list or adjacency list
            - O(V^3) if implemented with an adjacency matrix

    For sparse graphs (E ≈ V), O(V * E) ≈ O(V^2)

     */
    private void tabulation()
    {
        desShortestPath = new int[V];
        // base case
        // can't find any node with 0 edges
        for(int i = 0 ; i < V ; ++i)
            desShortestPath[i] = OO;
        // only src rechable with 0 edges
        desShortestPath[src] = 0;
        int ans = 0;
        int tmp;
        for(int e = 1 ; e < V ; ++e)
        {
            for(int des = 0 ; des < V ; ++des)
            {
                // options 1
                // don't take e th edge
                ans = desShortestPath[des];
                // option 2
                // take one incoming edge
                for(int k = 0 ; k < V ; ++k) // incoming nodes
                {
                    if(mat[k][des] != OO && desShortestPath[k] != OO)
                    {
                        ans = Math.min(ans ,  desShortestPath[k]+mat[k][des]);
                    }
                }
                desShortestPath[des] = ans;
            }
        }
    }
    private void tabulation_standard_way()
    {
        desShortestPath = new int[V];
        // base case
        Arrays.fill(desShortestPath,OO);
        desShortestPath[src] = 0;// only src reachable
        boolean isChanged =true;
        // n-1 relaxation only ,
        for(int k = 0 ; k < V-1 && isChanged ; ++k)
        {
            // if there is no change we don't need more iterations
            isChanged = false;
            // for every edge try to relax with indegree node
            for(Edge edge : edges){
                // to avoid overflow
                if(desShortestPath[edge.from] == OO )
                    continue;
                if(desShortestPath[edge.from] + edge.weight < desShortestPath[edge.to])
                {
                    desShortestPath[edge.to] = desShortestPath[edge.from] + edge.weight;
                    isChanged = true;
                }

            }
        }
    }
    private void tabulation_standard_way_withPrinting_withNegativeCycleDetection()
    {
        desShortestPath = new int[V];
         path = new int[V];
        Arrays.fill(path,OO);
        // base case
        Arrays.fill(desShortestPath,OO);
        desShortestPath[src] = 0;// only src reachable
        boolean isChanged =true;
        boolean hasNegativeCycle = false;
        // n-1 relaxation only ,
        for(int k = 0 ; k < V-1 && isChanged ; ++k)
        {
            // if there is no change we don't need more iterations
            isChanged = false;
            // for every edge try to relax with indegree node
            for(Edge edge : edges){
                // to avoid overflow
                if(desShortestPath[edge.from] == OO )
                    continue;
                if(desShortestPath[edge.from] + edge.weight < desShortestPath[edge.to])
                {
                    path[edge.to] = edge.from;
                    desShortestPath[edge.to] = desShortestPath[edge.from] + edge.weight;
                    isChanged = true;
                }
            }
        }
        // can i relax even after n-1 relaxation ?
        // if yes that's mean there is a cycle
        for(Edge edge : edges)
        {
            if(desShortestPath[edge.from] == OO)
                continue;
            if(desShortestPath[edge.from] + edge.weight < desShortestPath[edge.to])
            {
                hasNegativeCycle = true;
                break;
            }

        }
        //printPath(path,5);
    }
    private void printPath(int[] path , int des)
    {
        if(des == src)
        {
            System.out.print(src);
            return;
        }
        if(path[des] == OO)
            System.out.print("There is not path from:" + src + " to:" +des);
        printPath(path,path[des]);
        System.out.print("->"+des );
    }
    public static void main(String[] args) {

        BellmanFord bellmanFord = new BellmanFord();
        bellmanFord.fillEdges();
        bellmanFord.tabulation_standard_way_withPrinting_withNegativeCycleDetection();

        for(int i = 0 ; i < bellmanFord.V ; ++i)
        {
            if(i == bellmanFord.src)
                continue;
            System.out.println("Path from " + bellmanFord.src + " to " + i);
            bellmanFord.printPath(bellmanFord.path,i);
            System.out.println();
            System.out.println("-".repeat(10));
        }

    }
    private  void printMat(int[][] mat)
    {
        for(int i = 0 ; i < mat.length ; ++i)
        {
            for(int j = 0 ; j < mat.length ; ++j)
            {
                if(mat[i][j] != OO)
                    System.out.print(mat[i][j] + " ");
                else
                    System.out.print("OO ");
            }
            System.out.println();
        }
    }

    // leetcode 743
    class Solution {

        private final int OO = Integer.MAX_VALUE; // no negative values any way and its faster
        public int networkDelayTime(int[][] times, int n, int k) {

            int nedge , to , prev;
            int ans = 0;
            int ret = Integer.MIN_VALUE;
            int from;
            int weight = 0;

            final int src = k-1;
            final int[] shortestPath = new int[n];
            // base case no nodes can get the signal
            Arrays.fill(shortestPath , OO);
            shortestPath[src] = 0; // only the src node is rechable with 0 latency

            // bellman ford
            for( nedge = 1 ; nedge < n ; ++nedge)
            {
                // iterate on edges and try to relax with the indegree node
                for(int[] edge : times)
                {
                    from = edge[0]-1;
                    to = edge[1]-1;
                    weight = edge[2];
                    if(shortestPath[from] == OO) // no path to the prev node
                        continue;

                    // try to relax with the indegree
                    if(shortestPath[to] > shortestPath[from] + weight)
                        shortestPath[to] = shortestPath[from] + weight;
                }
            }

            for(int num :shortestPath)
            {
                if(num == OO)
                    return -1;
                ret = Math.max(ret , num);
            }


            return ret;
        }
    }

}

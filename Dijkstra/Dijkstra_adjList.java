package com;

import java.io.File;
import java.io.FileNotFoundException;
import java.lang.reflect.Array;
import java.util.*;

public class Dijkstra_adjList {

    private static class State{
        public int to;
        public int weight;

        public State(int to, int weight) {
            this.to = to;
            this.weight = weight;
        }
    }
    private ArrayList<ArrayList<State>> mat;
    private boolean[] isVisited;
    private  int V;
    private  int E;
    private int src;
    private int[]shortestPathTo;
    private final String inputPath= "/home/khogaly/yossef/Mastering_critical_SKILLS_in_Algorithms_using_C++_Part1/Algorithms-ProblemSolving/Dijkstra/input.txt";
    private final int OO = Integer.MAX_VALUE;
    private void fillInput()
    {
        File inputFile;
        try{
            inputFile = new File(inputPath);
        } catch (RuntimeException e) {
            ;
            throw new RuntimeException(e);
        }

        try(Scanner scanner = new Scanner(inputFile))
        {
            src = scanner.nextInt();
            V = scanner.nextInt();
            E = scanner.nextInt();
            mat = new ArrayList<>(V);
            for(int i = 0 ; i < V ; ++i)
                     mat.add(new ArrayList<>(V));

            shortestPathTo = new int[V];
            isVisited = new boolean[V];
            int from ,  to ,  w;
            for(int i = 0 ; i < E ; ++i)
            {
                from = scanner.nextInt();
                to = scanner.nextInt();
                w = scanner.nextInt();
                System.out.println(from + "->" + to + " w=" +w);
                mat.get(from).add(new State(to,w));
            }
        } catch (RuntimeException | FileNotFoundException e) {
            throw new RuntimeException(e);
        }
    }

    private void solve()
    {
        int i;
        boolean[] isVisited = new boolean[V];
        int[]prev = new int[V];
        Arrays.fill(prev,-1);
        for(i = 0 ; i < V ; ++i )
            shortestPathTo[i] = OO;

        PriorityQueue<State>queue = new PriorityQueue<>(V , Comparator.comparingInt(a -> a.weight));
        queue.add(new State(src,0));
        State node = null;
        while (!queue.isEmpty())
        {


            node = queue.remove();
            // we already calculated the best path for this node

            // we can use dist array as visited array
            // Not >= to make sure that we discovered all neighbours
            if(node.weight > shortestPathTo[node.to])
                continue;
            // node is reach here when we have its best path
            // and we explore node once
            shortestPathTo[node.to] = node.weight;
            // try to relax neighbours with curr node
            for(State neighbour : mat.get(node.to))
            {
                if(shortestPathTo[neighbour.to] >  shortestPathTo[node.to] + neighbour.weight)
                {
                    shortestPathTo[neighbour.to] = shortestPathTo[node.to] + neighbour.weight;
                    prev[neighbour.to] = node.to;
                    queue.add(new State(neighbour.to,shortestPathTo[node.to] + neighbour.weight ));
                }
            }
        }
        System.out.println(Arrays.toString(prev));
        printPath(1,prev);
        System.out.println();
    }

    private void printPath(int target , int[] prev)
    {
        if(target == src){
            System.out.print(src);
            return;
        }
        if(prev[target] == -1)
            return;
        printPath(prev[target],prev);
        System.out.print("->"+target);

    }
    private void printAns()
    {
        System.out.println(Arrays.toString(shortestPathTo));
    }
    public static void main(String[] args) {

        Dijkstra_adjList dij = new Dijkstra_adjList();
        dij.fillInput();
        dij.solve();
        dij.printAns();
    }
}

package com;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Arrays;
import java.util.Scanner;

public class Dijkstra_adjMat {

    private  int[][] mat;
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
            throw new RuntimeException(e);
        }

        try(Scanner scanner = new Scanner(inputFile))
        {
            src = scanner.nextInt();
            V = scanner.nextInt();
            E = scanner.nextInt();
            mat = new int[V][V];
            for(int [] row : mat)
                Arrays.fill(row,-1);
            shortestPathTo = new int[V];
            isVisited = new boolean[V];
            int from ,  to ,  w;
            for(int i = 0 ; i < E ; ++i)
            {
                from = scanner.nextInt();
                to = scanner.nextInt();
                w = scanner.nextInt();
                mat[from][to] = w;
            }
        } catch (FileNotFoundException e) {
            throw new RuntimeException(e);
        }
    }

    private void solve()
    {
        Arrays.fill(shortestPathTo,OO);
        // base case shrotest path to src is 0
        // but don't mark it visited so we can explore his neighbours
        shortestPathTo[src] = 0;
        int minIdx = -1 , minVal = OO;
        int to;
        System.out.println(V);
        while (true)
        {
            minIdx = -1 ;minVal = OO;
            for(to = 0 ; to < V ; ++to)
            {
                if(!isVisited[to] && shortestPathTo[to] < minVal){
                    minVal = shortestPathTo[to];
                    minIdx = to;
                }
            }
            if(minIdx == -1)
                break;
            isVisited[minIdx] = true;
            // try to relax with selected node
            for(int j = 0 ; j < V ; ++j)
            {
                if(mat[minIdx][j] == -1)
                    continue;
                if(shortestPathTo[j] > shortestPathTo[minIdx] + mat[minIdx][j]){
                    shortestPathTo[j] = shortestPathTo[minIdx] + mat[minIdx][j];
                }
            }
        }

    }
    private void printAns()
    {
        System.out.println(Arrays.toString(shortestPathTo));
    }
    public static void main(String[] args) {

        Dijkstra_adjMat dij = new Dijkstra_adjMat();
        dij.fillInput();
        dij.solve();
        dij.printAns();
    }
}
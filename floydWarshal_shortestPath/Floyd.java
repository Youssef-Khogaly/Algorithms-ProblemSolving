import java.io.File;
import java.io.FileNotFoundException;
import java.util.Arrays;
import java.util.Map;
import java.util.Scanner;

/*
floyd warshal doesn't solve the negative cycle problem but it can detect it
because we init the diangonal with 0 so if there is a node
that can go back to it self with path less than 0 then we sure that there is a negative cycle reachable from this node
but it still can get the shortest path between 2 node if these 2 nodes not reachable to the cycle
 */
public class Floyd {

    private int[][] mat = null;
    private int V;
    private int E;
    private final int OO = Integer.MAX_VALUE;
    private int[][][] memo;
    private  void fillInput(){
        String inputFile = "/home/khogaly/yossef/Mastering_critical_SKILLS_in_Algorithms_using C++:Part1/Algorithms-ProblemSolving/floydWarshal_shortestPath/input.txt";
        try(Scanner scanner = new Scanner(new File(inputFile)))
        {
            V = scanner.nextInt();
            E = scanner.nextInt();
            mat = new int[V][V];
            for(int[] row : mat)
                Arrays.fill(row,OO);
            int i = E;
            for(;i!=0;--i){
                int from = scanner.nextInt();
                int to = scanner.nextInt();
                int weight = scanner.nextInt();
                mat[from][to] = Math.min(mat[from][to] , weight);
            }
            for( i = 0 ; i < V ; ++i)
                mat[i][i] = 0;
            memo = new int[V+1][V][V];
            for(int[][] arr : memo){
                for(int[] row : arr)
                    Arrays.fill(row,-1);
            }
        } catch (FileNotFoundException e) {
            System.out.println(e.getMessage());
            throw new RuntimeException(e);
        }
        catch (Exception e) {
            System.out.println(e.getCause().getMessage());
            throw e;
        }
    }
            private int solve(int from , int to , int k)
            {
                if(k == 0){
                    return memo[0][from][to] = mat[from][to];
                }
                if( memo[k][from][to] != -1)
                    return memo[k][from][to];

                int leave = solve(from,to , k-1); // leave the kth node
                // take the kth node as intermediate
                int intermediateNode = k-1;
                int take1 = solve(from,intermediateNode,k-1);
                int take2 = solve(intermediateNode,to,k-1);
                int take;
                if(take1 == OO || take2 == OO)
                    take = OO;
                else
                    take = take1 + take2;



                return memo[k][from][to] = Math.min(leave,take);
            }


    private void solve_tabulation_v1(){
        // here the K represent with only k nodes as intermediate
        // base case with K = 0 only direct edges are allowed
        int from ,  to;
        int[][][] memo = new int[V+1][V][V];
        for(from = 0 ; from < V ; ++from){
            for (to = 0 ; to < V ; ++to){
                memo[0][from][to] = mat[from][to];
            }
        }
        System.out.println("After relaxing with " + 0);
        print_answer(memo[0]);

        // don't forget the = . you need to try till you can use all nodes as intermediate
        for(int k = 1 ; k <= V ; ++k)
        {
            int intermediate_node = k-1;
            for(from = 0 ; from < V ; ++from){
                for (to = 0 ; to < V ; ++to){
                    if(from == to)
                        continue;
                    int leave = memo[k-1][from][to];

                    int take1 = memo[k-1][from][intermediate_node];
                    int take2 = memo[k-1][intermediate_node][to];
                    int take;
                    if(take1 == OO || take2 == OO)
                        take = OO;
                    else
                        take = take1 + take2;
                    memo[k][from][to] = Math.min(leave,take);
                }
            }
            System.out.println("After relaxing with " + k);
            print_answer(memo[k]);
        }
    }
    private void solve_tabulation_opt(){
        int from ,  to;
        int[][] memo = new int[V][V];
        for(from = 0 ; from < V ; ++from){
            for (to = 0 ; to < V ; ++to){
                memo[from][to] = mat[from][to];
            }
        }
        System.out.println("After relaxing with " + 0);
        print_answer(memo);
        // here the K represent the Kth node as intermediate node
        // and then apply pick or leave pattern
        for(int k = 0 ; k < V ; ++k)
        {
            int intermediate_node = k;
            for(from = 0 ; from < V ; ++from){
                for (to = 0 ; to < V ; ++to){
                    if(from == to)
                        continue;
                        int leave = memo[from][to]; // leave the kth node
                        // take the kth node as intermediate
                        int take1 = memo[from][intermediate_node];
                        int take2 = memo[intermediate_node][to];
                        int take;
                        if(take1 == OO || take2 == OO)
                            take = OO;
                        else
                            take = take1 + take2;
                        memo[from][to] = Math.min(leave,take);
                }
            }
            System.out.println("After relaxing with " + k);
            print_answer(memo);
        }
    }
    private void print_answer(int[][]arr){

        for(int r = 0 ; r < V ; ++r)
        {
            for(int c = 0 ; c < V ; ++c){

                System.out.print(arr[r][c] == OO ? "OO " : arr[r][c]+ " ");
            }
            System.out.println();
        }
        System.out.println("*".repeat(V+1));
    }
    public static void main(String[] args) {

        Floyd floyd = new Floyd();
        floyd.fillInput();
        floyd.solve_tabulation_v1();
    }







}

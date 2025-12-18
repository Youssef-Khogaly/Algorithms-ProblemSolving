import java.io.File;
import java.io.FileNotFoundException;
import java.util.Arrays;
import java.util.Scanner;

public class MiniMaxFloyd {
    private int[][] mat = null;
    private int V;
    private int E;
    private final int OO = Integer.MAX_VALUE;
    private final String inputPath = "/home/khogaly/yossef/Mastering_critical_SKILLS_in_Algorithms_using C++:Part1/Algorithms-ProblemSolving/floydWarshal_shortestPath/input.txt";
    private  void fillInput(){
        try(Scanner scanner = new Scanner(new File(inputPath)))
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
        } catch (FileNotFoundException e) {
            System.out.println(e.getMessage());
            throw new RuntimeException(e);
        }
        catch (Exception e) {
            System.out.println(e.getCause().getMessage());
            throw e;
        }
    }
    /*

    mini max is
    minimizing the maximum damg that happen in the path
     */
    private void miniMaxSolve() {
        int from, to;
        for (int k = 0; k < V; ++k) {
            int intermediate_node = k;
            for (from = 0; from < V; ++from) {
                for (to = 0; to < V; ++to) {
                    if(from == to || k == from || k == to)
                        continue;
                    if(mat[from][k] == OO || mat[k][to] == OO)
                        continue;

                    // Math.max(mat[from][k] , mat[k][to]) to get the max weight in that path
                    // cause we want to get the maximum damg in that paths
                    // and minimize it
                    // then pick the minumum path
                    mat[from][to] = Math.min(mat[from][to] , Math.max(mat[from][k] , mat[k][to]));
                }
            }
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
        MiniMaxFloyd miniMaxFloyd = new MiniMaxFloyd();
        miniMaxFloyd.fillInput();
        System.out.println("source ------------------------------------");
        miniMaxFloyd.print_answer(miniMaxFloyd.mat);
        System.out.println("target ------------------------------------");
        miniMaxFloyd.miniMaxSolve();
        miniMaxFloyd.print_answer(miniMaxFloyd.mat);

    }
}

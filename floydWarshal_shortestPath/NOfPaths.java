import java.io.File;
import java.io.FileNotFoundException;
import java.util.Arrays;
import java.util.Scanner;

public class NOfPaths {
    private int[][] mat = null;
    private int[][] countMat = null;
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
//            for(int[] row : mat)
//                Arrays.fill(row,OO);
            int i = E;
            for(;i!=0;--i){
                int from = scanner.nextInt();
                int to = scanner.nextInt();
                //int weight = scanner.nextInt();
                mat[from][to] +=  1;
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
    private void countNumberOfPaths()
    {
        int k , src , des;

        for(k = 0 ; k < V ; ++k){
            for(src = 0 ; src < V ; ++src)
            {
                for(des = 0 ; des < V ; ++des)
                {
                    if(mat[k][des] == 0 || mat[src][k] == 0 )
                        continue;
                    /*
                        if there is only 1 path from src to k
                        and only 1 path from k to des
                        so its only 1 new path from src to des

                        what if there is 2 paths from src to k and only 1 from k to des
                        that's mean 2 * 1 new paths = 3

                     */
                    mat[src][des] += (mat[k][des] * mat[src][k]);
                }
            }
        }
        // handle cycle
        // now if  k node have cycle
        // and there is a path src -> k
        // and  k -> des that's mean there infinite number of paths from src -> des
        for(k = 0 ; k < V ; ++k){
            if(mat[k][k] != 0)
            {
                for(src = 0 ; src < V ; ++src)
                {
                    for(des = 0 ; des < V ; ++des)
                    {
                        if(mat[k][des] != 0 && mat[src][k] != 0)
                        {
                            mat[src][des] = -1;
                        }

                    }
                }
            }

        }
    }

    public static void main(String[] args) {
        NOfPaths nOfPaths = new NOfPaths();
        nOfPaths.fillInput();
        System.out.println("source ------------------------------------");
        nOfPaths.print_answer(nOfPaths.mat);
        System.out.println("target ------------------------------------");
        nOfPaths.countNumberOfPaths();
        nOfPaths.print_answer(nOfPaths.mat);

    }
}

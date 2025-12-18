import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Scanner;

public class PrintPath {

        private int[][] mat = null;
        private int V;
        private int E;
        private final int OO = Integer.MAX_VALUE/3;
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
            } catch (FileNotFoundException e) {
                System.out.println(e.getMessage());
                throw new RuntimeException(e);
            }
            catch (Exception e) {
                System.out.println(e.getCause().getMessage());
                throw e;
            }
        }

        private void solve(){

            int k , from , to;
            int midNode;
            // best node as intermediate from -> to
            int[][] paths = new int[V][V];
            // init paths
            for(int i = 0 ; i < V ; ++i)
            {
                for(int j = 0 ; j < V ; ++j)
                {
                    if(mat[i][j] == OO)
                        paths[i][j] = -1; // no path
                    else
                        paths[i][j] = j;
                }
            }
            int nextNode = 0;
            int ans;
            for(k = 0 ; k < V ; ++k)
            {
                for(from = 0 ; from < V ; ++from){

                    for (to = 0 ; to < V ; ++to){
                        if(mat[k][to] == OO || mat[from][k] == OO )
                        {
                            nextNode = to;
                            ans = mat[from][to];
                        }
                        else {
                            if(mat[from][to] > mat[from][k] + mat[k][to])
                            {
                                ans = mat[from][k] + mat[k][to];
                                // the next node for the path from -> to
                                // is the first node in the path from -> k
                                // not K !!!!!!!
                                paths[from][to] = paths[from][k];
                            }else
                                ans = mat[from][to];
                        }
                        mat[from][to] = ans;

                    }
                }
            }
            print(paths,0,4);
        }
        // print the shortest path from -> to
        private void print(int[][]paths , int from , int to){
            if(paths[from][to] == -1)
                System.out.println("Not reachable");
            if(from == to)
                return;
            System.out.print(from +" -> ");
            int next  = paths[from][to];

                if(next == to)
                {
                    System.out.print(next);

                }
                else
                {
                    print(paths,next,to);
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

            PrintPath floyd = new PrintPath();
            floyd.fillInput();
            floyd.solve();
        }

}

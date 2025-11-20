//https://www.geeksforgeeks.org/dsa/rat-in-a-maze/
public class ratInMaze
{
    
import java.util.*;
import java.util.stream.Collectors;

public class Main {
    public static void main(String[] args) {
        int[][] maze = {
                {1, 0, 0, 0},
                {1, 1, 0, 1},
                {1, 1, 0, 0},
                {0, 1, 1, 1}
        };

        RatInMaze solve = new RatInMaze();
        var answers = solve.countValidPaths(maze);
        System.out.println("min steps paths = " + answers.size());
        System.out.println("-----------------------------------------------------");
        answers.forEach(a ->{
            System.out.println(a);
            System.out.println("steps = " + a.size());
            System.out.println("-----------------------------------------------------");
        });
    }


    private static class RatInMaze
    {
        public static class node
        {
            public  int r;
            public  int c;
            public  node(int r , int c){
                this.r = r;
                this.c = c;
            }
            public node (node n){
                this.r = n.r;
                this.c = n.c;
            }
            @Override
            public String toString() {
                return "{" +r +','+  c + '}';
            }

            @Override
            public boolean equals(Object o) {
                if (o == null || getClass() != o.getClass()) return false;

                node node = (node) o;
                return r == node.r && c == node.c;
            }
            @Override
            public int hashCode() {
                int result = r;
                result = 31 * result + c;
                return result;
            }
        }
        private Set<ArrayList<node>> answers;

        private int minSteps = Integer.MAX_VALUE;
        private final int[] rd = new int[]{-1,1,0,0};
        private  final int[]cd = new int[]{0,0,-1,1};
        private int[][] grid;
        private int ROWS;
        private int COLS;
        private boolean[][] visited;
        private boolean isValid(int r , int c)
        {
            return (r > -1 && c > -1 && r< ROWS && c <COLS && grid[r][c] != 0);
        }
        private void solve(int r , int c , ArrayList<node> currPath){

            currPath.add(new node(r,c));
            // mark visited
            visited[r][c] =true;
            if(r == ROWS-1 && c == COLS-1)
            {

                if(currPath.size() < minSteps)
                {
                    minSteps = currPath.size();
                    answers.clear();
                    answers.add((new ArrayList<node>(currPath)));

                }else if (currPath.size() == minSteps){
                    answers.add((new ArrayList<node>(currPath)));
                }
            }
            else if (currPath.size() <= minSteps){
                int nr , nc , i;
                for(i = 0 ; i < 4 ; ++i)
                {
                    nr = r + rd[i];
                    nc = c+cd[i];
                    if(isValid(nr,nc) && !visited[nr][nc])
                    {
                        solve(nr,nc,currPath);
                    }
                }
            }
            visited[r][c] = false;
            currPath.remove(currPath.size()-1);
        }
        public Set<ArrayList<node>> countValidPaths(int[][]mat){
            grid = mat;
            ROWS = grid.length;
            COLS = grid[0].length;
            visited = new boolean[ROWS][COLS];
            answers = new HashSet<>();
            solve(0,0,new ArrayList<node>(ROWS*COLS));

            return answers;
        }
    }
}

}
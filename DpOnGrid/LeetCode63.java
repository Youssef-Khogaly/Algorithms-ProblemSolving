import java.util.Arrays;

public class LeetCode63 {


        // down , right
    private final int dr[] = new int[]{1,0};
    private final int dc[] = new int[]{0,1};
    private  int[][] memo = null;
    /* 
        f(r,c) -> return count of unique pathes starting from r,c
    */
    private boolean valid(int[][] grid , int r , int c)
    {
        return r < grid.length && c < grid[r].length && grid[r][c] == 0;
    }
    private int count(int[][]grid , int r , int c){ // o(rxc)time , o(rxc) memory
        if(false == valid(grid,r,c) )
            return 0;
        // have i reached the target ?
        if(r == grid.length - 1 && c == grid[r].length - 1 )
            return 1;
        
        if(memo[r][c] != -1)
            return memo[r][c];

        // move right and down and the answer is the sum
        // and save the answer
        return memo[r][c] = count(grid,r+dr[1],c+dc[1]) + count(grid,r+dr[0],c+dc[0]);
    } 
    public int uniquePathsWithObstacles(int[][] grid) {
        memo = new int[100][100];
        for(int[] row : memo){
            Arrays.fill(row,-1);
        }
        return count(grid,0,0);
    }

}

import java.util.Arrays;

public class LeetCode576 {
    private static final int[] rd = new int[]{1,-1,0,0};
    private static final int[] cd = new int[]{0,0,1,-1};
    private int m = 0;
    private int n = 0;
    private int sr = 0;
    private int sc = 0;
    private int[][][] memo = null;
    private static int mod = 1000000007;
    /*
     * 
     * solve(r,c,moves) -> return number of pathes starting from r,c with m moves
     */
    private int solve(int r , int c , int maxMove){

        // out of grid
        if(r < 0 || c < 0 ||  r > m-1 || c > n-1 ){
            // took more than max moves? invalid path
            // else valid path
            return maxMove > -1 ? 1 : 0;
        }
        else if (maxMove < 1) // no moves left and we are not out of grid
        {
            return 0;
        }

        if(memo[r][c][maxMove] != -1){
            return memo[r][c][maxMove];
        }
        int ret = 0;
        int i = 0;
        for(; i < 4 ; ++i){

            ret =  (ret + solve(r+rd[i],c+cd[i],maxMove-1)) % mod;
        }


        return memo[r][c][maxMove] = ret;

    }

    public int findPaths(int m, int n, int maxMove, int startRow, int startColumn) {
        this.m = m;
        this.n = n;
        sr = startRow;
        sc = startColumn;
        memo = new int[m][n][maxMove+1];
        for(int[][] arr : memo){
            for(int[]row : arr){
                Arrays.fill(row, -1);
            }
        }
        return solve(sr,sc,maxMove);
    }
}

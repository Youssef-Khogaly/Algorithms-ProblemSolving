public class outOfBoundryBall { // leetcode 576
class Solution {
    private final int MOD = 1000000007;
    private int ROWS;
    private int COLS;
                    // up , down , left , right
    private final int[] rd = new int[]{-1,1,0,0};
    private final int[] cd = new int[]{0,0,-1,1}; 
    private int[][][]memo;
    private int dp(int r , int c , int moves)
    {
        if(r == ROWS || c == COLS || r == -1 || c == -1)
            return 1;
        else if(moves == 0)
            return 0;
        else if(memo[r][c][moves] != -1)
            return memo[r][c][moves];
        int i = 0;
        int ans=0;
        for(;i < 4; ++i)
        {
            ans = (ans + dp(r+rd[i],c+cd[i],moves-1))% MOD;
        }

        return memo[r][c][moves] = ans;
    }
    private int helper(int r , int c , int m)
    {
        if(r == ROWS || c == COLS || r == -1 || c == -1)
            return 1;
        else if(m == 0)
            return 0;
        
        return memo[r][c][m];
    }
    private int tabulation(int maxMove, int startRow, int startColumn)
    {
        int r , c;
        int m;
        int ans;
        int i;
        // moves here control the state
        // so iterate over it from small to large
        for( m = 1 ; m <= maxMove ; ++m)
        {
            for(r = 0 ; r < ROWS ; ++r)
            {
                for(c = 0 ; c < COLS ; ++c)
                {
                        ans = 0;
                        for(i = 0;i < 4; ++i)
                        {
                            ans = (ans + helper(r+rd[i],c+cd[i],m-1))% MOD;
                        }
                        memo[r][c][m] = ans;
                    
                }
            }
        }
        return memo[startRow][startColumn][maxMove];
    }
    public int findPaths(int m, int n, int maxMove, int startRow, int startColumn) {
        ROWS = m;
        COLS = n;
        memo = new int[m][n][maxMove+1];

        return tabulation(maxMove,startRow,startColumn);
    }
}
}

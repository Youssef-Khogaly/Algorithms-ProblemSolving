import java.util.Arrays;

public class Leetcode931 {

    private static int[][] memo = new int[100][100];
    private boolean isValid(int[][]mat,int r,int c){
        return c > -1 && r < mat.length && c < mat[r].length;
    }
    /*
        minSum(r,c) -> return min sum starting from r ,c
    */
    int minSum(int[][] mat , int r, int c){
        // reach end
        if(r == mat.length-1){
            return mat[r][c];
        }
        if(memo[r][c] != -1){
            return memo[r][c];
        }
        int ans = Integer.MAX_VALUE;

        // can move diag left ?
        if(isValid(mat,r+1,c-1)){
            ans = Integer.min(ans,minSum(mat,r+1,c-1));
        }
        // can move down
        if(isValid(mat,r+1,c)){
            ans = Integer.min(ans,minSum(mat,r+1,c));
        }
        // can move diag right
        if(isValid(mat,r+1,c+1)){
            ans = Integer.min(ans,minSum(mat,r+1,c+1));
        }

        return memo[r][c] = ans+mat[r][c];
    }
    public int minFallingPathSum(int[][] mat) {
        int ret = Integer.MAX_VALUE;
        for(int[]row : memo){
            Arrays.fill(row,-1);
        }
        for(int i = 0 ; i < mat[0].length ; ++i){
            ret = Integer.min(ret,minSum(mat,0,i));
        }
        return ret;
    }
}

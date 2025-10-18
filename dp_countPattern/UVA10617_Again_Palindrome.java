import java.util.Arrays;

public class UVA10617_Again_Palindrome {

    private int[][] memo;
    private int dp_solve(String s , int l , int r){

        if(l == r)
            return 1;
        else if (l > r)
            return 0;
        if(memo[l][r] != -1)
            return memo[l][r];

        char c1  = s.charAt(l);
        char c2 = s.charAt(r);
        memo[l][r] = 0;
        if(c1 == c2)
        {
            // use both end
            // with the answer of inner block 
            memo[l][r] = 1 +  dp_solve(s, l+1, r-1) ;
        }
        // remove left and remove right
        memo[l][r] +=  dp_solve(s, l+1, r)+ dp_solve(s,l, r-1) - dp_solve(s, l+1, r-1);
            // the block between l & r will be counted twice
            // once inside dp_solve(s, l+1, r) calls and again inside dp_solve(s,l, r-1)
            // so just compute the inner block answer and subtract it from the answer :)
        
        return memo[l][r] = memo[l][r];
    }

    public int count(String s)
    {
        memo = new int[s.length()+1][s.length()+1];
        for(int[] row : memo)
            Arrays.fill(row, -1);
        
        return dp_solve(s,0,s.length()-1);
    }
    
}

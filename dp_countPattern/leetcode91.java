import java.util.Arrays;

class Solution {
    private int[] memo;
    private int dp_solve(String s , int idx) // o(2^n)
    {
        if(idx == s.length())
            return 1;

        if(memo[idx] != -1)
                return memo[idx];
        if(s.charAt(idx) == '0' )
            return memo[idx] = 0;

        int take1 = 0 , take2 = 0;
        char c1 = s.charAt(idx);
        
        // solve for 1 take
        take1 = dp_solve(s, idx + 1);

        // can i take 2?
        if(idx+1 < s.length()){
            char c2 = s.charAt(idx+1);
            if(c1 == '1' ||( c1 == '2' && c2 < '7')){
                take2 = dp_solve(s, idx + 2);
            }
        }


        return memo[idx] = take1 + take2;
    }
    public int numDecodings(String s) {
        
        memo = new int[s.length()+1];
        Arrays.fill(memo, -1);
        return dp_solve(s,0);
    }
}
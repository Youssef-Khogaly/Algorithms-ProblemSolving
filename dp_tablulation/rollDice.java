public class rollDice { // leetcode 1155
class Solution {
    private int MOD = 1000000007;
    private int dices;
    private int faces;
    private int[][]memo;
    private int dp(int i , int target)
    {
        if(i == dices){
            return (target == 0) ? 1 : 0;
        }
        if(memo[i][target] != -1)
            return memo[i][target];
        int ans = 0;
        for(int j = 1 ; j <= faces ; ++j)
        {
            if(target-j < 0)
                break;
            ans = (ans + dp(i+1,target-j))%MOD; 
        }

        return memo[i][target]=ans;
    }
    private int tabulation(int target)
    {
        int base = Math.min(faces,target);
        // base case
        // what i can make with 1 dice
        // memo[0][0] is not possible to get target = 0
        for(int i = 1 ; i <= base ; ++i)
            memo[0][i] = 1;

        for(int i = 1 ; i < dices ; ++i)
        {
            for(int t = 1 ; t <= target ; ++t)
            {
                long ans = 0;
                for(int j = 1 ; j <= faces ; ++j)
                {
                    if(t-j < 0)
                        break;
                    ans = (ans + memo[i-1][t-j])%MOD;  
                }
                memo[i][t] = (int)ans;
            }
        }
        return memo[dices-1][target];
    }
    public int numRollsToTarget(int n, int k, int target) {
        dices = n;
        faces = k;
        memo = new int[dices][target+1];

        return tabulation(target);
    }
}
}

public class CoinsChange1 {
    // leetcode 322
    class Solution {
    private int[] arr;
    private int len;
    private final int NO_ANSWER = Integer.MAX_VALUE-10000;
    private int[][] memo;
    /*
        compute the number of coin used to get amunt
        for dp(i , amount)
        return NO_ANSWER if there is no answer
    */
    private int dp(int idx , int amount){
        if(idx  == len || amount <= 0){
            //  return 0 mean no coins used
            return amount == 0 ? 0 : NO_ANSWER; 
        }
        if(memo[idx][amount] != -1)
            return memo[idx][amount];
        // pick current again 
        // can i pick 
        int pick = (amount-arr[idx] >= 0) ? dp(idx,amount-arr[idx])+1 : NO_ANSWER;
        // compute best answer if i didn't pick this
        int leave = dp(idx+1,amount);

        return memo[idx][amount] = Math.min(pick,leave);
    }
    private int tabulation_helper(int idx , int amount){
        if(idx < 0 || amount < 0)
            return NO_ANSWER;

        return memo[idx][amount];
    }
    private int tabulation(int amount){
        memo = new int[len][amount+1];

        // base case
        // to make 0 amount we need 0 coins
        //    for(int i = 0 ; i < len ; ++i)
        //     memo[i][0] = 0;
        // we can skip the init since

        int ans;
        for(int idx = 0 ; idx < len ; ++idx){
            for(int target = 1 ; target < amount+1 ; ++target){
                // leave use previous coins
                int leave = tabulation_helper(idx-1,target);
                // compute pick answer
                int pick = tabulation_helper(idx,target-arr[idx]) + 1;
                
                memo[idx][target] = Math.min(pick,leave);
            }
        }
        return memo[len-1][amount];
    }
    public int coinChange(int[] coins, int amount) {
        if(amount == 0)
            return 0;

        arr = coins;
        len = coins.length;
        int ans = tabulation(amount);
        return ans == NO_ANSWER ? -1 : ans;
    }
}
}

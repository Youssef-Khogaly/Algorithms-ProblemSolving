public class CoinsChange2 {
class Solution {
    private int[] arr;
    private int len;
    private int[][] memo;
    private int[] memo_opt;
    /*
        represent the answer for dp(i,amount)
        answer starting from idx = i with amount = amount
    */
    private int top_down(int idx , int amount){
        if(idx == len  || amount < 1){
            return amount == 0 ? 1 : 0;
        }
        if(memo[idx][amount] != -1)
            return memo[idx][amount];
        int pick = top_down(idx , amount-arr[idx]);
        int leave = top_down(idx+1,amount);

        return memo[idx][amount]=pick+leave;
    }
    private int tabulation_helper(int idx , int amount){
        if(idx == -1 || amount < 0)
            return 0;
        if(amount == 0)
            return 1;
        
        return memo[idx][amount];
    }
    private int tabulation(int amount){
        memo = new int[len][amount+1];
        //for(int[] row : memo)
        //    row[0] = 1; // base case if you need amount of 0 you need 1 coin
        // we can skip it
        for(int idx = 0 ; idx < len ; ++idx){
            for(int target = 1 ; target < amount+1 ; ++target){
                int pick = tabulation_helper(idx,target-arr[idx]);
                int leave = tabulation_helper(idx-1,target);
                memo[idx][target] = pick+leave;
            }
        }
        return memo[len-1][amount];
    }
    public int change(int amount, int[] coins) {
        if(amount == 0)
            return 1;
        arr = coins;
        len = coins.length;

        return tabulation_space_opt(amount);
    }

        private int tabulation_helper_space_opt(int idx , int amount){
        if(idx == -1 || amount < 0)
            return 0;
        if(amount == 0)
            return 1;
        
        return memo_opt[amount];
    }
    private int tabulation_space_opt(int amount){
        // we can reduce the memory to only save the previous row
        // since current answer only depend on the previous answer
        // but smarter idea 
        // we need only to store how many comination
        // to get that amount and accumlate we don't care about the idx
        memo_opt = new int[amount+1];
        memo_opt[0] = 1; // base case since we need 1  coin to make amount of 0
        for(int idx = 0 ; idx < len ; ++idx){
            for(int target = 1 ; target < amount+1 ; ++target){
                int pick = tabulation_helper_space_opt(idx,target-arr[idx]);
                int leave = tabulation_helper_space_opt(idx-1,target);
                memo_opt[target] = pick+leave;
            }
        }
        return memo_opt[amount];
    }
}
}

class Solution {

    private int[][] memo;
    private int solve(int amount , int[] coins , int idx){ // o(co * m) time , o(n*m)memory
        if(idx == coins.length){
            return amount == 0 ? 1 : 0;
        }
        if(memo[idx][amount] != -1){ return memo[idx][amount];}

        // skip current
        memo[idx][amount] = solve(amount , coins, idx+1);
        // pick current again if we can
        if(coins[idx] <= amount)
        {
            memo[idx][amount] += solve(amount-coins[idx] , coins, idx);
        }
        return memo[idx][amount];
    }
    public int change(int amount, int[] coins) {
        memo = new int[coins.length+1][amount+1];
        for (int[] row : memo)
            Arrays.fill(row, -1);
        
        return solve(amount, coins, 0);
    }
}
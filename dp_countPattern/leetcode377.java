import java.util.Arrays;

public class leetcode377 {
    class Solution {

    private int[] memo;



    private  int solve(int[] nums , int target){
        if(target == 0)
            return 1;
        if(memo[target] != -1)
            return memo[target];
        int res = 0;
        // get all possible answers from here
        // since order matter
        for(int i = 0 ; i < nums.length ; ++i){
            if(target >= nums[i]){
                res += solve(nums,target-nums[i]);
            }
        }

        return memo[target] = res;
    }
    public int combinationSum4(int[] nums, int target) {
        memo = new int[1001];
        Arrays.fill(memo,-1);
        return solve(nums,target);
    }
}
}

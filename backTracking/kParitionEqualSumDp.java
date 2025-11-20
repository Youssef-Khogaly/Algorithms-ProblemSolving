public class kParitionEqualSumDp {
class Solution {
        private int totalSum = 0;
        private int equalSum;
        private int[] nums;
        private int k;
        private boolean[] mask;
        private boolean solve(int i , int partion_idx , int curr_sum) { // o(K * 2^N)

            // if current parition filled try to fill the second
            // and so on
            if(curr_sum == equalSum)
                return solve(0,partion_idx+1,0);
               

            if(partion_idx == k) // already all parition filled
                return true;
            
            if(i == nums.length)
                return false;
            
            // classic pick or leave dp pattern

            // can't pick
            if(mask[i] == true)
            {
                return solve(i+1,partion_idx,curr_sum);
            }
            // pick current
            mask[i] = true;
            boolean pick = solve(i+1,partion_idx , curr_sum+nums[i]);
            if(pick)
                return true;

            mask[i] = false; // mark leaved
            // leave current
            return solve(i+1,partion_idx , curr_sum);
        }

        public boolean canPartitionKSubsets(int[] nums, int k) {
            for (int n : nums)
                totalSum += n;
            if (totalSum % k != 0)
                return false;

            
            equalSum = totalSum / k;

            for (int n : nums)
            {
                if(n > equalSum)
                    return false;
            }
            this.k = k;
            this.nums = nums;
            mask = new boolean[nums.length];

            return solve(0,0,0);
        }
}



}

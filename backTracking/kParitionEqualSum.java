import java.util.Arrays;

public class kParitionEqualSum { //leetcode 698
class Solution {
        private int totalSum = 0;
        private int[] paritions;
        private int equalSum;
        private int[] nums;
        private int k;
        private int countEqual = 0;
        private boolean solve(int i) { // o(k^N)
            boolean ret = false;
            if (i == nums.length) {
                return countEqual == k;
            }
            if(countEqual == k-1)
                return true;
            int j;
            for (j = 0; j < k; ++j) {
                // can I add in this partition?
                if (paritions[j] + nums[i] <= equalSum) {
                        paritions[j] += nums[i];
                        if( paritions[j] == equalSum)
                            ++countEqual;
                        if (solve(i + 1))
                            return true;
                        if( paritions[j] == equalSum)
                            --countEqual;
                        paritions[j] -= nums[i];
                        // too important TLE without it  x10 perfomance
                        // if bucket is empty after undo no need to check another bucket
                        /*
                            what about first call
                            as example we add 2 in first bucket with others bucket empty
                            if there is no solution with only 2 in first bucket
                            so for sure there is no solution
                        */
                        if(paritions[j] == 0) 
                            return false;
                }
            }
            return false;
        }

        public boolean canPartitionKSubsets(int[] nums, int k) {
            for (int n : nums)
                totalSum += n;
            if (totalSum % k != 0)
                return false;

            
            equalSum = totalSum / k;
            paritions = new int[k];

            for (int n : nums)
            {
                if(n > equalSum)
                    return false;
            }
            this.k = k;
            this.nums = nums;
            Arrays.sort(nums);
            int tmp;
            // reverse
            for(int i = 0 , j = nums.length-1 ; i < j ; ++i , --j){
                tmp = nums[i];
                nums[i] = nums[j];
                nums[j] = tmp;
            }
                
            return solve(0);
        }
}
}

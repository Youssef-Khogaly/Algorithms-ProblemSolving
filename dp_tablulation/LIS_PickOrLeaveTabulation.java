public class LIS_PickOrLeaveTabulation {
        public int lengthOfLIS(int[] nums) {
        arr = nums;
        memo = new int[nums.length];
        
        // base case
        // the LIS for last element is always 1
        memo[nums.length-1] = 1;
        int ans = 1;
        for(int idx = nums.length-2 ; idx > -1 ; --idx)
        {
            memo[idx]=1;
            // check the best value to be my next
            for(int next = idx+1 ; next < nums.length ; ++next){
                
                // can i pick?
                if(arr[idx] < arr[next]){
                    // the answer is the 
                    // max between the LIS starting form my next + 1 vs my current lis
                    memo[idx] = Math.max(memo[idx],memo[next]+1);
                } // leave
            }
            if(memo[idx] > ans)
                ans = memo[idx];
        }
        return ans;
    }
}

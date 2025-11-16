    public int lengthOfLIS(int[] nums) {
        memo = new int[nums.length+1];

        memo[0] = 1; // base case
        int ans = 1;
        for(int i = 1; i < nums.length ; ++i){
            
            memo[i] = 1;
            for(int k = i-1 ; k > -1;--k)
            {
                if(nums[k] < nums[i] && memo[i] < memo[k]+1){

                    memo[i] = memo[k]+1;
                }
            }
            if(memo[i] > ans)
                ans = memo[i];
        }
            
        return ans;
    }
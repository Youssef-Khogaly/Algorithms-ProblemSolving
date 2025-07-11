
class Solution {

public:
/*

1 5 11 5

*/
    typedef signed char s8_t;
    inline bool canPartition(vector<int>& nums) noexcept {
        int totalSum = 0;
        // if the total sum of the array is odd we can not divide it into two subset with equal
        // sum anyway
        for(auto& n : nums)
            totalSum += n;

        if((totalSum % 2) == 1)
            return false;
        vector<vector<s8_t>> memo(nums.size(),vector<s8_t>(totalSum/2 +1 , -1));
        // now its pure pick or leave "knapsack" pattern
        // if you can find a subset with sum equal to totalsum/2
        // then must be there is another subset with totalsum/2 :)

        return pickOrLeave(nums,0,totalSum/2,memo);
    }

    inline bool pickOrLeave(vector<int>& nums , int idx , int target,vector<vector<s8_t>>& memo) noexcept
    {
        if(target == 0)// we got the answer
            return true;
        if(idx == nums.size() || target < 0 ) // all array number is postive if target is negative we cant get it 
            return false;
        auto&ret =  memo[idx][target];
        if(ret != -1)
            return ret;
        bool pick = pickOrLeave(nums,idx+1,target-nums[idx],memo);
        if(pick)
            return pick; // alittle optimization
        bool leave = pickOrLeave(nums,idx+1,target,memo);

        return ret = (int)(pick||leave);
    }
};
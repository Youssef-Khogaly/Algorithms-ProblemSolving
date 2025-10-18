class Solution {
    int memo[303][303];
public:
    int maxCoins(vector<int>& nums) {
        //memset(memo,-1,sizeof(memo));
        /*
            to make the boundries have neighbours
            since we thinking as current idx is the last ballon to brust
        */
        nums.insert(nums.begin(),1);
        nums.push_back(1);
        return dp(nums,1,nums.size()-2);
    }
    /*
        do(s,e): represent the max cost can we get from this range

        brute force all idcies as the LAST BALLON not first
        becasue if we chose first the left and right subproblems will depend on each other
        so reverse thinking
    */
    int dp(vector<int>& nums , int s , int e)
    {
        if(s > e)
            return 0;
        auto& ret = memo[s][e];
        if(ret != 0)
            return ret;

        int cost;
        int ans = INT_MIN;
        /*
            check all ballon in this range
            as the last ballon to brust
        */
        for(int k = s ; k <= e ; ++k)
        {
            // the last element in previous sub group
            // * current element since its the last one in this group
            // * the first element in the next subgroup
            cost = nums[s-1]*nums[k]*nums[e+1];
            ans = max(ans,cost+dp(nums,k+1,e)+dp(nums,s,k-1));
        }
        return ret = ans;
    }
};
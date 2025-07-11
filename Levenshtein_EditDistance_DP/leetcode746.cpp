class Solution {

private:

/*
    represet the min cost we can get 
    if we are in the idx i
*/
int memo[1001];
public:
    inline int minCostClimbingStairs(vector<int>& cost) noexcept {
        memset(memo,-1,sizeof(memo));

        return dp(cost);
    }

    /*
        def: return the min cost of if we are at idx i
        i don't care how

        typically an lis or lcs pattern
        just brute force all your choices and use memoization

        o(n) time , o(n)memory , o(n) max stack depth
    */
    int dp(vector<int>& cost,int i = 0) noexcept
    {
        if(i >= cost.size())
            return 0;

        auto& ret = memo[i];
        if(ret != -1)
            return ret;
        // 1 step
        int step1 = cost[i]+dp(cost,i+1);
        // special case we can jump from idx 0 to idx 1 for free
        if(i == 0)
            step1 = min(step1,dp(cost,i+1));
        // 2 step
        int step2 = cost[i]+dp(cost,i+2);

        return ret = min(step1,step2);
    }
};
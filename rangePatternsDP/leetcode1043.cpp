class Solution {
private:
    int memo[501];
    int maxLen;
public:
    inline int maxSumAfterPartitioning(vector<int>& arr, int k) noexcept {
        memset(memo,-1,sizeof(memo));
        maxLen = k;
        return dp(arr,0);
    }
    /*
    dp(i): the answer of i to the end of the array
    o(nxk) time , o(n)memory 
    */
    inline int dp(const vector<int>& arr , int s)noexcept
    {
        if(s == arr.size())
            return 0;
        if(s == arr.size()-1)
            return arr[s];

        int& ret = memo[s];
        if(-1 != ret)
            return ret;
        int currMax = -1;
        int currSum;
        for(int e = s , i = 1 ; i <= maxLen && e < arr.size() ; ++e , ++i){
            currMax = max(currMax,arr[e]);
            currSum = currMax*i;
            /*
                answer = currSum + the sum of the next block
            */
            ret = max(ret,currSum + dp(arr,e+1));
        }
        return ret;   
    }
};
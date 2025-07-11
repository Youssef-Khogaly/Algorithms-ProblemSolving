class Solution {
private:
int memo[10001];
public:
    int numSquares(int n) {
        if(n < 4) // special case
            return n;
        memset(memo,-1,sizeof(memo));

        return dp(n);
    }

    /*
        o(nsqrt(n))time 
    */
    int dp(int n)
    {
        if(n == 0)
            return 0;
        auto& ret = memo[n];
        if(ret != -1)
            return ret;
        int temp;
        ret = 999999;
        // brute force my choices
        // o(sqrt(n))
        for(int i = 1 ; i < n ; ++i)
        {
            temp = i*i;
            if(temp > n)
                break;
            
            ret = min(ret , 1+dp(n-temp));
        }
        return ret;
    }
};
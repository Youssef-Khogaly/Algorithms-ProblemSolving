class Solution {
private:
    // memo[i][j] longest palid sub seq in the range for i to j
    int memo[501][501];
public:
    inline int minInsertions(string s) noexcept {
        memset(memo,-1,sizeof(memo));
        return dp(s,0,s.size()-1);
    }
    /*
        dp(s,e): min number of inseartion in this range
        
        if(str[s] == str[e])
            this is our best case and we need to inseart no thing

        else
        we have 2 choices
        insert str[s] before e
        or insert str[e] before s

        o(n^2) time , o(n^2)memory
        o(n) max stack depth
    */
    int dp(const string& str ,int s , int e) noexcept
    {
        if( s >= e)
            return 0;
        auto& ret = memo[s][e];
        if(ret != -1)
            return ret;

        if(str[s] == str[e])
            return ret = dp(str,s+1,e-1);
        
        return ret = min(1+dp(str,s+1,e) , 1+dp(str,s,e-1));
    }
};
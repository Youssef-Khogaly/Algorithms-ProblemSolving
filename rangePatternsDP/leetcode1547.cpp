class Solution {
private:
    int memo[101][101];
public:
    inline int minCost(int n, vector<int>& cuts) noexcept{
        sort(begin(cuts),end(cuts));
        memset(memo,-1,sizeof(memo));
        /*
            add 0 at the start
            and add n to the end
            so now our s and e pointer
            represent the current length of the stick
        */
        cuts.insert(cuts.begin(),0);
        cuts.push_back(n);
        return dp(cuts,0,cuts.size()-1);
    }
    //dp(i,j) the min cost to get all cuts in i to j range
    int dp(vector<int>& cuts , int s , int e) noexcept
    {
        if(s +1 >= e)
            return 0; // there is no middle to split

        auto& ret = memo[s][e];
        if(ret != -1)
            return ret;
        
        int left , right,curr;
        int ans = INT_MAX;
        // brute force all split points to find the optimal "k" to split the current range
        for(int k = s+1 ; k < e ; ++k)
        {
            left = dp(cuts,s,k);
            right = dp(cuts,k,e);
            curr = cuts[e]-cuts[s];
            ans = min(ans , curr+left+right);
        }

        return ret = ans;

    }
};
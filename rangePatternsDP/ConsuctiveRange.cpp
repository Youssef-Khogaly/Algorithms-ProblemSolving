    #include <bits/stdc++.h>





    using namespace std;

    int memo[1000];
    // cost = price[end] * (sum quantity[start .. end]+10)
    /*
        min total cost to buy quantities starting from here to the end
    */
    int dp(const vector<int>& quan , const vector<int>& prices , int idx){
        if(idx == quan.size())
            return 0;
        auto& ret = memo[idx];
        if(ret != -1)
            return ret;
        int sum = 0;
        int cost;
        int ans = 99999999;
        for(int end = idx ; end < quan.size() ; ++end)
        {
            sum += quan[end];
            cost = (sum+10)*prices[end];
            /*
                calcualting the cost of ending here
                and then solve the rest
                and minmize
            
            */
            ans = min(ans,cost+dp(quan,prices,end+1)); 
        }
    
        return ret = ans;
    }
    int minCostToBuyAll(const vector<int>& quan , const vector<int>& prices)
    {
        memset(memo,-1,sizeof(memo));
        return dp(quan,prices,0);    
    }






    int main(){

    }
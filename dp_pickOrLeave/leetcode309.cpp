class Solution {
private:
    inline static constexpr int SIZE = 5001;
    int memo[SIZE][2]; // size of day , 2 holding or not holding state
public: 
    inline int maxProfit(vector<int>& prices) noexcept {
        memset(memo,-1,sizeof(memo));
        return knapsack(prices,0);
    }
    /*

        defination:
        knapsack(0,holding )the max profit you can earn statring from 0 while holding a stock
        knapsack(0,not holding)the max profit you can earn statring from 0 while not holding a stock

        calculate the best at every idx with the 2 state holding stock or not
         its much  better  than curr and prev as state 
    */
    int knapsack(vector<int>& prices , int curr , bool holding = false ) noexcept
    {
        if(curr >= prices.size())
            return 0;
        auto& ret = memo[curr][holding];
        if(ret != -1)
            return ret;
        int sell{-1};
        int buy{-1};
        int wait{-1};
        // can i sell
        if(holding)
            sell = knapsack(prices,curr+2, false) + prices[curr];
        else // can i buy ?
            buy = knapsack(prices,curr+1,true)-prices[curr];
        // wait
        wait = knapsack(prices,curr+1,holding);

        return ret=max({sell,buy,wait});
    }
};
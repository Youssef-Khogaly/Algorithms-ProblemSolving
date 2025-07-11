#include<bits/stdc++.h>


using namespace std;

class Solution {
private:
    struct comp{
        bool operator () (const vector<int>& a , const vector<int>& b)
        {
            return a > b;
        }
    };
    int memo[101][101]; // no need to mark we cannot get 0 as answer anyway
    int N;
public:
    int maxHeight(vector<vector<int>>& cuboids) {
        for(auto& v : cuboids) // o(n) since cuboids[i].size() is constant = 3
            sort(v.begin(),v.end());
        sort(cuboids.begin(),cuboids.end(),comp());
        // we sort becasue we need to maximize th height and we need the bigger cube first
        N = cuboids.size();

        return knapsack(cuboids,N,0);
    }
    inline bool isSmaller(vector<vector<int>>& cuboids,int prev  , int idx )const noexcept {
        return (cuboids[idx][0] <= cuboids[prev][0] && cuboids[idx][1] <= cuboids[prev][1] && cuboids[idx][2] <= cuboids[prev][2]);
    }
    /*
        pick or leave pattern
        definiation:
        knapack(0,1) will return the best answer for current window: from 1 to N-1 no matter how
    */
    int knapsack(vector<vector<int>>& cuboids,int prevIdx   , int idx ){
        if(idx == N)
            return 0;
        
        auto& ret = memo[prevIdx][idx];
        if(ret != 0)
            return ret;
        int pick{-1},leave{-1};

        // can i pick ?
        if(prevIdx == N || isSmaller(cuboids,prevIdx,idx)){
            pick = cuboids[idx][2] + knapsack(cuboids,idx,idx+1);
        }
        // leave
        leave = knapsack(cuboids,prevIdx,idx+1);

        return ret = max(pick,leave);
    }
};
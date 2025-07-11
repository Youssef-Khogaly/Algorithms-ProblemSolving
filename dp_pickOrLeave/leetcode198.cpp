#include<bits/stdc++.h>


using namespace std;






class Solution {

private:
    typedef signed short s16;
    s16 memo[401];
public:
    int rob(vector<int>& nums) {
        memset(memo,-1,sizeof(memo));
        return knapsack(nums,0);
    }
    /*
        no need to keep the history
        we can just move the idx+2 if we picked current idx since we can't pick two adjacent elements
        and if we want to leave current idx just idx + 1

        o(N) time , o(n) memory , auxalirty space o(n) for stack calls
    */
    int knapsack(vector<int>& nums , int idx)
    {
        if(idx >= nums.size())
            return 0;
        // sub problems overlap use memoization
        if(memo[idx] != -1)
            return memo[idx];


        // pick or leave pattern
        //  max between if we chose to rope current house or leave it 
        return memo[idx] = max(nums[idx]+knapsack(nums,idx+2) , knapsack(nums,idx+1));   
    }
};




int main(){

}
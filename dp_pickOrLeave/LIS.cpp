#include <bits/stdc++.h>


using namespace std;







vector<int> arr = {0,8,4,12,2,10,6,14,1,9,5,13,3,11,7,15};
vector<int> mask = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int memoization[2000][2000];



// return the longest sub seq
int lis(int prevPicked = -1 ,int idx = 0)
{
    if(idx  == (int)arr.size())
        return 0;


    auto& ret = memoization[prevPicked+1][idx];
    if(ret != -1)
        return ret;

    int picked = -1 , leave = -1;

    // can i pick it ?
    if(prevPicked == -1 || arr[prevPicked] < arr[idx])    
        picked = 1+lis(idx,idx+1);
    
    leave = lis(prevPicked,idx+1);

    return (ret = std::max(picked,leave));
}



namespace leetcode300
{
class Solution {

private:
    inline static constexpr int MAX = 2501;
    int memo[MAX][MAX];
public:
    int lengthOfLIS(vector<int>& nums) noexcept {
        
        memset(memo,-1,sizeof(memo));

        return lis(nums);
    }
    // pick or leave pattern , knapsack
    // o(n^2) time , o(n)stack depth , o(n^2)memory for the dp array
    int lis(vector<int>&nums , int currIdx = 0 , int lastPickedIdx = -1) noexcept
    {
        if(currIdx == nums.size())
            return 0;
        int picked = -1 , leaved = -1;
        auto& ret = memo[lastPickedIdx+1][currIdx];
        if(ret != -1)
            return ret; // result computed before just return it

        // can i pick it ?
        if(lastPickedIdx == -1 || nums[currIdx] > nums[lastPickedIdx])
            picked = 1+lis(nums,currIdx+1,currIdx);

        leaved = lis(nums,currIdx+1,lastPickedIdx);


        return ret = max(picked,leaved);
    }
};


class Solution2 {

private:
    inline static constexpr int MAX = 2501;
    int memo[MAX];
public:

/*
    now its an o(n^2) solution but it optimize the memory
    in the memoization array to only o(n)
*/
    int lengthOfLIS(vector<int>& nums) noexcept {
        
        memset(memo,-1,sizeof(memo));
        int maxlen = -1;
        for(int i = 0 ; i < nums.size() ; ++i)
        {
            /*
                compute the answer of every element as starting point
            */
            if(memo[i] == -1)
            {
                lis(nums,i);
            }
            maxlen = std::max(maxlen,memo[i]);
        }

        return maxlen;
    }
    int lis(vector<int>&nums , int currIdx = 0) noexcept
    {
        if(currIdx == nums.size())
            return 0;
        if(memo[currIdx] != -1)
            return memo[currIdx];
        
        int maxLen = 1;

        for(int i = currIdx+1 ; i < nums.size() ; ++i)
        {
            // on every possible choice compute the answer
            // and maximuze among all of them
            if(nums[i] > nums[currIdx])
            {
                maxLen = max(maxLen , lis(nums,i)+1);
            }
        }

        return  memo[currIdx] = maxLen;
    }
};

}








int main(){

    memset(memoization,-1,sizeof(memoization));
    cout << lis()<<endl;;

    for(int i = 0 ; i < mask.size() ; ++i)
    {
        if(mask[i] == 1)
            cout << arr[i] <<" ";
    }

    return 0;
}
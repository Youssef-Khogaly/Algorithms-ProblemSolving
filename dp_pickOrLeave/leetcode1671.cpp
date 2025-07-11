#include<bits/stdc++.h>


using namespace std;

class Solution {
    private:
    int memo[1001];
    int memo2[1001];
public:
    int minimumMountainRemovals(vector<int>& nums) noexcept{
        if(nums.size() == 3)
            return 0;
        memset(memo,-1,sizeof(memo));
        memset(memo2,-1,sizeof(memo2));

        /*
            longest increasing subsequence ending at i
        */
        for(int i = nums.size()-1 ; i > -1 ; --i)
            lis(nums,i);

        /*
            longest decreasing subsequence starting at i
        */
        for(int i = 0 ; i < nums.size() ; ++i)
            lds(nums,i);

        int maxret = 0;
        for(int i = 0 ; i < nums.size() ; ++i)
        {
            /*
                now we can find the longest mountain easly
                since memo[i] represend the longest increasing seq ending at i
                and memo2[i] represend the longest decreasing seq starting from i

            */
            if(memo[i] > 1 && memo2[i] > 1)
                maxret = std::max(maxret , memo[i]+memo2[i]-1);            
        }
        return nums.size()-(maxret);
    }

    /*
    def:
        lis(0): return the max increasng seq length starting with nubmer arr[0]
    */
    inline int lis(vector<int>& nums , int curr) noexcept
    {
        if(curr == nums.size())
            return 0;
        auto& ret = memo[curr];
        if(ret != -1)
            return ret;
        int maxret{1}; // 1 becasue the current element must be the end of the lis seq
        /* if arr[i] is bigger / caculate the lis(i)*/
        for(int i = curr-1 ; i >-1  ; --i)
        {
            if(nums[i] < nums[curr])
            {
                maxret = std::max(maxret,1 + lis(nums,i));
            }
        }
        
        return ret = maxret;
    }
    inline int lds(vector<int>& nums , int curr) noexcept
    {
        if(curr == nums.size())
            return 0;
        auto& ret = memo2[curr];
        if(ret != -1)
            return ret;
        int maxret{1}; // 1 becasue the current element must be the start of the lds seq
        /* if arr[i] is smaller / caculate the lis(i)*/
        for(int i = curr+1 ; i < nums.size() ; ++i)
        {
            if(nums[i] < nums[curr])
            {
                maxret = std::max(maxret,1 + lds(nums,i));
            }
        }

        return ret = maxret;
    }
};
/*

1 1 2 2 3 5 6
*/
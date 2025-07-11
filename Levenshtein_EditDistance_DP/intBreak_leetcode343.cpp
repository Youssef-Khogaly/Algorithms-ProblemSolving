#include <bits/stdc++.h>







class Solution {
    private:
    int memo[64];
public:
    inline int integerBreak(int n) noexcept{
        if(n == 2 || n == 3) // special case becasue in the constrains we must divide the number to 2 sum atleast
            return n-1;      // handle them here better than play with my dp function
       memset(memo,-1,sizeof(memo));
       return maxProduct(n); 
    }
    /*
        def:
        divide n to sum operations and return the max product
        i don't care how 
        
    */
    int maxProduct(int n)noexcept 
    {
        if(n == 1)
            return 1;
        auto& ret = memo[n];
        if(ret != -1)
            return ret;

        int max = n; // maybe i will choice to not divide it 
        // brute force all my choices
        for(int i = 1 ; i < n ; ++i)
        {
            max = std::max(max,maxProduct(n-i)*i);
        }

        return ret = max;
    }
};








int main(){
    
}
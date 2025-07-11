#include <bits/stdc++.h>


using namespace std;






namespace leetcode1143
{
class Solution {
    private:
    int memo[1001][1001];
public:
    int longestCommonSubsequence(string text1, string text2) noexcept {
        memset(memo,-1,sizeof(memo));

        return lcs(text1,text2);
    }
    // typically pick or leave pattern
    // but with 4 choices
    // pick from first , leave from second
    // leave first , pick second
    // .. etc


    /*
    
        the definiation:
        lcs(i,j) return the largest common sequence 
        in the window of i to N and j to M no more tracing than that
        
        o(NM) time , o(NM) memory for the memoization
        o(NM) max stack depth
        */
    inline int lcs(string& text1 , string& text2 , int idx1 = 0 , int idx2 = 0) noexcept{
        if(idx1 == text1.size() || idx2 == text2.size())
            return 0;
        auto& ret  = memo[idx1][idx2];
        if(ret != -1)
            return ret;

        int pickBoth = -1;
        int pickFirst = -1;
        int pickSecond = -1;
        int leaveBoth = -1;
        // the most logically choice here is to pick both and no need to do any other thing
        // and logically we need only to pick both if they are equal
        if(text1[idx1] == text2[idx2]){
            return ret = lcs(text1,text2,idx1+1,idx2+1) + 1;
        }
        pickFirst = lcs(text1,text2,idx1,idx2+1);
        pickSecond = lcs(text1,text2,idx1+1,idx2);
        // we can ignore the leave both case since it will be computed
        // in the subcalls of the above calls anyway
        //leaveBoth = lcs(text1,text2,idx1+1,idx2+1);


        return ret = std::max({pickBoth,pickFirst,pickSecond,leaveBoth});
    }
};
}





int main(){

}
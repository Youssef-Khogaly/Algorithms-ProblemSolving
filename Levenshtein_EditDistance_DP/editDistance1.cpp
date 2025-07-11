#include <bits/stdc++.h>


using namespace std;

// leetcode72
class Solution {

    private:
    typedef signed short s16;

    s16 memo[501][501];
public:
    int minDistance(string word1, string word2) {
        memset(memo,-1,sizeof(memo));


        return editDistance(word1,word2,0,0);
    }

    /*
        we have 4 stat here
        first match both chars
        2-insert a char from current w2  in w1 
        3-delete a char in w1
        4- replace a char in w1 with current char in w2


        def:
        editDistance(2,3): return the minum edit needed
        starting from w1[2] and w2[3] to make both strings matching
    */
    int editDistance(const string&w1 , const string& w2 , int idx1 , int idx2)
    {
        if(idx1 == w1.size() && idx2 == w2.size())
            return 0;
        else if(idx1 == w1.size() || idx2 == w2.size())
        {
            int r1 = w1.size()-idx1;
            int r2 = w2.size()-idx2;
            return (r1 > r2) ? r1 : r2;
        }
        auto& ret = memo[idx1][idx2];
        if(ret != -1)
            return ret;

        if(w1[idx1]==w2[idx2])
        {
            return editDistance(w1,w2,idx1+1,idx2+1);
        }
        int ins{-1},del{-1},rep{-1};

        ins = 1+editDistance(w1,w2,idx1,idx2+1);
        rep = 1+editDistance(w1,w2,idx1+1,idx2+1);
        del = 1+editDistance(w1,w2,idx1+1,idx2);


        return ret = std::min({ins,rep,del});
    }
};



// leetcode712

class Solution2 {
private:
    int memo[1001][1001];
public:
    inline int minimumDeleteSum(string s1, string s2)noexcept {
        memset(memo,-1,sizeof(memo));

        return minSum(s1,s2,0,0);
    }
    /*
        we have 4 states
        if both chars are equal we better to skip both
        delete from s1
        delete from s2
        delete from both

    */
    int minSum(string& s1 , string& s2 , int i , int j) noexcept
    {
        if(i == s1.size())
        {
            int sum = 0;
            for(; j < s2.size() ; ++j)
                sum+= s2[j];

            return sum;
        }
        else if(j == s2.size())
        {
            int sum = 0;
            for(; i < s1.size() ; ++i)
                sum+= s1[i];

            return sum;
        }
        auto& ret = memo[i][j];
        if(ret != -1)
            return ret;

        if(s1[i] == s2[j])
            return minSum(s1,s2,i+1,j+1);

        int del1{-1},del2{-1}; // no need to handle delete both

        del1 = (int)s1[i]+minSum(s1,s2,i+1,j);
        del2 = (int)s2[j]+minSum(s1,s2,i,j+1);

        return ret = min({del1,del2});
    }
};


int main(){

}
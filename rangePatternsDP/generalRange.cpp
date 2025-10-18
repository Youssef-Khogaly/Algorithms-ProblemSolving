#include <bits/stdc++.h>




using namespace std;

bool isPalid(const string& str , int start , int end)
{
    if(start >= end)
        return true;
    
    if(str[start] == str[end])
        return false;

    return isPalid(str,start+1,end-1);
}


class Solution {

    private:
    int memo[1001][1001];
    pair<int,int>ans{-1,-1};
    int longest = -1;
public:
    string longestPalindrome(string s) {
        memset(memo,-1,sizeof(memo));
        isPalid(s,0,s.size()-1);

        return s.substr(ans.first,ans.second-ans.first);
    }

    // longest palidrome sequence in this range
    int isPalid(const string& str , int start , int end)
    {
        if(start > end)
            return 0;
        if(start == end)
            return 1;
        auto & ret = memo[start][end];

        if(ret != -1)
            return ret;

        if(str[start] == str[end])
        {
            ret = 1+ isPalid(str,start+1,end+1);
            if(ret > longest){
                longest = ret;
                ans = {start,end};
            }
            return ret;
        }

        // my choices
        int startSkip = isPalid(str,start+1,end);
        int endSkip = isPalid(str,start,end-1);
        ret = max(startSkip , endSkip);
        if(ret > longest){
            longest = ret;
            ans = {start,end};
        }
        return ret;
    }
};





int main(){

    cout << isPalid("aza",0,2);
}
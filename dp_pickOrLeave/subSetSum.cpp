#include<bits/stdc++.h>





using namespace std;




int memo[501][2001];

/*
    result depend on current idx and target
*/
bool pickOrLeave(const vector<int>& arr , int idx , int target )
{
    if(target == 0)
        return true;
    if(idx == arr.size())
        return false;

    if(memo[idx][target] != -1)
        return memo[idx][target];

    bool pickit = pickOrLeave(arr,idx+1,target-arr[idx]);
    bool leaveit = pickOrLeave(arr,idx+1,target);
    return memo[idx][target] = (int)(pickit || leaveit);
}


// we need to know if there is a subseq its sum == target
bool subSetSum(const vector<int>& arr , int target)
{
    memset(memo , -1 , sizeof(memo));
    return pickOrLeave(arr,0,target);
}






int main()
{
    vector<int> test{3,12,4,12,5,2};

    cout << subSetSum(test,9) << endl;

    vector<int> test2{3,40,4,12,5,2};

    cout << subSetSum(test2,30) << endl;
}
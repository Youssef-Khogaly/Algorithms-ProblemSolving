#include<bits/stdc++.h>

using namespace std;



int itemSize[2000];
int itemVal[2000];

int cache[2000][2000];

int MaxCap;
int n;


// return the max profit
int knapsack(int idx , int remmainingCap) noexcept
{
    if(idx > n-1 || remmainingCap < 1)
        return 0;

    // if the sub problem computed before return it 
    if(cache[idx][remmainingCap] != -1 )
        return cache[idx][remmainingCap];
    int pickIt{0};
    int leaveIt{0};
    // pick it choice , profit
    // can i take it ?
    if(remmainingCap >= itemSize[idx])
        pickIt = itemVal[idx] + knapsack(idx+1,remmainingCap-itemSize[idx]);
    // leave it choice , profit
    leaveIt = knapsack(idx+1,remmainingCap);
    // return the maximum

    // cache the result of current sub problem
    return  cache[idx][remmainingCap] = std::max(pickIt,leaveIt);
}
int MaxVal() noexcept
{

    return knapsack(0,MaxCap);
}









int main()
{
    int S , N;
    cin >> S  >> N;
    MaxCap = S;
    n = N;
    memset(cache,-1,sizeof(cache));
    for(int i = 0 ; i < N ; ++i)
    {
        cin >> itemSize[i] >> itemVal[i];
    }

    cout << MaxVal();
}
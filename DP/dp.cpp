#include <bits/stdc++.h>







unsigned long int dp[100];

// top down approche
int fib(int n)
{
    if(n <= 1)
        return 1;
    if(dp[n] != 0)
        return dp[n];

    dp[n] = fib(n-1) + fib(n-2);
    
    return dp[n];
}
// bottom up approche
int fib_2(int n)
{
    if(dp[n] != 0)
        return dp[n];

    int i = n;

    // start from last computed number
    while(dp[i] == 0)
        --i;

    while(i != n)
    {
        dp[i+1] = dp[i] + dp[i-1];
        ++i;
    }

    return dp[n];
}

// o(1) memory
int fib_3(int n)
{
    if(n <= 1)
        return 1;

    int prev_1 = 1;
    int prev_2 = 1;
    int next;

    for(int i = 2 ; i <= n ; ++i)
    {
        next = prev_1 + prev_2;
        prev_1 = prev_2;
        prev_2 = next;
    }

    return next;
}







int main(){
    dp[0] = 1;
    dp[1] = 1;
}
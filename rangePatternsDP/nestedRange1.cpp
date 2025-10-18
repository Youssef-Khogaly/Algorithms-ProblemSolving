#include<bits/stdc++.h>



using namespace std;


class mat{
    public:
    int row;
    int col;
    mat(int row , int col) noexcept : row(row) , col(col) {

    }
};
vector<mat>arr = {{1,2},{2,3} , {3,4}};

int memo[100][100];
/*
    min cost to mutiple chain of matricies
    def:
    min cost to split the sub array [s to e]
*/
int mcm(int s , int e){
    
    if(s==e) // single matrix no multi
    {
        return 0;
    }
    auto& ret = memo[s][e];
    if(ret != 0)
        return ret;

    int minCost = 9999999999;
    int subBlock1 , subBlock2;
    int combiningCost = arr[s].row;
    for(int k = s ; k < e ; ++k) // k represent the idx to split
    {
        // cost of combining
        combiningCost =  arr[s].row * arr[k].col * arr[e].col;
        // solve for other
        subBlock1 = mcm(s,k);
        subBlock2 = mcm(k+1,e);
        /*
            result is the sum of the cost of the 2 block  + cost if mutipling the 2 blocks
            s to k 
            k+1 to e
            cost of combining

        */
        minCost = min(minCost , combiningCost+subBlock1+subBlock2);
    }


    return ret = minCost;
}








int main(){
    cout << mcm(0,arr.size()-1);

}
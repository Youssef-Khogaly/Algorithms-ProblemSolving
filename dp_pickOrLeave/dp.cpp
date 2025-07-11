#include <bits/stdc++.h>


using namespace std;


/*
    asume we have items each item have weight and value we need to pick 
    less than or equal the max weight and we need to get the max benefit
*/
int items_val[5] = {10,15,3,1,4};
int items_weight[5] ={10,4,20,5,7};


#define MAX_WEIGHT 12
vector<vector<int>>ans;
vector<int>temp;

// generate all cominations and  loop over every solution and pick the best brute force solution
void allGeneratedItem(int start ,vector<int>&current , vector<vector<int>>& ans)
{
    if(start >= 5)
    {
        return;
    }

    for(int i = start ; i < 5 ; ++i)
    {
        current.push_back(i);
        allGeneratedItem(i+1,current,ans);
        ans.push_back(current);
        current.pop_back();
    }
}

// optimized brute force version only keep generating if the current weight is less that or equal the max weight
void allGeneratedItem_2(int start ,int currentWeight ,vector<int>&current , vector<vector<int>>& ans)
{
    if(start >= 5 || currentWeight >= MAX_WEIGHT)
    {
        return;
    }

    for(int i = start ; i < 5 ; ++i)
    {
        currentWeight += items_weight[i];
        current.push_back(i);
        // if current weight already bigger that the max no need to try add more  to current answer
        // <= in case of item with 0 weight 
        if(currentWeight <= MAX_WEIGHT)
        {
            allGeneratedItem_2(i+1,currentWeight,current,ans);
            ans.push_back(current);
        }
        currentWeight -= items_weight[i];
        current.pop_back();
    }
}
bool sortDesc(const tuple<int,int,int>& a , const tuple<int,int,int>& b)
{
    return (a > b);
}

void Generation(int idx  , string& str)
{
    if(idx >= str.size())
    {
        cout << str << endl;
        return;
    }
    str[idx] = '0';
    Generation(idx+1,str);
    
    str[idx] = '1';
    Generation(idx+1,str);
    
}
void generateBinaryMasks(int n)
{
    string str;
    str.resize(n);
    fill(str.begin(),str.end(),' ');
    Generation(0,str);
}




int main()
{
    generateBinaryMasks(4);
    allGeneratedItem_2(0,0,temp,ans);
    /* now compute the val and weight of every possible*/
    vector<tuple<int,int,int>> val_weightIdxs(ans.size()); /* [0] = val , [1] = weight , [2] = sequence idx in the ans vector*/

    for(int i = 0 ; i < ans.size(); ++i)
    {
        int w = 0;
        int v = 0;
        for(auto& n : ans[i])
        {
            w += items_weight[n];
            v += items_val[n];
        }
        val_weightIdxs[i] = make_tuple(v,w,i);
    }

    /*now sort the val_weight_idx in desending order so the highest val will be in the */
    sort(begin(val_weightIdxs),end(val_weightIdxs),sortDesc);
    int ans_idx = -1;
    /* now find the highest val which verifiy the weight condiition ,, we can optimize it and apply binary search since its sorted btw */
    for(int i = 0 ; i < val_weightIdxs.size() ; ++i)
    {
        if(get<1>(val_weightIdxs[i]) <= MAX_WEIGHT)
        {
            cout << get<1>(val_weightIdxs[i]) << endl;
            ans_idx = get<2>(val_weightIdxs[i]);
            break;
        }
    }
    if(ans_idx != -1)
    {
        cout <<"Printing Answer\n";

        for(auto& n : ans[ans_idx])
        {
            cout << n <<" ";
        }

        cout <<"\n----------------------------------------------------------------------------\n";
    }
    /*
        print all possiblites
    */
    for(auto& vec : ans)
    {
        for(auto& n : vec)
            cout << n <<" ";

        cout << endl;
    }
}

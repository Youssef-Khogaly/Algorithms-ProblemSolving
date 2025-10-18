#include <bits/stdc++.h>





using namespace std;

int countarr[26];

bool isequal(string& a , string& b , int s1 , int e1 , int s2 , int e2)
{
    
    memset((void*)countarr,0,sizeof(countarr));

    for(int i = s1 ; i < e1+1 ; ++i)
        countarr[a[i]-'a']++;

    for(int j = s2 ; j < e2+1 ; ++j){
        if(countarr[b[j]-'a'] == 0)
            return false;
        
        countarr[b[j]-'a']--;
    }
    for(int i = 0 ; i < 26 ; ++i)
    {
        if(countarr[i] != 0)
            return false;
    }

    return true;
}
bool solve(string& a , string& b , int s1 , int e1 , int s2 , int e2)
{
    if(e1-s1 == 0 )
        return  a[s1] == b[s2];
    if(isequal(a,b,s1,e1,s2,e2) == false)
        return false;

    int mid = s1 + (e1-s1)/2;

    return (solve(a,b,s1,mid,s2,mid) && solve(a,b,mid+1,e1,mid+1,e2)) || (solve(a,b,s1,mid,mid+1,e2) && solve(a,b,mid+1,e1,s2,mid));

}
bool isEqu(string& a , string& b)
{
    if(a.size() != b.size())
        return false;
    
    if(isequal(a,b,0,a.size()-1,0,b.size()-1) == false)
        return false;
    int size1 = a.size()/2 - 1;
    return (solve(a,b,0,size1,0,size1) && solve(a,b,size1+1,a.size()-1,size1+1,b.size()-1)) ||(solve(a,b,0,size1,size1+1,b.size()-1) && solve(a,b,size1+1,a.size()-1,0,size1));
}




int main(){


    
}
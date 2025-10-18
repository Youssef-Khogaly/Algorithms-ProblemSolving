#include <bits/stdc++.h>

using namespace std;

void merge(int arr[], int s , int m , int e)
{
    int* ret = new int[7]{0};
    int l = s;
    int r = m+1;
    int it = 0;
    while(l <= m && r <= e)
    {
        if(arr[l] <= arr[r])
            ret[it++] = arr[l++];
        else
            ret[it++] = arr[r++];
    }
    while(l <= m)
        ret[it++] = arr[l++];

    while(r <= e)
        ret[it++] = arr[r++];
    it = 0;
    while(s <= e)
    {
        arr[s++] = ret[it++];
    }
}

void mergeSort(int arr[], int s , int e){
    if(s == e)
    {
        return;
    }
    int m = s + (e-s)/2;

    mergeSort(arr,s,m);
    mergeSort(arr,m+1,e);
    return merge(arr,s,m,e);
}


int main(){

    int arr[7]={12,26,35,87,7,9,28};
    int n = 7;

    mergeSort(arr,0,6);

    for(int i = 0 ; i < 7 ; ++i)
        cout <<arr[i] <<" ";

}
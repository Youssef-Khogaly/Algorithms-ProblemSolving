#include <bits/stdc++.h>

using namespace std;





int make_Partition(vector<int>& arr , int s,  int e)
{
    if(s == e)
        return s;
    int pivotIdx = s +(e-s)/2;
    int pivot = arr[pivotIdx];
    // move pivot to the end
    swap(arr[e],arr[pivotIdx]);
    int storeIdx = s;
    for(int i = s ; i <e ; ++i){
        if(arr[i] < pivot){
            swap(arr[i],arr[storeIdx]);
            storeIdx++;
        }
    }
    // move pivot to its right location
    swap(arr[storeIdx] , arr[e]);
    return storeIdx;
}

void quickSort(vector<int>& arr , int s, int e){
    if(s>=e) return;

    int pivot = make_Partition(arr,s,e);

    quickSort(arr,s,pivot-1);
    quickSort(arr,pivot+1,e);
}

/* support duplicates */

int make_Partition2(vector<int>& arr , int s,  int e)
{
    if(s == e)
        return s;
    int pivotIdx = s +(e-s)/2;
    int pivot = arr[pivotIdx];
    int count = 0;
    int biggerEqual = 0;
    int lessCount = 0;
    for(int i = s ; i < e+1 ; ++i){
        if(i != pivotIdx && arr[i] < pivot){
            ++count;
        }
        if(i < pivotIdx && arr[i] == pivot )
            ++lessCount;
        if(i > pivotIdx && arr[i] == pivot)
            biggerEqual++;
    }
    count += lessCount;
    swap(arr[count] , arr[pivotIdx]);
    pivotIdx = count;
    int low = s  , high = e;
    
    for(;low < pivotIdx && high > pivotIdx ;){
        while(low < pivotIdx && arr[low] < arr[pivotIdx])
            ++low;
        while(high > pivotIdx && arr[high] > arr[pivotIdx])
            --high;
        if(low < pivotIdx ){
            swap(arr[low] , arr[high]);
        }  
    }
    for(low = s ; low < pivotIdx && lessCount ; ++low)
    {
        if(arr[low] == pivot)
        {
            swap(arr[low] , arr[pivotIdx-lessCount]);
            --lessCount;
        }
    }
    int i;
    for(high = pivotIdx+1 ,  i = 1 ; high < e && biggerEqual ; ++high)
    {
        if(arr[high] == pivot)
        {
            swap(arr[high] , arr[pivotIdx+i]);
            --biggerEqual;
        }
    }
    return pivotIdx;
}

void quickSort2(vector<int>& arr , int s, int e){
    if(s>=e) return;

    int pivot = make_Partition2(arr,s,e);

    quickSort(arr,s,pivot-1);
    quickSort(arr,pivot+1,e);
}

int main(){
    
    vector<int> arr{6,6,4,5,6,7,1,1,0,6,3,3};
    quickSort2(arr,0,arr.size()-1);
    for(int& n : arr){
        cout << n << " ";
    }
}
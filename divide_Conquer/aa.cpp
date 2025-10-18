#include <bits/stdc++.h>


using namespace std;

class TimeMap {
private:
    unordered_map<string , set<pair<int,string>>> m;
    
public:
    TimeMap() noexcept : m(unordered_map<string , std::set<pair<int,string>>>{})   {
        
    }
    
    void set(string key, string value, int timestamp) {
        
    }
    
    string get(string key, int timestamp) {
        auto& s = m.at(key);
        s.key_comp
    }
};


void sort(vector<int>& arr)
{

    /*
    
        5 4a 4b 3 
        4a 5 4b 3
        4a 4b  5 3
        3 4a 4b 5
    */
    int tmp{};
    int i , j;
    for( i = 1 ; i < (int)arr.size() ; ++i)
    {
        tmp=arr[i];
        for( j = i-1 ; j > -1 && arr[j] > tmp ; ++j)
        {
            arr[j+1] = arr[j];
        }
        arr[j+1] = tmp;
    }
}


void SelectionSort(vector<int>& arr)
{
    int minIdx;

    for(int i = 0 ; i < arr.size() ; ++i)
    {
        minIdx = i;
        for(int j = i+1 ; j < arr.size() ; ++j)
        {
            if(arr[j] < arr[minIdx])
                minIdx = j;
        }
        if(i != minIdx)
            swap(arr[i],arr[minIdx]);
    }
}

int main()
{

}
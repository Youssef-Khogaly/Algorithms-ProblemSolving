#include <bits/stdc++.h>



template<typename T>
std::ostream& operator << (std::ostream& out , const std::vector<T>& vec)
{

    for(const auto & n : vec)
    out << n <<",";

    out << '\n';

    return out;
}

void swap(int& a , int& b)
{
    int temp = b;
    b = a;
    a = temp;
}


void insertionSortV1(std::vector<int>& vec )
{


    int key{};
    int i = 1 , j = 0;
    /*
    
        3 3 6
    */
    for(i = 1; i < vec.size() ; ++i)
    {
        int key = vec[i];
        for(j = i-1 ; j > -1 && vec[j] < key ; --j)
        {
            vec[j+1] = vec[j];
        }
        vec[j+1] = key;
    }
}


void insertionSortV2(std::vector<int>& vec )
{


    int key{};
    int i = 1 , j = 0;
    /*
    
        4,3,2,1

    */
    for(i = 1; i < vec.size() ; ++i)
    {
        for(j = i-1 ; j > -1 && vec[j] < vec[j+1] ; --j)
        {
            // using swap function is making insertion swort slower
            // since i do  2 extra copy operation in every iteration
            swap(vec[j+1],vec[j]);
        }
        
    }
}



/**
 * 
 *  1 <= array len <= 50000
 * 
 *  values range : -50000 <= arr[i] <= 50000
 * 
 */
std::vector<int> CountSortForNegative(const std::vector<int>& nums)
{
    using namespace std;
    int min = 50000;
    int max = -50000;
    for(const auto & n : nums)
    {
        if(n < min)
            min = n;
        if (n > max)
            max = n;
    }

    if(min >= 0)
        min = 0;
    if(max <= 0)
        max = 0;

    std::vector<int>negativeFreq(abs(min)+1);
    std::vector<int>Freq(abs(max)+1);
    std::vector<int>output;
    output.reserve(nums.size());

    for(const int & n : nums)
    {
        if(n < 0)
            ++negativeFreq[-n];
        else
            ++Freq[n];
    }
        
        for(int i = negativeFreq.size()-1 ; i > -1 ; --i)
        {
            while(negativeFreq[i] > 0)
            {
                output.push_back(-i);
                --negativeFreq[i];
            }
        }
        
        cout << "1\n";
        for(int i = 0 ; i < Freq.size() ; ++i)
        {
            while(Freq[i] > 0)
            {
                output.push_back(i);
                --Freq[i];
            }
        }
        cout << "2\n";
    return output;
}



/*
    -10^9 <= nums[i] <= 10^9

    max - min <= 500




    [-5,-4,-3,-2,-1]

    min = -5

    -5 - 

*/
std::vector<int>CountSortForRange(const std::vector<int> nums)
{
    std::vector<int>output;
    output.reserve(nums.size());
    int min = std::numeric_limits<int>::max();
    int max = std::numeric_limits<int>::min();
    for(auto & n : nums)
    {
        if(n < min)
            min = n;
        if(n > max)
            max = n;
    }
    int range = max - min;
    std::cout << range << std::endl;
    std::vector<int>freq(range+1);

    for(const auto & n : nums)
        ++freq[n-min]; // -min to shift values

    for(int i = 0 ; i < freq.size() ; ++i)
    {
        while(freq[i] != 0)
        {
            output.push_back(i+min); // +min to return shifted value to the original value
            --freq[i];
        }
    }
    return output;
}





using namespace std;
void CountSortStr(std::vector<string>& arr)
{

    vector<deque<string>>freq(26);
    
    for( auto & str: arr)
    {
        freq[str[0]-'a'].push_back(move(str));
    }

    int j = 0;
    for(int i = 0 ; i < 26 ; ++i)
    {
        while(freq[i].empty() == false)
        {
            arr[j++] = move(freq[i].front());
            freq[i].pop_front();
        }
    }


}

// hash for first 2 char of string for CountSortStr_v2
int chash(const string & str)
{

    return (str[0]-'a')*26 + ((str[1]-'a'));
}
void CountSortStr_v2(std::vector<string>& arr)
{

 

    vector<deque<string>>freq(676);
    
    for( auto & str: arr)
    {
        freq[chash(str)].push_back(move(str));
    }

    int j = 0;
    for(int i = 0 ; i < 676 ; ++i)
    {
        while(freq[i].empty() == false)
        {
            arr[j++] = move(freq[i].front());
            freq[i].pop_front();
        }
    }


}






/*

    stable count sort
    based on the accumlative sum of the freqs
*/

using namespace std;
vector<int> CountSort_stable(const vector<int>& arr) // assume all values >= 0
{
    int max = arr[0];
    vector<int>output(arr.size());
    for(const auto & n : arr)
    {
        if(n > max)
            max = n;
    }
    vector<int>freq(max+1);

    for(const auto & n : arr)
    {
        ++freq[n];
    }

    std::partial_sum(freq.begin(),freq.end(),freq.begin());

    for(int i = arr.size()-1 ; i >= 0 ; i--) // we start from the end bucsae the accumlated sum -1 is the idx of the last element
    {
        // now the idx of the value arr[i] in the output array
        // equal to the accumlated sum - 1
        int idx = freq[arr[i]] - 1;
        output[idx] = arr[i];
        --freq[arr[i]]; // decrement sice we already inserted this element in the output array
    }


    return output;
}


/*


[3,8,-10,23,19,-4,-14,27]

[-14 -10 -4 3 8 19 23 27]



*/
vector<vector<int>> minimumAbsDifference(vector<int>& arr) {

    vector<vector<int>>output;
    if(arr.size() == 2)
    {
        output.push_back(arr);
        return output;
    }
    output.reserve(arr.size());
    std::sort(arr.begin(),arr.end());
    int min_diff =numeric_limits<int>::max();
    for(int i = arr.size()-1 ; i > 0 ; --i)
    {
        int curr = abs(arr[i] - arr[i-1]);
        if(curr < min_diff)
            min_diff = curr;
    }
    
    for(int i = 0 ; i < arr.size()-1 ; ++i)
    {
        int diff = abs(arr[i+1]-arr[i]);

        if(diff == min_diff)
        {
            output.push_back({arr[i],arr[i+1]});
        }
    }

    return output;
}











// the sum of any two sides must be greater than third side
// but since we sort the array
// we can check if the sum of 2 smallest side greater than third or not
inline bool isTriangle(int a , int b , int c)
{
    if(a+b > c)
        return true;

    return false;
}


/*
    leet code 972

[1,2,1,10]

[1 1 2 10]
 a b c

 not triangle

 [1 1 2 10]
  a   b  c
  not triangle

  [1 1 2 10]
     a b  c
     not triangle
*/
int largestPerimeter(vector<int>& nums) {
    // sort to force first 2 element to be smallest sides
    // so we need only to check if first 2 sides samller that third 
    // instead of checking all comination
    sort(begin(nums),end(nums));

    // start from the end so first valid triangle we meet is the largest
    for(int i = nums.size()-1; i >1;--i)
    {
        if(isTriangle(nums[i-2],nums[i-1],nums[i]))
        {

            return nums[i-2]+nums[i-1]+nums[i];
        }
    }
    return 0;
}






/*
1 2 3 4 
1 + 3

[6 2 6 5 1 2]
1 2 2 5 6 6

1 + 2 + 6= 9

leetcode 561
*/
int arrayPairSum(vector<int>& nums) {
    std::sort(begin(nums),end(nums));
    int sum = 0;

    for(int i = 0 ; i < nums.size();i+=2)
    {
        sum += nums[i];
    }

    return sum;
}

/*

nums[i] <= nums[i+1] >= nums[i+2]
*/
void WiggleSort(vector<int>& nums) // o(nlogn) , o (n)
{
    std::vector<int>ans{};
    ans.reserve(nums.size());
    sort(begin(nums),end(nums));

    int min = 0 , max = nums.size()-1;
    for( ;min < max; ++min , --max)
    {
        ans.push_back(nums[min]);
        ans.push_back(nums[max]);
    }
    nums = std::move(ans);
}


void WiggleSort_2(vector<int>& nums) //(n)
{


    for(int i = 1 ; i < nums.size()-1 ; i+=2)
    {
        swap(nums[i] , nums[i+1]);
    }
}


/*

    leetcode 1921



    [1 4 3] , [1 1 1]

    [1 4 3]
*/
int eliminateMaximum(vector<int>& dist, vector<int>& speed) {
        
    int count = 1;
    vector<int>time;
    time.reserve(dist.size());
    for(int i = 0 ; i < dist.size() ; ++i)
    {
        // time the monster need to reach me
        double t = ceil((double)dist[i]/speed[i]);
        time.push_back(t);
    }

    sort(begin(time),end(time));
    for(int i = 1 ; i < time.size() ; ++i)
    {
        // -i bucase it the time i need to kill this monster
        time[i] -= i;
        if(time[i] > 0)
            count++;
    }
    return count;
}


/*

[8,-7,-3,-9,1,9,-6,-9,3]

k = 4
[9 9 6 7 1 3 8 9]

k = 1 , minidx=1 
[4 ,-2,3]

*/
int largestSumAfterKNegations(vector<int>& nums, int k) {
        

    CountSort(nums);
    int minIdx = 0;
    for(int i = 0 ; i < nums.size() && k;  --k)
    {
        if(abs(nums[i]) < abs(nums[minIdx])) // keep tracking of min absolute
                minIdx = i;

        if(nums[i] >= 0) // when we meet first postive value we don't need to continue
            break;       // since we can just keep fliping the min abolute we got it 
        else 
        {
            nums[i] = -nums[i];
            ++i;
        }
    }
    if(k & 1 == 1) // if remaning k is odd just flip the min once else no need to flip
        nums[minIdx] = -nums[minIdx];
    return accumulate(begin(nums),end(nums),0);
}


void CountSort(vector<int>& nums)
{
    #define Shift 100
    array<int,200+1>freq{};

    for(int i = 0 ; i < nums.size() ; ++i)
    {
        ++freq[nums[i] + Shift];
    }
    int j = 0;
    for(int i = 0 ; i < freq.size() ; ++i)
    {
        while(freq[i]> 0)
        {
            nums[j++] = i-Shift;
            --freq[i];
        }
    }
    return;
}


/*

    leetcode 581
*/
int findUnsortedSubarray(vector<int>& nums)  // o(nlong) , o(n)
{

    vector<int>temp(nums);

    sort(begin(temp),end(temp));

    int l = -1;
    int h = -1;

    for(int i = 0 , j = nums.size()-1 ; i < nums.size(); i++,--j)
    {
        if(l== -1 && nums[i] != temp[i])
            l = i;
        if(h == -1 && nums[j] != temp[j])
            h = j;
        if(l != -1 && h != -1)
            break;
    }

    if(l == -1 && h== -1)
        return 0;
    return (h-l+1);
}


int findUnsortedSubarray_2(vector<int>& nums) { // o(n) , o(1)

    if(nums.size() <= 1)
        return 0;
    int min_val = numeric_limits<int>::max();
    int max_val = numeric_limits<int>::min();
    int start = 0;
    int end = nums.size()-1;
    bool sorted = true;
    // get the start where order break
    for(int i = 0 ; i < nums.size()-1 ; ++i)
    {
        if(nums[i] > nums[i+1])
        {
            start = i;
            sorted = false;
            break;
        }
    }
    if(sorted) // already sorted
        return 0;
    // get the end
    for(int i = nums.size()-1 ; i > 0 ; --i)
    {
        if(nums[i] < nums[i-1])
        {
            end = i;
            break;
        }
    }


    // get the min and max of the sub array
    for(int i = start ; i <= end ; ++i)
    {
        if(nums[i] < min_val)
            min_val  = nums[i];
        if(nums[i] > max_val)
            max_val = nums[i];
    }
    // now check if the min is bigger than the all values that before the start of current sub array
    // if not then expand the left boundry
    for(int i = start-1 ; i > -1 ; --i)
    {
        if(nums[i] > min_val)// its my new start
        {
            start = i; // expand the left boundry
        }
    }

    // now check if the max is less than all values after the end of the current sub array
    for(int i = end+1 ; i < nums.size() ; ++i)
    {
        if(max_val > nums[i])
        {
            end = i; // expand the right boundry
        }
    }
    return end-start +1;
}


int findUnsortedSubarray_3(vector<int>& nums) { // o(n) , o (1) but shorter and cleaner than _2

    if(nums.size() <= 1)
        return 0;
    int max_val = numeric_limits<int>::min();
    int min_val = numeric_limits<int>::max();
    int start = -1;
    int end = -1;
    for(int i = 0 ; i < nums.size() ; ++i)
    {
        max_val = max(max_val,nums[i]);
        if(nums[i] < max_val)// that's mean this location maybe the end of the shortest sub array
            end = i;
    }

    // repeat the same process but from end to start to get the start
    for(int i = nums.size()-1 ; i> -1 ; --i)
    {
        min_val = min(min_val,nums[i]);
        if(nums[i] > min_val) // that's mean this location maybe the start of the shortest sub array
            start = i;
        
    }
    if(end == -1)
        return 0;
    return end-start+1;
}


/*
    leet code 826
*/
int maxProfitAssignment(vector<int>& difficulty, vector<int>& profit, vector<int>& worker) {
    priority_queue<pair<int,int>> heap; // profit , difficulty
    for(int i = 0 ; i < difficulty.size();++i)
        heap.push({profit[i] , difficulty[i]});

    sort(begin(worker) , end(worker) , [](int a , int b) ->bool {return b<a;});
    int sum = 0;
    for(int i = 0 ; i < worker.size() && !heap.empty() ;)
    {

        if(worker[i] >= heap.top().second)
        {
            sum += heap.top().first;
            ++i;
        }
        else
        {
            heap.pop();
        }
    }

    return sum;
}



/*
    leet code 1887


    // each time reach new number increase number of operation needed to get it to the min 
    and keep summing
op = 2 , sum = 3
     [1 3 5]
        1  2
op = 2 , sum = 4
    [1 1 2 2 3]
op   0 0 1 1 2
*/
int reductionOperations(vector<int>& nums) {

    int sum = 0;
    sort(begin(nums),end(nums));
    int min_val = nums[0];
    int operations{0};
    for(int i = 1 ; i < nums.size() ; ++i)
    {
        if(nums[i] != nums[i-1])
            ++operations;

       sum += operations;
    }
    
    return sum;
}
int main()
{

    using namespace std;

    std::vector<int> vec {-2,3,-5};
/*
    insertionSortV2(vec);
*/
    //cout << CountSortForNegative({0,0,1,5,9,-10});



    //cout << CountSortForRange({-400,0,-5,99});
  //  cout << CountSortForRange({10000107,10000035,10000001});
   // cout << CountSortForRange({-10000107,-10000035,-10000001});

    //std::vector<string> arr{"ziad","belal","adam","baheir", "ali"};
    //CountSortStr(arr);
    /*
    std::vector<string> arr{"axz","axa","zzz","abc", "abe"};
    CountSortStr_v2(arr);
    cout << arr;


    cout << CountSort_stable({9,5,3,9,5,9,7}) << endl;
*/
    vector<int>v{3,5,2,1,6,4};

    WiggleSort(v);
    cout << v << endl;
    return 0;
}

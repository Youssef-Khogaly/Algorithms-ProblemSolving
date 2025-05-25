#include <bits/stdc++.h>
#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>
#include<cmath>
#include<iomanip>

namespace leetCode_34
{
    using namespace std;
    int myLowerBound(vector<int>& nums , int target)
    {
        int low = 0 , high  = (int)nums.size() - 1;
        int middle = 0;
        while(low < high)
        {
            middle = low + (high-low)/2;
            if(target > nums[middle])
            {
                low = middle+1;
            }
            else if (target < nums[middle])
                high = middle-1;
            else
                high = middle; // search window to the left to make sure to find first element
        }
        if(low < 0 || low > nums.size()-1) // we didnot found it
            return -1;
        if(nums[low] != target) // we didnot found it
            return -1;
        return low;
    }
        int myUpperBound(vector<int>& nums , int target)
    {
        int low = 0 , high  = (int)nums.size() - 1;
        int middle = low + (high-low)/2;
        while(low < high)
        {
            /* 
            +1 here because if two target element are consuctive  when we update the low to be the middle will go infinte loop
            assume
            idx 5 6 , target = 7
            arr 7 7
            midd = 5
            again low = mid
            idx 5 6
            arr 7 7
            mid = 5
            INF LOOP!!!!
            */
            middle = low + (high-low + 1)/2; 
            if(target > nums[middle])
                low = middle+1;
            else if(target < nums[middle])
                high = middle-1;
            else
                low = middle ; // search window to the right to make sure to find last element
        }

        if(low < 0 || low > nums.size()-1)
            return -1;
        if(nums[low] < target)
            return -1;

        return low;
    }
    // better solution no edge cases and weird tricks , not pos conditions
    int myLowerBound2(vector<int>& nums , int target)
    {
        int low = 0 , high  = (int)nums.size() - 1;
        int pos = -1;
        int middle = 0;
        while(low <= high)
        {
            middle = low + (high-low)/2;
            if(target > nums[middle])
            {
                low = middle+1;
            }
            else if (target < nums[middle])
                high = middle-1;
            else
                high = middle-1 , pos = middle; 
        }
        return pos;
    }
        int myUpperBound2(vector<int>& nums , int target)
    {
        int low = 0 , high  = (int)nums.size() - 1;
        int middle = low + (high-low)/2;
        int pos = -1;
        while(low <= high)
        {
            middle = low + (high-low + 1)/2; 
            if(target > nums[middle])
                low = middle+1;
            else if(target < nums[middle])
                high = middle-1;
            else
                low = middle + 1 , pos = middle ; // search window to the right to make sure to find last element
        }
        return pos;
    }
    vector<int> searchRange(vector<int>& nums, int target) {
        vector<int>ret{-1,-1};

        ret[0] = myLowerBound(nums,target);
        if(ret[0] == -1)
            return ret;
        
        ret[1] = myUpperBound(nums,target);

        return ret;
    }
}


namespace leetCode_436
{
    using namespace std;
    struct cmp{

        bool operator()(const pair<int,int>&a , const pair<int,int>&b)
        {
            return a.first < b.first;
        }
    };
    int MyUpperBound2(const vector<pair<int,int> > & vec, int target)
    {
        int low = 0 ,  high = (int)vec.size()-1;
        int middle = low + (high-low)/2;
        while(low <= high)
        {
            /*
            1 2 3 13 15 16
            0 1 2  3  4  5 
            target = 14

            1 2 4
            0 1 2
            target = 3
            */
            if(target == vec[middle].first)
            {
                return vec[middle].second;
            }
            else if (target <= vec[low].first)
            {
                return vec[low].second;
            }   
            else if (target < vec[middle].first)
            {
                high = middle -1;
            }
            else
            {
                low = middle +1;
            }
            middle = low + (high-low)/2;
        }

        if(middle < vec.size() &&  vec[middle].first > target)
            return vec[middle].second;
        
        return -1;
    }
    vector<int> findRightInterval(vector<vector<int>>& intervals) {
        vector<pair<int,int>>Starts{}; // start , i
        Starts.reserve(intervals.size());
        for(int i = 0 ; i < intervals.size() ; ++i)
        {
            Starts.push_back({intervals[i][0] , i});
        }
        std::sort(begin(Starts) , end(Starts) , cmp());
        vector<int>ret(intervals.size());
        ret.reserve(intervals.size());

        for(int i = 0 ; i < intervals.size() ; ++i)
        {
            if(intervals[i][1] == intervals[i][0])
            {
                ret[i] = i;
            }
            else
                ret[i] = MyUpperBound2(Starts,intervals[i][1]);
        }

        return ret;
    } 


    // stl solution
}


namespace leetcode_611
{
    using namespace std;
    void countSort(vector<int>& nums)
    {
        vector<int>count(1001 , 0);
        for(const auto & n :nums)
        {
            ++count[n];
        }
        int j = 0;
        for(int i = 0 ; i < 1001 ; ++i)
        {
            while(count[i] != 0)
            {
                nums[j++] = i;
                --count[i];
            }
        }
    }

    int LowerBound2(int low , int high  , const vector<int>& nums , int target)
    {
        int middle = low + (high-low)/2;

        while(low <= high && high < nums.size())
        {
            if(nums[middle] >= target)
            {
               high =  middle -1;
            }
            else
                low = middle+1;

            middle = low + (high-low)/2;
        }
        return low;
    }
    int triangleNumber2(vector<int>& nums) {
        if(nums.size() < 3)
            return 0;

        countSort(nums);
        int count = 0;
        for(int i = 0 ; i < nums.size()-2 ; ++i) //o(n)
        {
            

            // skip zeros
            if(nums[i] == 0)
                continue;

            int third_idx = i+2;
            for(int j = i+1 ;  j < nums.size()-1 ; ++j) // o(nlogn)
            {
                if(nums[j] == 0)
                    continue; // skip zeros
                if(third_idx == j)
                    third_idx = j+1;
                third_idx =  LowerBound2(third_idx,nums.size()-1,nums,nums[j]+nums[i]);

                count += third_idx - j - 1;
            }
        }

        return count;
    }
}

namespace LeetCode441
{
/*

n = 5

low = 1 , high = 5

number of coin needed to be this row complete =  r*(r+1) / 2

mid = 3
nOfCoin = 6 not complete go left

low = 1 high = 2
mid = 1
nOfCoin = 1 complete go right

low = 2 , high = 2
mid = 2
nOfCoins = 3 complete go right

low = 3 , high = 2
break
return low-1

*/
int arrangeCoins(int n) {
    if(n <= 2)
        return 1;
    uint64_t low = 1 , high = n;
    uint64_t middle;
    while(low <= high)
    {
        middle = low+(high-low)/2;
        // number of coins must n be greater than or equal to be this row and all previous row completed
        uint64_t nOfCoinsNeeded = middle *(middle+1) / 2; 
        if(nOfCoinsNeeded > n) // not complete go left
        {
            high = middle-1;
        }
        else
        {
            low = middle+1;
        }
    }

    return low-1;
}
}



namespace leetcode1283{
/*
[1 2 5 9]

low = 1 , high = 9
mid = 5

sum = [1 1 1 2] = 5 , last = 5
check if there is a smaller value in my left

low = 1 high = 4

mid = 2

sum = [1 1 3 5] = 10

low = 3 high = 4
mid = 4
sum = [1 1 2 3] = 7
low = 5 high = 4

return low

----------

low = 1 high = 44

mid = 22

[2 1 2 1 1] = 7

low = 22+1=23 , high = 44
mid = 33
[2 , 1 , 1 , 1 ,1] = 6


low = 34 , high = 44

mid = 39


*/
using namespace std;
int smallestDivisor(vector<int>& nums, int threshold) {
        
    int low = 1 , high = 0;
    int mid;
    for(auto& n : nums){
        if(n > high)
            high = n;
    }
    while(low <= high){

        mid = low + (high-low)/2;
        int sum = 0;
        // compute sum
        for(auto& n : nums)
            sum += (ceil(n/(double)mid));

        if(sum > threshold){
            low = mid+1;
        }
        else if (sum <= threshold){
            high = mid-1;
        }
    }

    return low;
}
}

namespace leetcode1482{
/*


low = 1 , high = 10

mid = 5

i can make 3 pockets at  day 5

low = 1 high = 4
mid = 2
i can make 2 pockets only

low = 3 high = 4
mid = 3
i can make 3 pockets
low = 3 high = 3
mid = 3

return 3

i can start from the min to the max to optimize searching

*/
using namespace std;
int countPockets(vector<int>& bloomDay , int day , int k){
    
    int count = 0;
    int adj = 0;
    for(int& d : bloomDay)
    {
        if(d-day <= 0){
            adj++;
            if(k - adj == 0)
            {
                ++count;
                adj = 0;
            }
        }
        else
            adj = 0;
    }

    return count;
}
int minDays(vector<int>& bloomDay, int m, int k) {
    if((uint64_t)k*m > (uint64_t)bloomDay.size())
        return -1;

    int low = *min_element(begin(bloomDay),end(bloomDay));
    int high = *max_element(begin(bloomDay),end(bloomDay));
    int mid;
    int pockets;

    while(low <= high){
        mid = low + (high-low)/2;

        pockets = countPockets(bloomDay,mid,k); // o(n) , o(n)memory

        if(pockets >= m ){
            high = mid-1;
        }
        else
            low = mid+1;
    }

    return low;
}
}


namespace leetcode475{

    using namespace std;
/*

iterate of every house
and find the closest heater to the house
and calculate the distance

keep tracking of the maxmimum distance
its the answer
*/

int findRadius(vector<int>& houses, vector<int>& heaters) {
    int housesSize = houses.size();
    int low = 0 ; 
    int high = heaters.size();
    int mid;
    int minDistance = 0;
    sort(heaters.begin(),heaters.end());
    for(int& house : houses){
        low = 0 ; 
        high = heaters.size()-1;
        int closestDist = INT_MAX;
        while(low <= high){
            mid = low + (high-low)/2;
            closestDist = min(closestDist , abs(house-heaters[mid]));
            if(house == heaters[mid])
            {
                low = mid;
                break;
            }
            else if(heaters[mid] > house)
                high = mid - 1;
            else
                low = mid + 1;;
        }

        minDistance = max(minDistance ,closestDist);
    }


    return minDistance;

}

}


namespace leetcode1060{

    using namespace std;
    /*
        [4,7,9,10]

        i = 1
        arr[i] == arr[i-1]+1 ? no 
        number of missing elements is 
        7-4 - 1 = 2 elements
        2 >= k ?
        return arr[i-1]+k
        else
        decrement k -= 2
        repeat till the Missing between current and prev bigger than k
        then the answer will be the previous number +k
    
         
    */
    int missingElement(vector<int>& nums , int k) // o (n)
    {

        int countMissing = 0;
        for(int i = 1 ; i < (int)nums.size() ; ++i){

            if(nums[i] != nums[i-1]+1){
                countMissing = nums[i]-nums[i-1]-1;

                if(countMissing >= k){
                    return nums[i-1]+k;
                }
                else
                    k -= countMissing;
            }

        }

        return nums.back()+k;
    }



    /*

        [4 7 8 9]

    assume that at arr[3] number of missing elemnts are 7

    then arr[4] number of missing elements must be at least 7

    how to compute number of missing?

    if the start is 4
    then in idx 2 is 8? while it should be 4+2 = 6
    and there is 5 6 is missing

    assume we at idx 3 arr[3] = 9
    number of missing 5 6 

    number of missing = arr[i]-arr[0]-i

    countMissing > k ? go left

    coutMissing > k go left to get first element

    countMissing < k go right
    low = 1 , high = 3
    mid = 4/2 = 2

    countMissing(2) = 2
    >= k
    break;

    return arr[mid-1]+k;

    */
   int CountMissing(vector<int>& nums , int i ){

        return (nums[i]-nums[0]-i);
   }
    int missingElement_2(vector<int>& nums , int k) // o (log n )
    {

        int low = 1 , high = (int)nums.size()-1;
        int mid = 0;
        int lowerBound = -1;
        if(CountMissing(nums , high) < k){
            return nums.back()+k -(CountMissing(nums , high));
        }
        while(low <= high){
            mid = low + (high-low)/2;

            if(CountMissing(nums,mid) >= k) // go left
            {
                lowerBound = mid;
                high = mid-1;
            }
            else{
                low = mid+1;
            }
        }
        return nums[lowerBound-1]+k;
    }
}

namespace leetCode668{

    using namespace std;
/*
m = 3 , n = 3

table of  m = 1
1 , 2 , 3
table of  m = 2
2 , 4 , 6

table of m = 3
3 , 6 , 9

sort
m=  1 1 2 1 3 2 2 3 3
    1 2 2 3 3 4 6 6 9
idx 0 1 2 3 4 5 6 7 8
n=  1 2 1 3 1 2 3 2 3


assume we have a function(vale , m ,n) return how many numbers less than val in 
m*n table

so if we developed this function we can apply lower bound binary search to get 
first value function(val,m,n) >= k

so how to develop this function ????????
we can brute force it but we will get a time limit





    since searching is logn and counting is n*m to optimize the solution
    we need to find a better way to  count how many numbers less  than or equal
    value in the table

    we can brute force on m only

    we check every row

    value / row = how many numbers less than or equal value
    and if value/row > cols then the value is bigger than all values in the row
    
    so iterate of all rows
    and get min(value/row,cols)
*/


    /*
    
    brute force count how many number are less than or equal value in the table

    */
   int Count_len(int val , int m , int n){

    int count = 0;

    for(int i = 1 ; i <= m ; ++i){
        if(i > val)
            break;
        for(int j = 1 ; j <= n ; ++j){

            if(i*j <= val)
                ++count;
            else
                break;
        }
    }

    return count;
}


inline int Count_len_2(int& val , int& m , int& n) // optimized version o(m)
{
    int count = 0;
    // how many number <= val in each row
    // 
    for(int i = 1 ; i <= m ; ++i){
        count += min(val/i ,n);
    }
    return count;
}
int findKthNumber(int m, int n, int k) { // o(mlog(n*m)) , memory o(1)
    
    int low = 1 , high = m*n;
    int mid;
    int lowerBound = -1;
    while(low <= high){
        mid = low + (high-low)/2;
        if(Count_len_2(mid,m,n) >= k){
            high = mid-1;
            lowerBound = mid;
        }
        else
            low = mid+1;
    }

    return lowerBound;
}
}


double f(double x){

    using namespace std;

    return (4.0 *pow(x,7)) + (3*pow(x,5)) - 1000.0;
}

int dCmp(double a , double b , double absol){

    double diff = std::fabs(a-b);
    if (diff > absol){
        return 1; // a > b
    }
    else if (diff < absol)
        return -1; // a < b

    return 0; // equal

}
double solve(double result){

    double low = 0.0 , high = 3.0;
    double mid ;
    double EPS = 1e-12;
    while(high-low > EPS){
        mid = low + (high-low)/2.0;

        if(f(mid) - result > EPS ){
            high = mid;
        }
        else{
            low = mid;
        }
    }
    return low;
}



namespace leetcode69{

    /*
x = 8
low = 1 , high = 8
mid = 4

4*4 = 16 
16 > x
low = 0 , high = 3
mid = 1
1*1 = 1
1 < x
low = 2 , high = 3
mid = 2
2*2 = 4
4 < x
low = 3 , high = 3
mid = 3
9>x
low = 3 , high = 2

then the result is low -1
but we need to handle x = 0 case

*/

class Solution {
public:
    int mySqrt(int x) {
        if(x == 0 || x== 1)
            return x;
        uint64_t low = 1 , high = x/2;
        uint64_t mid;
        while(low <= high){
            mid = low + (high-low)/2;
            if(mid * mid > x)
                high = mid-1;
            else
                low = mid+1;     
        }

        
        return low-1;
    }
};
}



/*
https://www.spoj.com/problems/PIE/
*/
namespace PIE{

using namespace std;


double circle_area(double r) {

    const double PI = acos( -1.0);
      return PI * r * r;
     }
    

    /*
        low = 3 , high = 4

        mid = 3.5 area = 38.465

        is valid area?
        how to check that. if there is N radius can provide this area then its valid (N == number of people)

        if not valid area
        just make then its too big makes it smaller by setting high = mid

        if its valid 
        we need to make sure that there is no bigger valid area
        set low = mid and keep traking of last valid area
    
    */

     bool isValidArea(vector<double> &pie_radius,double area , int people){

        
        for(auto& r : pie_radius){
            
            double currArea = circle_area(r);
           if (currArea + 1e-12 >= area){
                people--;
            }
            if(people == 0)
                break;
        }

        return (people == 0);
     }
     double largest_area(vector<double> &pie_radius, int people) {

        double low = 0;
        double high = *max_element(begin(pie_radius) , end(pie_radius));
        high = circle_area(high);
        double mid;
        double last = high;
        for(int i = 0 ; i < 100 ; ++i)
        {
            mid = (high+low)/2;
            if(isValidArea(pie_radius , mid , people)){
                last = mid;
                low = mid;
            }else{
                high = mid;
                
            }
        }
        return last;
    }
}
//https://www.spoj.com/problems/GLASNICI/
namespace PIE_SPOJGLASNICI{

    using namespace std;
/*

[0,4,4,8]

assume time = 2 , max number of steps = 2
msg dist = 2
[2,4,6, 8]
valid time

--------
time = 1 , number of steps = 1
msg dist = 2

[1,3,6,8]
valid

--------
time = 0.5 , number of steps = 0.5
msg dist = 2

[0.5,3.5,4,8]

--------
[0,9,18] , msg dist = 5


low = 0 , high = 9

time = 4.5
is valid ?:
[4,9,18]



*/

bool isValidTime(vector<double>& pos ,double msg_dist ,double maxStepToMove){

    double lastPos = pos[0]+maxStepToMove;// previous persion postion
    double lastMsgPos; // the max postion of the message to be heared
    double currPos; 
    for(int i = 1 ; i < (int)pos.size(); ++i){
        lastMsgPos = lastPos+ msg_dist;
        currPos = pos[i];

        /*
            if current person postion bigger that the msg postion
            we need to move it back so he can hear the message
            at the same time we want him to be close as possible to the msg so he can hear it and shout it more distance to the next persion
        */
        if(currPos > lastMsgPos){

            currPos = max(lastMsgPos,currPos-maxStepToMove);
        }
        /*
            if current persion pos before the maxmium distance to hear the message
            we need to move him to the maxmum distance to hear the message so he can shout it for more distance to the next person
        */
        else if ( currPos <= lastMsgPos){
            currPos = min(lastMsgPos,currPos+maxStepToMove);
        }
        /*
            if after moving the current person still can't hear the message
            so its not valid time
        */
        if(currPos > lastMsgPos)
            return false;
        
        lastPos = currPos;
    }

	return true;
}
double min_time(vector<double> &positions, double msg_dist) {
	// TODO fill this function

	if(positions.front()+msg_dist > positions.back())
		return 0;
	double high = (positions.back() - positions.front())/2;
	double low = 0;
	double mid;
	double lowerBound = high;
	for(int i = 0 ; i < 100 ; ++i){

		mid = low + (high-low)/2;
		if(isValidTime(positions,msg_dist,mid)){
			high = mid;
			lowerBound = mid;
		}else{
			low = mid;
		}
	}

	return lowerBound;
}
}
int main()
{
    using namespace std;
    vector<double> Postions{0,4,4,8};
    double msgDist = 2;
    cout << fixed;
    cout << setprecision(2)<<PIE_SPOJGLASNICI::min_time(Postions,msgDist);

}
// https://www.spoj.com/problems/PIE/

#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>
#include<cmath>
#include<iomanip>
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
	 	and count how many people can be served by each radius if we choseed this area" till people need to be served is 0


        if not valid area
        just make then its too big makes it smaller by setting high = mid

        if its valid 
        we need to make sure that there is no bigger valid area
        set low = mid and keep traking of last valid area
    
    */

     bool isValidArea(vector<double> &pie_radius,double area , int people){

        int count = 0;
        for(auto& r : pie_radius){
            
            double currArea = circle_area(r);
           count += (currArea/area); // how many people can eat from current area
		   if(count >= people)
				break;
        }

        return (count >= people);
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

int main() {
	int cases, n, f;
	cin >> cases;

	while (cases--) {
		cin >> n >> f;
		vector<double> pie_radius(n);

		for (int i = 0; i < n; i++)
			cin >> pie_radius[i];

		double area = largest_area(pie_radius, f + 1);	// +1 for the host person

		cout << fixed;
		cout << setprecision(4) << area << "\n";
	}
	return 0;
}

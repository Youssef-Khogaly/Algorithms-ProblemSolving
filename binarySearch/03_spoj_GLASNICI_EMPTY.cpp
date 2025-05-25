// https://www.spoj.com/problems/GLASNICI/

#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>
#include<cmath>
#include<iomanip>
using namespace std;

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
int main() {
	int cases, n;
	double msg_dist;
	cin >> cases;

	while (cases--) {
		cin >> msg_dist >> n;
		vector<double> positions(n);

		for (int i = 0; i < n; i++)
			cin >> positions[i];

		double time = min_time(positions, msg_dist);

		cout << fixed;
		cout << setprecision(2) << time << "\n";
	}
	return 0;
}


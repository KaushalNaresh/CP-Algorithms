#include<bits/stdc++.h>

using namespace std;

// Definition of Interval:
class Interval {
public:
    int start, end;
    Interval(int start, int end) {
        this->start = start;
        this->end = end;
    }
};
 

class Solution {
public:

    static bool comp(Interval i1, Interval i2){
        return i1.start < i2.start;
    }
    /**
     * @param intervals: an array of meeting time intervals
     * @return: the minimum number of conference rooms required
     */
    int minMeetingRooms(vector<Interval> &intervals) {
        // Write your code here
        sort(intervals.begin(), intervals.end(), comp);
        vector<int> endTimes;

        for(int i = 0; i < intervals.size(); i++){
            int j;
            for(j = 0; j < endTimes.size(); j++){
                if(intervals[i].start >= endTimes[j]){
                    endTimes[j] = max(intervals[i].end, endTimes[j]);
                    break;
                }
            }
            if(j == endTimes.size())
                endTimes.push_back(intervals[i].end);
        }

        return endTimes.size();
    }
};

int main(){

    vector<Interval> intervals = {Interval(0, 30), Interval(5, 10), Interval(15, 45)};
    Solution* sol = new Solution();

    cout<<sol->minMeetingRooms(intervals);
}
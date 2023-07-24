#include<bits/stdc++.h>
using namespace std;

class Solution {
public:

    int maxEvents(vector<vector<int>>& events) {
        
        sort(events.begin(), events.end());
        int n = events.size(), i = 0, count = 0, curr_day = events[0][0];

        priority_queue<int, vector<int>, greater<int>> pq;

        while(i < n){

            while(i < n && events[i][0] == curr_day){
                pq.push(events[i][1]);
                i++;
            }

            pq.pop();
            count++;
            curr_day++;

            while(!pq.empty() && pq.top() < curr_day)
                pq.pop();

            if(pq.empty() && i < n)
                curr_day = events[i][0];
        }

        while(!pq.empty()){

            if(pq.top() >= curr_day){
                count++;
                curr_day++;
            }
            pq.pop();
        }

        return count;
    }
};

// [1,3] [2,2] [2, 5] [3, 3]
// [1, 3] [2, 3] [3, 5]
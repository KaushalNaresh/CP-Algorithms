#include<bits/stdc++.h>
using namespace std;

vector<vector<pair<int, int>>> schedules;

struct compare{

    bool operator()(pair<int, int> p1, pair<int, int> p2){

        vector<pair<int, int>> schedule1 = schedules[p1.second];
        vector<pair<int, int>> schedule2 = schedules[p2.second];

        int end1 = schedule1[p1.first].second;
        int end2 = schedule2[p2.first].second;

        return end1 > end2;
    }
};

bool overlap(pair<int, int> p1, pair<int, int> p2){

    pair<int, int> interval1 = schedules[p1.second][p1.first];
    pair<int, int> interval2 = schedules[p2.second][p2.first];

    return interval2.first <= interval1.second;
}

pair<int, int> getFreeTime(pair<int, int> p1, pair<int, int> p2){

    pair<int, int> interval1 = schedules[p1.second][p1.first];
    pair<int, int> interval2 = schedules[p2.second][p2.first];

    return {interval1.second, interval2.first};
}

int main(){

    int k, strt, end, n;
    cout<<"Enter number of schedules : ";
    cin>>k;

    priority_queue<pair<int, int>, vector<pair<int, int>>, compare> pq; // {interval in particular schedule, schedule number}

    for(int i = 0; i < k; i++){
        cout<<"Enter number of intervals for schedule-"<<i<<" : ";
        cin>>n;
        vector<pair<int, int>> schedule = {};
        for(int j = 0; j < n; j++){
            cout<<"Enter start and end time"<<endl;
            cin>>strt>>end;
            schedule.push_back({strt, end});
        }
        schedules.push_back(schedule);
        pq.push({0, i});
    }

    // for(int i = 0; i < schedules.size(); i++){
    //     for(int j = 0; j < schedules[i].size(); j++){
    //         cout<<schedules[i][j].first<<"-"<<schedules[i][j].second<<" ";
    //     }
    //     cout<<endl;
    // }
    
    pair<int, int> prev = {-1, -1};

    vector<pair<int, int>> free_times;

    while(!pq.empty()){
        
        pair<int, int> curr = pq.top();
        
        if(prev.first != -1){
            pq.pop();

            if(!overlap(prev, curr))
                free_times.push_back(getFreeTime(prev, curr));

            if(curr.first < schedules[curr.second].size()-1)
                pq.push({curr.first+1, curr.second});
        }

        prev = curr;
    }

    cout<<"Free-times are : "<<endl;
    for(int i = 0; i < free_times.size(); i++)
        cout<<free_times[i].first<<"-"<<free_times[i].second<<endl;
}
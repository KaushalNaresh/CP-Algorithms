#include<bits/stdc++.h>
using namespace std;

struct compare{

    bool operator()(pair<int, pair<int, int>> p1, pair<int, pair<int, int>> p2){
        return p1.first > p2.first; // min_heap
    }
};

static bool compare_sort(vector<int> v1, vector<int> v2){
    return v1[0] < v2[0];
}

int main(){

    vector<vector<int>> jobs;
    int n, strt, end, load, max_load = INT_MIN, curr_load = 0;

    // {end_time, {start_time, load}}
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, compare> pq;

    cin>>n;

    for(int i = 0; i < n; i++){
        cin>>strt>>end>>load;
        jobs.push_back({strt, end, load});
    }

    sort(jobs.begin(), jobs.end(), compare_sort);

    for(int i = 0; i < n; i++){

        int j;
        while(!pq.empty()){
            
            int end_time = pq.top().first;
            int start_time = pq.top().second.first;
            int load = pq.top().second.second;

            if(end_time <= jobs[i][0]){
                curr_load -= load;
                pq.pop();
            }
            else
                break;
            
        }

        pq.push({jobs[i][1], {jobs[i][0], jobs[i][2]}});
        curr_load += jobs[i][2];

        if(max_load < curr_load)
            max_load = curr_load;
    }

    cout<<max_load<<endl;
}
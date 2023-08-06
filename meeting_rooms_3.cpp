#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int mostBooked(int n, vector<vector<int>>& meetings) {
        
        sort(meetings.begin(), meetings.end());

        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> endTime_room;
        priority_queue<int, vector<int>, greater<int>> notEngaged;
        vector<int> count(n, 0);

        endTime_room.push({meetings[0][1], 0});
        for(int i = 1; i < meetings.size(); i++)
            notEngaged.push(i);
        
        count[0] = 1;

        long long end = 0, room = 0;

        for(int i = 1; i < meetings.size(); i++){

            while(!endTime_room.empty() && endTime_room.top().first <= meetings[i][0]){
                end = endTime_room.top().first;
                room = endTime_room.top().second;
                endTime_room.pop();
                notEngaged.push(room);
            }
            
            if(endTime_room.size() < n){
                end = end <= meetings[i][0] ? meetings[i][0] : end;
                endTime_room.push({end+meetings[i][1]-meetings[i][0], notEngaged.top()});
                count[notEngaged.top()]++;
                notEngaged.pop();
            }
            else{

                room = endTime_room.top().second;
                end = endTime_room.top().first;
                endTime_room.pop();
                notEngaged.push(room);
                end = end <= meetings[i][0] ? meetings[i][0] : end;
                endTime_room.push({end+meetings[i][1]-meetings[i][0], notEngaged.top()});
                count[notEngaged.top()]++;
                notEngaged.pop();
            }
        }

        int max = INT_MIN;
        for(int i = 0; i < n; i++){
            if(count[i] > max){
                max = count[i];
                room = i;
            }
        }

        for(int i = 0 ;i < n; i++)
            cout<<count[i]<<" ";

        return room;
    }
};
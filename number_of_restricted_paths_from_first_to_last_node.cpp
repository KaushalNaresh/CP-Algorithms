#include<bits/stdc++.h>
using namespace std;

class Solution {
public:

    int MOD = 1000000007;
    vector<int> dp;

    int dfs(unordered_map<int, vector<pair<int, int>>> &graph, int idx, vector<int> &minDist, int n){

        if(idx == n)
            return 1;

        if(dp[idx-1] != -1)
            return dp[idx-1];

        int count = 0;
        for(int i = 0; i < graph[idx].size(); i++){
            int new_idx = graph[idx][i].first;
            if(minDist[idx-1] > minDist[new_idx-1])
                count = (count + dfs(graph, new_idx, minDist, n)%MOD)%MOD;
        }        

        return dp[idx-1] = count;
    }

    struct compare{

        bool operator()(pair<int, int> p1, pair<int, int> p2){
            return p1.first > p2.first; // orderin Asc
        }
    };

    int countRestrictedPaths(int n, vector<vector<int>>& edges) {

        unordered_map<int, vector<pair<int, int>>> graph; // {strt -> {end, wt}}

        for(int i = 0; i < edges.size(); i++){
            graph[edges[i][0]].push_back({edges[i][1], edges[i][2]});
            graph[edges[i][1]].push_back({edges[i][0], edges[i][2]});
        }

        priority_queue<pair<int, int>, vector<pair<int, int>>, compare> pq;  // dist, idx

        pq.push({0, n});
        vector<int> visited(n, 0), minDist(n, INT_MAX);

        minDist[n-1] = 0;

        while(!pq.empty()){

            pair<int, int> p = pq.top();
            int dist = p.first, idx = p.second;
            visited[idx-1] = 1;
            pq.pop();

            for(int i = 0; i < graph[idx].size(); i++){
                int new_dist = graph[idx][i].second;
                int new_idx = graph[idx][i].first;
                if(visited[new_idx-1] == 0 && minDist[new_idx-1] > minDist[idx-1]+new_dist){
                    pq.push({ minDist[idx-1]+new_dist, new_idx});
                    minDist[new_idx-1] = minDist[idx-1]+new_dist;
                }
            }
        }

        visited = vector<int>(n, 0);
        dp = vector<int>(n, -1);
        
        int ans = dfs(graph, 1, minDist, n)%MOD;

        return ans;

    }
};
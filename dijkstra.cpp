#include<bits/stdc++.h>
using namespace std;

int main(){

    int edges, verts, start, src, dest, cost;
    cin>>edges>>verts>>start;

    unordered_map<int, vector<pair<int, int>>> graph;
    vector<int> dist(verts, INT_MAX), parent(verts, -1), visited(verts, 0);

    dist[start] = 0;

    for(int i = 0; i < edges; i++){
        cin>>src>>dest>>cost;
        graph[src].push_back({dest, cost});
        graph[dest].push_back({src, cost});
    }

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, start});

    while(!pq.empty()){
        pair<int, int> p = pq.top();
        src = p.second;
        int costSoFar = p.first;
        pq.pop();

        visited[src] = 1;

        for(auto itr = graph[src].begin(); itr != graph[src].end(); itr++){
            dest = itr->first;
            cost = itr->second;
            if(!visited[dest] && costSoFar + cost < dist[dest]){
                dist[dest] = costSoFar + cost;
                pq.push({dist[dest], dest});
                parent[dest] = src;
            }
        }
    }

    for(int i = 0; i < verts; i++){
        cout<<dist[i]<<" ";
    }
    cout<<endl;

    for(int i = 0; i < verts; i++){
        cout<<parent[i]<<" ";
    }
    cout<<endl;

}
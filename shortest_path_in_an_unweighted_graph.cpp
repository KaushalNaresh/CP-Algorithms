#include<bits/stdc++.h>
using namespace std;

void createGraph(unordered_map<int, vector<int>>& graph, vector<vector<int>> edges, int n){

    for(auto edge : edges)
        graph[edge[0]].push_back(edge[1]);
}

vector<int> shortest_path(vector<vector<int>> edges, int source, int dest, int n){

    unordered_map<int, vector<int>> graph;
    int idx = dest;

    createGraph(graph, edges, n);
    vector<int> parent(n, -1);
    vector<int> visited(n, 0);

    queue<int> q;
    q.push(source);
    visited[source] = 1;

    while(!q.empty()){

        int front = q.front();
        q.pop();

        if(front == dest)
            break;

        vector<int> neighbours = graph[front];
        
        for(auto neigh : neighbours){
            if(visited[neigh] == 0){
                parent[neigh] = front;
                q.push(neigh);
                visited[neigh] = 1;
            }
        }
    }
    vector<int> ans;

    while(idx != -1){
        ans.push_back(idx);
        idx = parent[idx];
    }

    if(ans.size() != 0)
        reverse(ans.begin(), ans.end());

    return ans;
}


int main(){

    int n, source, dest, vert1, vert2;
    cin>>n>>source>>dest;

    vector<vector<int>> edges;
    for(int i = 0; i < n; i++){
        cin>>vert1>>vert2;
        edges.push_back({vert1, vert2});
    }

    vector<int> shortestPath = shortest_path(edges, source, dest, n);

    for(auto i : shortestPath)
        cout<<i<<" ";
}
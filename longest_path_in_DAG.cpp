#include<bits/stdc++.h>
using namespace std;

int main(){

    int n, src, dest, cost, verts = 0, start, end;
    cin>>n>>start>>end;

    unordered_map<int, vector<pair<int, int>>> graph;

    for(int i = 0; i < n; i++){
        cin>>src>>dest>>cost;
        if(graph.count(src)){
            graph[src].push_back({dest, cost});
            verts++;
        }
        else
            graph[src] = {{dest, cost}};
        
        if(!graph.count(dest)){
            graph[dest] = {};
            verts++;
        }
    }

    vector<int> inDegree(verts, 0);
    vector<float> totalCost(verts, FLT_MIN);

    for(auto itr = graph.begin(); itr != graph.end(); itr++){
        for(auto itr1 = itr->second.begin(); itr1 != itr->second.end(); itr1++){
            inDegree[itr1->first]++;
        }
    }
    
    totalCost[start] = 1;
    queue<int> q;
    bool possible = false;
    q.push(start);

    while(!q.empty()){
        int ver = q.front();
        q.pop();

        if(ver == end){
            cout<<totalCost[ver]<<endl;
            possible = true;
            break;
        }

        for(auto itr = graph[ver].begin(); itr != graph[ver].end(); itr++){
            inDegree[itr->first]--;
            if(inDegree[itr->first] == 0)
                q.push(itr->first);
            if(totalCost[itr->first] == FLT_MIN)
                totalCost[itr->first] = itr->second;
            else 
                totalCost[itr->first] = max(totalCost[itr->first], totalCost[ver]*itr->second);
        }
    }

    if(!possible)
        cout<<-1.0<<endl;
}
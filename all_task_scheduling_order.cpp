#include<bits/stdc++.h>
using namespace std;

void getAllSchedules(unordered_map<int, vector<int>> &graph, 
                    unordered_map<int, int> inDegree, 
                    vector<vector<int>> &schedules,
                    vector<int> sources,
                    vector<int> schedule){

                        if(schedule.size() == inDegree.size()){
                            schedules.push_back(schedule);
                            return;
                        }

                        if(sources.size() > 0){
                            for(int i = 0; i < sources.size(); i++){

                                vector<int> sourcesForNextCall = sources;
                                auto vertex = sourcesForNextCall.begin()+i;
                                int vert = *vertex;

                                schedule.push_back(vert);
                                sourcesForNextCall.erase(vertex);

                                for(auto j : graph[vert]){
                                    inDegree[j] -= 1;
                                    if(inDegree[j] == 0)
                                        sourcesForNextCall.push_back(j);
                                }
                                
                                getAllSchedules(graph, inDegree, schedules, sourcesForNextCall, schedule);
                                
                                schedule.pop_back();
                                for(auto j : graph[vert]){
                                    inDegree[j]++;
                                }

                            }
                        }

                        return;

}

int main(){

    int tasks, edges, strt, end;
    cin>>tasks>>edges;

    unordered_map<int, vector<int>> graph;
    unordered_map<int, int> inDegree;

    for(int i = 0; i < edges; i++){
        cin>>strt>>end;
        graph[strt].push_back(end);
        inDegree[end]++;
        if(!inDegree.count(strt))
            inDegree[strt] = 0;
    }

    vector<int> sources;
    for(auto itr = inDegree.begin(); itr != inDegree.end(); itr++){
        if(itr->second == 0)
            sources.push_back(itr->first);
    }
    

    vector<vector<int>> schedules;
    vector<int> schedule;
    getAllSchedules(graph, inDegree, schedules, sources, schedule);

    for(int i = 0; i < schedules.size(); i++){
        for(int j = 0; j < schedules[i].size(); j++){
            cout<<schedules[i][j]<<" ";
        }
        cout<<endl;
    }

}
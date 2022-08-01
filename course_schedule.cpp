#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        
        unordered_map<int, vector<int>> graph;
        vector<int> inDegree(numCourses, 0);
        vector<int> ver;
        
        for(auto vec : prerequisites){
            int course = vec[0];
            int prereq = vec[1];
            
            if(graph.find(prereq) == graph.end())
                graph[prereq] = {course};
            else
                graph[prereq].push_back(course);
            
            inDegree[course] += 1;
        }
        
        for(int i = 0; i < numCourses; i++){
            if(inDegree[i] == 0)
                ver.push_back(i);
        }
        
        if(ver.size() == 0)
            return false;
        
        while(ver.size() != 0){
            
            int node = ver[ver.size()-1];
            ver.pop_back();
            
            for(auto i : graph[node]){
                inDegree[i] -= 1;
                if(inDegree[i] == 0)
                    ver.push_back(i);
            }
        }
        
        for(auto i : inDegree)
            if(i != 0)
                return false;
        
        return true;
    }
};
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        
        if(edges.size() == 0)
            return {0};
        
        vector<int> leaves;
        unordered_map<int, list<int>> m;
        
        for(int i = 0; i < edges.size(); i++){
            int v1 = edges[i][0];
            int v2 = edges[i][1];
            m[v1].push_back(v2);
            m[v2].push_back(v1);
        }
        
        for(int i = 0; i < n; i++){
            if(m[i].size() == 1)
                leaves.push_back(i);
        }
        
        while(n > 2){
            n-=leaves.size();
            vector<int> newLeaves;
            for(int i = 0; i < leaves.size(); i++){
                int leaf = leaves[i];
                m[m[leaf].front()].remove(leaf);
                if(m[m[leaf].front()].size() == 1)
                    newLeaves.push_back(m[leaf].front());
            }
            leaves = newLeaves;
        }
        
        return leaves;
    }
};
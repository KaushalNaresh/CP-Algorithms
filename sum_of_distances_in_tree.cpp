#include<bits/stdc++.h>
using namespace std;


class Solution {
public:

    pair<int, int> util(int root, vector<vector<int>> &graph, vector<int> &count, vector<int> &sum, int parent){
        
        int nodes = 0, sums = 0;
        for(int i = 0; i < graph[root].size(); i++){
            if(graph[root][i] == parent)
                continue;
            pair<int, int> ret = util(graph[root][i], graph, count, sum, root);
            nodes += ret.first;
            sums += ret.second;
        }
        count[root] = nodes+1;
        sum[root] = nodes + sums;

        return {count[root], sum[root]};
    }

    void dfs2(int root, vector<int> &ans, vector<vector<int>> &graph, vector<int> &count, vector<int> &sum, int n, int parent){

        if(root == 0)
            ans[0] = sum[0];
        
        for(int i = 0; i < graph[root].size(); i++){
            if(graph[root][i] == parent)
                continue;
            ans[graph[root][i]] = ans[root] - count[graph[root][i]] + n - count[graph[root][i]];
            dfs2(graph[root][i], ans, graph, count, sum, n, root);
        }

        return;
    }

    vector<int> sumOfDistancesInTree(int n, vector<vector<int>>& edges) {
        
        vector<int> count(n, 0), sum(n, 0);

        vector<vector<int>> graph(n);

        for(int i = 0; i < edges.size(); i++){
            int src = edges[i][0];
            int dest = edges[i][1];
            graph[src].push_back(dest);
            graph[dest].push_back(src);
        }

        util(0, graph, count, sum, -1);

        vector<int> ans(n, 0);

        dfs2(0, ans, graph, count, sum, n, -1);

        return ans;
    }
};
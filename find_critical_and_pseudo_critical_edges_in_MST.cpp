#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    class UF{

        public:
        int n;
        vector<int> parent, rank;

        UF(int n){
            this->n = n;
            parent = vector<int>(n);
            rank = vector<int>(n, 1);

            for(int i = 0; i < n; i++)
                parent[i] = i;
        }

        int find(int v){
            if(this->parent[v] == v)
                return v;
            
            return parent[v] = find(parent[v]);
        }


        // We can use union by rank by that we can keep trak of max size of the union tree and if its not equal to total vertices then graph is disconnected
        bool Union(int v1, int v2){
                
            int p1 = find(v1);
            int p2 = find(v2);

            if(p1 == p2)
                return false;
            else{
                if(rank[p1] == rank[p2])
                    parent[p1] = p2;
                else if(rank[p1] < rank[p2])
                    parent[p1] = p2;
                else
                    parent[p2] = p1;
                return true;
            }
        }
    };

    static bool compare(vector<int> v1, vector<int> v2){

        return v1[2] < v2[2];
    }

    int getMstCost(int n, vector<vector<int>>& edges, int idx, char c){
        
        UF* uf = new UF(n);
        int mstCost = 0;

        if(c == 'f'){
            uf->Union(edges[idx][0], edges[idx][1]);
            mstCost += edges[idx][2];
        }

        for(int i = 0; i < edges.size(); i++){
            if(i == idx)
                continue;
            if(uf->Union(edges[i][0], edges[i][1])){
                mstCost += edges[i][2];
            }
        }


        // to check if the graph is connected
        int root = uf->find(0);
        for(int i = 1; i < n; i++){
            if(root != uf->find(i))
                return INT_MAX;
        }

        return mstCost;
    }

    vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>>& edges) {
        
        for(int i = 0; i < edges.size(); i++)
            edges[i].push_back(i);
        
        sort(edges.begin(), edges.end(), compare);   // ElogE

        int mstCost = getMstCost(n, edges, -1, 'i');

        vector<int> critical = {}, pseudoCritical = {};

        for(int i = 0; i < edges.size(); i++){
            int cost = getMstCost(n, edges, i, 'i');
            if(cost > mstCost)
                critical.push_back(edges[i][3]);
            else{
                cost = getMstCost(n, edges, i, 'f');
                if(cost == mstCost)
                    pseudoCritical.push_back(edges[i][3]);
            }
        }

        return {critical, pseudoCritical};

    }
};
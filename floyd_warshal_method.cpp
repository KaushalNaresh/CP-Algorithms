/**
 * @file floyd_warshal_method.cpp
 * @author Naresh Kumar Kaushal
 * @details : Floyd_warshal method is used to detect negative cycles in graph and to calculate shortest
 *            distance between any 2 nodes. Main difference between Floyd_warshal and Bellman Ford
 *            is that Bellman ford finds shortest distance to all vertices from source node whereas 
 *            Floyd warshal finds shortest distance between any 2 nodes.
 */

#include<bits/stdc++.h>
using namespace std;

void prepareMatrix(vector<pair<int, int>>& edges, vector<int>& weights, vector<vector<int>>& matrix){

    int n = matrix.size();
    
    for(int i = 0; i < weights.size(); i++)
        matrix[edges[i].first][edges[i].second] = weights[i];
    
    for(int i = 0; i < n; i++)
        matrix[i][i] = 0;
}

void floyd_warshal(vector<vector<int>>& matrix, int n){

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            for(int k = 0; k < n; k++){
                if(matrix[j][i] != INT_MAX && matrix[i][k] != INT_MAX 
                   && matrix[j][i]+matrix[i][k] < matrix[j][k])
                    matrix[j][k] = matrix[j][i]+matrix[i][k];
            }
        }
    }

    for(int i = 0; i < n; i++){
        if(matrix[i][i] < 0){
            cout<<"Graph has a negative cycle"<<endl;
            return;
        }
    }

    cout<<"Graph has no negative cycle"<<endl;
    return;
}

int main(){

    int n, u, v, wt, size;
    cin>>n>>size;

    vector<pair<int, int>> edges;
    vector<vector<int>> matrix(size, vector<int>(size, INT_MAX));
    vector<int> weights;

    for(int i = 0; i < n; i++){
        cin>>u>>v>>wt;
        edges.push_back({u, v});
        weights.push_back(wt);
    }

    prepareMatrix(edges, weights, matrix);
    floyd_warshal(matrix, size);
}
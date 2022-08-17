#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    
    vector<pair<int, int>> getNeighbours(vector<vector<int>>& grid, int r, int c, vector<vector<int>>& visited){
        
        vector<pair<int, int>> neigh;
        int rows = grid.size();
        int cols = grid[0].size();
        
        if(r+1 < rows && visited[r+1][c] == 0 && grid[r+1][c] == 1)
            neigh.push_back({r+1, c});
        if(r-1 >= 0 && visited[r-1][c] == 0 && grid[r-1][c] == 1)
            neigh.push_back({r-1, c});
        if(c+1 < cols && visited[r][c+1] == 0 && grid[r][c+1] == 1)
            neigh.push_back({r, c+1});
        if(c-1 >= 0 && visited[r][c-1] == 0 && grid[r][c-1] == 1)
            neigh.push_back({r, c-1});
        
        return neigh;
    }
    
    void bfs(vector<vector<int>>& grid, int r, int c, vector<vector<int>>& rotTime){
        
        int rows = grid.size();
        int cols = grid[0].size();
        
        vector<vector<int>> visited(rows, vector<int>(cols, 0));
        
        queue<pair<pair<int, int>, int>> q;
        q.push({{r, c}, 0});
        rotTime[r][c] = 0;
        visited[r][c] = 1;
        
        while(!q.empty()){
            
            pair<pair<int, int>, int> p = q.front();
            
            int currR = p.first.first;
            int currC = p.first.second;
            int time = p.second;
            
            q.pop();
            
            vector<pair<int, int>> neigh = getNeighbours(grid, currR, currC, visited);
            
            if(neigh.size())
                time++;
            
            for(int i = 0; i < neigh.size(); i++){
                q.push({neigh[i], time});
                visited[neigh[i].first][neigh[i].second] = 1;
                
                rotTime[neigh[i].first][neigh[i].second] = min(rotTime[neigh[i].first][neigh[i].second], time);
            }
            
        }
    }
    
    void print(vector<vector<int>> grid){
        
        for(auto vec : grid){
            for(auto i : vec)
                cout<<i<<" ";
            cout<<endl;
        }
    }
    
    int orangesRotting(vector<vector<int>>& grid) {
        
        int rows = grid.size();
        int cols = grid[0].size();
        
        vector<vector<int>> rotTime(rows, vector<int>(cols, INT_MAX));
        
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                if(grid[i][j] == 0 || grid[i][j] == 2)
                    rotTime[i][j] = 0;
            }
        }
        
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                if(grid[i][j] == 2)
                    bfs(grid, i, j, rotTime);
            }
        }
        
        int maxTime = INT_MIN;
        
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                if(rotTime[i][j] == INT_MAX)
                    return -1;
                if(rotTime[i][j] > maxTime)
                    maxTime = rotTime[i][j];
            }
        }
        
        return maxTime != INT_MIN ? maxTime : -1;
    }
};
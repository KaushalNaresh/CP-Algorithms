#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        
        priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;
        int rows = matrix.size();
        int cols = matrix[0].size();
        
        pq.push({matrix[0][0], {0, 0}});
        matrix[0][0] = INT_MIN;
        
        while(k && !pq.empty()){
            pair<int, pair<int, int>> p = pq.top();
            int x = p.second.first;
            int y = p.second.second;
            pq.pop();
            
            if(x+1 < rows && matrix[x+1][y] != INT_MIN){
                pq.push({matrix[x+1][y], {x+1, y}});
                matrix[x+1][y] = INT_MIN;
            }
            if(y+1 < cols && matrix[x][y+1] != INT_MIN){
                pq.push({matrix[x][y+1], {x, y+1}});
                matrix[x][y+1] = INT_MIN;
            }
            
            k--;
            if(k == 0)
                return p.first;
        }
        
        return -1;
    }
};
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:

    /*
        Time Complexity : O(klogk)
        Space Complexity : O(k)
    */
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


    /*
        Time Complexity : O((m+n)logD) where m and n are number of rows and cols respectively 
                                       D is the difference between matrix[0][0] and matrix[m-1][n-1]
        Space Complexity : O(1)
    */
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        int rows = matrix.size(), cols = matrix[0].size();
        int LB = matrix[0][0], UB = matrix[rows-1][cols-1], ans = -1;
        while(LB <= UB){
            int mid = (LB+UB)>>1;
            if(countLessOrEqual(mid, matrix) >= k){
                ans = mid;
                UB = mid-1;
            }
            else
                LB = mid+1;
        }
        return ans;
    }

    int countLessOrEqual(int numb, vector<vector<int>>& matrix){
        int c = matrix[0].size()-1, ans = 0;
        for(int r = 0; r <= matrix.size()-1; r++){    
            while(c >= 0 && matrix[r][c] > numb)
                c-=1;
            ans+=c+1;
        }
        return ans;
    }
};
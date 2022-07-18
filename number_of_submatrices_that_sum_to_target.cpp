#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int numSubmatrixSumTarget(vector<vector<int>>& matrix, int target) {
        
        int rows = matrix.size();
        int cols = matrix[0].size();
        
        for(int i = 0; i < rows; i++){
            for(int j = 1; j < cols; j++){
                matrix[i][j] += matrix[i][j-1];
            }
        }
        
        int count = 0;
        
        for(int i = 0; i < cols; i++){
            for(int j = i; j < cols; j++){
                unordered_map<int, int> submatSum;
                submatSum[0] = 1;
                int currSum = 0;
                for(int k = 0; k < rows; k++){
                    currSum += matrix[k][j];
                    if(i != 0)
                        currSum -= matrix[k][i-1];
                    int needSum = currSum - target;
                    
                    if(submatSum.count(needSum))
                        count += submatSum[needSum];
                    
                    submatSum[currSum] += 1;
                }
            }
        }
        
        return count;
    }
};
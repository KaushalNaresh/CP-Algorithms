/**
 * // This is the BinaryMatrix's API interface.
 * // You should not implement it, or speculate about its implementation
 * interface BinaryMatrix {
 *     public int get(int row, int col) {}
 *     public List<Integer> dimensions {}
 * };
 */

#include<bits/stdc++.h>
using namespace std;

class Solution {
    public:
    int leftMostColumnWithOne(BinaryMatrix binaryMatrix) {

        vector<int> dim = binaryMatrix.dimensions();
        int rows = dim[0];
        int cols = dim[1];
        int lb = 0, ub = cols-1, prev = -1;
        bool hasOne = false, isPossible = false;

        while(lb <= ub){
            hasOne = false;

            int mid = (lb+ub)/2;

            for(int i = 0; i < rows; i++){
                if(binaryMatrix.get(i, mid) == 1){
                    hasOne = true;
                    isPossible = true;
                    break;
                }
            }

            if(hasOne)
                ub = mid-1;
            else
                lb = mid+1;

            prev = mid;
        }

        return isPossible ? lb : -1;
    }
};
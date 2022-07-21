#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Time Complexity : O(n) Using Stacks
    int largestRectangleArea(vector<int>& heights) {
        
        int n = heights.size();
        vector<int> leftIdx(n), rightIdx(n), stack;
        
        for(int i = 0; i < n; i++){
            
            if(stack.empty()){
                stack.push_back(i);
                leftIdx[i] = i;
            }
            else{
                int topIdx = stack.back();
                if(heights[topIdx] < heights[i]){
                    stack.push_back(i);
                    leftIdx[i] = i;
                }
                else{
                    while(!stack.empty() && heights[topIdx] >= heights[i]){
                        stack.pop_back();
                        if(!stack.empty())
                            topIdx = stack.back();
                    }
                    if(stack.empty())
                        leftIdx[i] = 0;
                    else
                        leftIdx[i] = topIdx+1;
                    stack.push_back(i);
                }
            }
        }
        
        stack = vector<int>();
        for(int i  = n-1; i >= 0; i--){
            
            if(stack.empty()){
                stack.push_back(i);
                rightIdx[i] = i;
            }
            else{
                int topIdx = stack.back();
                if(heights[topIdx] < heights[i]){
                    stack.push_back(i);
                    rightIdx[i] = i;
                }
                else{
                    while(!stack.empty() && heights[topIdx] >= heights[i]){
                        // topIdx = stack.back();
                        stack.pop_back();
                        if(!stack.empty())
                            topIdx = stack.back();
                    }
                    if(stack.empty())
                        rightIdx[i] = n-1;
                    else
                        rightIdx[i] = topIdx-1;
                    stack.push_back(i);
                }
            }
        }
        
        int maxArea = INT_MIN;
        for(int i = 0; i < n; i++){
            int left = leftIdx[i];
            int right = rightIdx[i];
            int area = (right-left+1)*heights[i];
            if(area > maxArea)
                maxArea = area;
        }
        
        return maxArea;
    }
    
    // Time Complexity : O(n) using DP
    int largestRectangleArea(vector<int>& heights) {

        int n = heights.size(), maxArea = INT_MIN;
        vector<int> leftBound(n), rightBound(n);
        leftBound[0] = -1;
        rightBound[n-1] = n;
        
        for(int i = 1; i < n; i++){
            int p = i-1;
            while(p >= 0 && heights[i] <= heights[p]){
                p = leftBound[p];
            }
            leftBound[i] = p;
        }

        for(int i = n-2; i >= 0; i--){
            int p = i+1;
            while(p < n && heights[i] <= heights[p]){
                p = rightBound[p];
            }
            rightBound[i] = p;
        }

        for(int i = 0; i < n; i++){
            int area = (rightBound[i]-leftBound[i]-1)*heights[i];
            maxArea = area > maxArea ? area : maxArea;
        }

        return maxArea;
    }
};
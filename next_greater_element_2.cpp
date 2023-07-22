#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {

        int n = nums.size();

        for(int i = 0; i < n; i++)
            nums.push_back(nums[i]);

        vector<int> stack;
        vector<int> nextGreater(2*n, -1);

        for(int i = 2*n-1; i >= 0; i--){
            if(stack.empty())
                stack.push_back(i);
            else{
                while(!stack.empty()){
                    int top = stack[stack.size()-1];
                    if(nums[top] > nums[i]){
                        nextGreater[i] = nums[top];
                        break;   
                    }
                    stack.pop_back();
                }
                stack.push_back(i);
            }
        }

        vector<int> ans;
        for(int i = 0; i < n; i++)
            ans.push_back(nextGreater[i]);

        return ans;
    }
};
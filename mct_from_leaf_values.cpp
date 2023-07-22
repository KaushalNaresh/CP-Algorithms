#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int mctFromLeafValues(vector<int>& arr) {

        int n = arr.size();
        vector<int> stack;
        stack.push_back(INT_MAX);

        int res = 0;

        for(auto numb : arr){
            while(!stack.empty()){
                int top = stack.back();
                if(top <= numb){
                    stack.pop_back();
                    res += top * min(stack.back(), numb);
                }
                else
                    break;
            }
            stack.push_back(numb);
        }
        
        for(int i = 2; i < stack.size(); i++)
            res += stack[i]*stack[i-1];

        return res;
    }
};
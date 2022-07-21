#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int trap(vector<int>& height) {
        
        stack<int> stk; // idx
        
        int water = 0;
        
        for(int i = 0; i < height.size(); i++){
            
            if(stk.empty()){
                stk.push(i);
            }
            
            else{
                
                int idx = stk.top();
                
                if(height[idx] > height[i]){
                    stk.push(i);
                }
                else{
                    
                    while(!stk.empty() && height[idx] <= height[i]){
                        int ht = height[idx];
                        stk.pop();
                        
                        if(!stk.empty()){
                            idx = stk.top();
                            water += (min(height[i], height[idx])-ht)*(i-idx-1);
                        }
                    }
                    
                    stk.push(i);
                }
            }
        }
        
        return water;
    }
};
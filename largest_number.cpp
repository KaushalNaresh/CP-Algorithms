#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    static bool compare(string s1, string s2){
        return s1+s2>s2+s1;
    }
    
    string largestNumber(vector<int>& nums) {
        
        vector<string> vec;
        
        for(int i = 0 ; i < nums.size(); i++){
            vec.push_back(to_string(nums[i]));
        }
        
        sort(vec.begin(), vec.end(), compare);
        
        string res = "";
        
        for(int i = 0; i < vec.size(); i++){
            res += vec[i];
        }
        
        while(res[0] == '0' && res.size() > 1){
            res.erase(0, 1);
        }
        
        return res;
    }
};
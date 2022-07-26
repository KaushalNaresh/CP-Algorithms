#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        
        unordered_map<char, int> mp, ms;
        for(auto c : p)
            mp[c] += 1;
        
        int lptr = 0, rptr = 0;
        vector<int> ans;
        
        while(rptr < s.size()){
            if(mp.count(s[rptr]) == 0){
                rptr++;
                lptr = rptr;
                ms = unordered_map<char, int>();
                continue;
            }
            else{
                if(mp[s[rptr]] <= ms[s[rptr]]){
                    while(s[lptr] != s[rptr]){
                        ms[s[lptr]]-=1;
                        lptr++;
                    }
                    ms[s[lptr]]-=1;
                    lptr++;
                }
                ms[s[rptr]] += 1;
            }
            
            if(rptr-lptr+1 == p.size()){
                ans.push_back(lptr);
            }
            rptr++;
        }
        return ans;
    }
};
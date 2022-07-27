#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        
        unordered_map<char, int> m;
        int maxSoFar = INT_MIN, maxCount = 0;
        
        for(auto c : tasks){
            m[c] += 1;
            
            if(m[c] == maxSoFar){
                maxCount += 1;
            }
            else if(m[c] > maxSoFar){
                maxSoFar = m[c];
                maxCount = 1;
            }
        }
        
        int parts = maxSoFar-1;
        int partLength = n-(maxCount-1);
        int emptyPlaces = parts*partLength;
        int available_tasks = tasks.size() - maxSoFar*maxCount;
        int idles = max(0, emptyPlaces-available_tasks);
        
        return idles+tasks.size();
        
    }
};
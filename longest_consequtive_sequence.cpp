#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    
    int count = 0;
    
    void dfs(unordered_map<int, int>& m, int idx){
        
        m[idx] = 1;
        count += 1;
        
        if(m.find(idx+1) != m.end() && m[idx+1] == 0)
            dfs(m, idx+1);
        if(m.find(idx-1) != m.end() && m[idx-1] == 0)
            dfs(m, idx-1);
        
        return;
    }
    
    class UF{
        
        public:
        vector<int> parent, size;
        
        UF(int n){
            this->parent = vector<int>(n);
            this->size = vector<int>(n);
            
            for(int i = 0; i < n; i++){
                this->parent[i] = i;
                this->size[i] = 1;
            }
        }
        
        void Union(int idx1, int idx2){
            
            int root1 = this->find(idx1);
            int root2 = this->find(idx2);
            
            if(root1 == root2)
                return;
            this->parent[root1] = root2;
            this->size[root2] += size[root1];
                
        }
        
        int find(int idx){
            
            if(this->parent[idx] == idx)
                return idx;
            
            return this->parent[idx] = find(this->parent[idx]);
        }
        
        int getLargetComponentSize() {
            int maxSize = 0;
            for (int i = 0; i < this->parent.size(); i++) {
                if (this->parent[i] == i && size[i] > maxSize) {
                    maxSize = size[i];
                }
            }
            
            return maxSize;
        }
    };
    
    int longestConsecutive(vector<int>& nums) {

//         Time Complexity : O(n) using DFS 
//         int n = nums.size();
//         unordered_map<int, int> m;
        
//         for(int i = 0; i < n; i++)
//             m[nums[i]] = 0;
        
//         int maxLen = INT_MIN;
        
//         for(auto i : m){
//             if(i.second == 0){
//                 count = 0;
//                 dfs(m, i.first);
//                 maxLen = count > maxLen ? count : maxLen; 
//             }
//         }
        
//         return maxLen != INT_MIN ? maxLen : 0;
  
        
/*****************************************************************/        
        
//         Time Complexity : O(n) using union find algorithm
        
        int n = nums.size();
        unordered_map<int, int> m;
        
        UF* uf = new UF(n);
        
        for(int i = 0; i < n; i++){
            if(m.find(nums[i]) != m.end())
                continue;
            
            if(m.find(nums[i]+1) != m.end())
                uf->Union(i, m[nums[i]+1]);
            if(m.find(nums[i]-1) != m.end())
                uf->Union(i, m[nums[i]-1]);
            
            m[nums[i]] = i;
        }
        
        return uf->getLargetComponentSize();
    }
};

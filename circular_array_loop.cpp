#include<bits/stdc++.h>
using namespace std;

// class Solution {
// public:

//     bool dfs(int node, vector<int>& nums, vector<vector<int>> &graph, vector<int> &visited, vector<int> stack, int direction){
        
//         visited[node] = 1;
//         stack[node] = 1;

//         for(int i = 0; i < graph[0].size(); i++){
//             if(node == i)
//                 continue;
//             if(graph[node][i] == 1 && direction*nums[i] > 0 && !(visited[i] == 1)){
//                 if(dfs(i, nums, graph, visited, stack, direction)){
//                     return true;
//                 }
//             }
//             else if(graph[node][i] == 1 && (stack[i] == 1))
//                 return true;
//         }

//         return false;
//     }

//     bool circularArrayLoop(vector<int>& nums) {
        
//         int n = nums.size();
//         vector<vector<int>> graph(n, vector<int>(n, 0));

//         vector<int> visited(n, 0), stack(n, 0);

//         for(int i = 0; i < n; i++){
//             int neigh = ((i+nums[i])%n+n)%n;
//             graph[i][neigh] = 1;
//         }

//         for(int i = 0; i < n; i++){
//             int direction = nums[i] < 0 ? -1 : 1;
//             if(visited[i] != 1)
//                 if(dfs(i, nums, graph, visited, stack, direction)){
//                     return true;
//                 }
//         }

//         return false;
//     }
// };

/*Using Union Find*/

class Solution {
public:

    int find(int node, vector<int> parent){

        if(parent[node] == node)
            return node;

        return parent[node] = find(parent[node], parent); 
    }

    bool circularArrayLoop(vector<int>& nums) {

        int n = nums.size();
        vector<int> parent(n, 0);

        for(int i = 0; i < n; i++)
            parent[i] = i;

        for(int i = 0; i < n; i++){
            int j = ((i + nums[i])%n+n)%n;
            if(i != j && nums[i]*nums[j] > 0){
                int prnt1 = find(i, parent);
                int prnt2 = find(j, parent);

                if(prnt1 == prnt2)
                    return true;
                parent[prnt1] = prnt2;
            }
        }

        return false;
    }
};


int main(){

    Solution* soln = new Solution();
    vector<int> nums;
    int n, numb;

    cin>>n;
    for(int i = 0; i < n; i++){
        cin>>numb;
        nums.push_back(numb);
    }

    cout<<soln->circularArrayLoop(nums);
}
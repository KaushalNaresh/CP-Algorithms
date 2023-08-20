#include<bits/stdc++.h>
using namespace std;

int utilFunc(unordered_map<int, vector<pair<int, int>>> &map, pair<int, int> node, int &res){

    int single_line_path = node.second, triag_path = node.second, branch_path1 = INT_MIN, branch_path2 = INT_MIN;
    for(int i = 0; i < map[node.first].size(); i++){
        
        int temp = utilFunc(map, map[node.first][i], res);
        
        if(temp > branch_path1){
            branch_path2 = branch_path1;
            branch_path1 = temp;
        }
        else if(temp > branch_path2)
            branch_path2 = temp;

        single_line_path = max(temp+node.second, single_line_path);
    }

    if(branch_path1 != INT_MIN && branch_path2 != INT_MIN)
        triag_path = max(branch_path1+branch_path2+node.second, triag_path);
    
    res = max(res, max(single_line_path, triag_path));

    return single_line_path;

}

int getMaxPathSum(vector<int>& parents, vector<int>& values){

    unordered_map<int, vector<pair<int, int>>> map;

    for(int i = 0; i < parents.size(); i++){
        map[parents[i]].push_back({i, values[i]});
    }

    int res = INT_MIN;
    utilFunc(map, map[-1][0], res);

    return res;
}

int main(){
    
    int n, p, val;
    cin>>n;

    vector<int> parent(n), values(n);

    for(int i = 0; i < n; i++){
        cin>>p>>val;
        parent[i] = p;
        values[i] = val;
    }

    cout<<getMaxPathSum(parent, values);
}
#include<bits/stdc++.h>
using namespace std;

class UnionFind{

    public:
    vector<int> parent, rank;
    UnionFind(int n){
        
        parent = vector<int>(n);
        rank = vector<int>(n, 1);

        for(int i = 0; i < n; i++)
            parent[i] = i;
    }

    int find(int node){
        if(this->parent[node] == node)
            return node;

        return parent[node] = find(parent[node]);
    }

    bool Union(int node1, int node2){

        int prnt1 = find(node1);
        int prnt2 = find(node2);

        if(prnt1 == prnt2)
            return true;
        else if(rank[prnt1] < rank[prnt2])
            parent[prnt1] = prnt2;
        else if(rank[prnt2] < rank[prnt1])
            parent[prnt2] = prnt1;
        else{
            parent[prnt2] = prnt1;
            rank[prnt1]++;
        }
        return false;
    }
};

class Solution{

    public:
    bool doesPathExist(vector<vector<char>> graph, int hx, int hy, int sx, int sy,
                       vector<vector<int>> ops){

        int rows = graph.size(), cols = graph[0].size();
        int house = hx*cols+hy, salon = sx*cols+sy;

        vector<vector<int>> direcs = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

        UnionFind* uf = new UnionFind(rows*cols);

        for(int i = 0; i < ops.size(); i++){
            int x = ops[i][0], y = ops[i][1];
            int node1 = x*cols+y;

            graph[x][y] = 'R';

            for(int j = 0; j < 4; j++){
                int new_x = x+direcs[j][0];
                int new_y = y+direcs[j][1];

                int node2 = new_x*cols+new_y;

                if(new_x >= 0 && new_x < rows && new_y >= 0 && new_y < cols &&
                   graph[new_x][new_y] != '.'){
                    uf->Union(node1, node2);
                }
            }

            // for(int i = 0; i < rows*cols; i++)
            //     cout<<uf->parent[i]<<" ";
            // cout<<endl;

            if(uf->find(house) == uf->find(salon))
                return true;
        }
        return false;
    }
};

int main(){

    int rows, cols, hx, hy, sx, sy;
    cin>>rows>>cols;

    vector<vector<char>> graph(rows, vector<char>(cols));

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            char ch;
            cin>>ch;
            graph[i][j] = ch;
        }
    }

    cin>>hx>>hy>>sx>>sy;

    int ops;
    cin>>ops;

    vector<vector<int>> operations(ops, vector<int>(2));

    for(int i = 0; i < ops; i++){
        int x, y;
        cin>>x>>y;

        operations[i][0] = x;
        operations[i][1] = y;
    }

    Solution* soln = new Solution();
    cout<<soln->doesPathExist(graph, hx, hy, sx, sy, operations);
}
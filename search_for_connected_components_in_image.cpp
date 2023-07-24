#include<bits/stdc++.h>
using namespace std;

int rows, cols, numb;

pair<int, int> find(vector<vector<pair<int, int>>> &parent, int r, int c){

    if(parent[r][c].first == r && parent[r][c].second == c)
        return {r, c};

    return parent[r][c] = find(parent, parent[r][c].first, parent[r][c].second);

}

void Union(vector<vector<int>> &size, vector<vector<pair<int, int>>> &parent, int r1, int c1, int r2, int c2){

    pair<int, int> p1 = find(parent, r1, c1);
    pair<int, int> p2 = find(parent, r2, c2);

    if(p1.first != p2.first || p1.second != p2.second){
        if(size[p1.first][p1.second] >= size[p2.first][p2.second]){
            parent[p2.first][p2.second] = p1;
            size[p1.first][p1.second] += size[p2.first][p2.second];
        }
        else{
            parent[p1.first][p1.second] = p2;
            size[p2.first][p2.second] += size[p1.first][p1.second];
        }
    }
}

int main(){

    cin>>rows>>cols;
    vector<vector<int>> image(rows, vector<int>(cols)), size(rows, vector<int>(cols, 1));
    vector<vector<pair<int, int>>> parent(rows, vector<pair<int, int>>(cols, {-1, -1}));

    for(int i = 0 ; i < rows; i++){
        for(int j = 0; j < cols; j++){
            cin>>numb;
            image[i][j] = numb;
            if(numb == 0)
                parent[i][j] = {i, j};
        }
    }

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            if(image[i][j] == 0){
                if(i-1 >= 0 && image[i-1][j] == 0)
                    Union(size, parent, i, j, i-1, j);
                if(j-1 >= 0 && image[i][j-1] == 0)
                    Union(size, parent, i, j, i, j-1);
            }
        }
    }

    // for(int i = 0; i < rows; i++){
    //     for(int j = 0; j < cols; j++){
    //         cout<<"{"<<parent[i][j].first<<","<<parent[i][j].second<<"}"<<" ";
    //     }
    //     cout<<endl;
    // }

    // for(int i = 0; i < rows; i++){
    //     for(int j = 0; j < cols; j++){
    //         cout<<size[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }

    int count = 0;
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            if(parent[i][j].first == i && parent[i][j].second == j)
                count++;
        }
    }

    cout<<count;

}
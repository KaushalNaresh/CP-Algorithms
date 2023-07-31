#include<bits/stdc++.h>
using namespace std;

void bfs(int x, int y, vector<vector<int>> &graph, vector<vector<int>> &cnt,
         vector<vector<int>> &dist){

    queue<pair<int, int>> q;
    q.push({x, y});

    int rows = graph.size();
    int cols = graph[0].size();

    vector<pair<int, int>> neighbours = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));

    int distance = 0;

    while(!q.empty()){

        int size = q.size();
        distance++;
        for(int i = 0; i < size; i++){
            pair<int, int> p = q.front();
            q.pop();

            for(int i = 0; i < 4; i++){
                int new_x = p.first+neighbours[i].first;
                int new_y = p.second+neighbours[i].second;

                if(new_x >= 0 && new_x < rows && new_y >= 0 && new_y < cols &&
                !visited[new_x][new_y] && graph[new_x][new_y] == 0){
                        q.push({new_x, new_y});
                        visited[new_x][new_y] = true;
                        dist[new_x][new_y] += distance;
                        cnt[new_x][new_y] ++;
                }
            }
        }

    }
       
}

int main(){

    int rows, cols, numb, buildings = 0;
    cin>>rows>>cols;
    vector<vector<int>> graph(rows, vector<int>(cols)), cnt(rows, vector<int>(cols)), dist(rows, vector<int>(cols));

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            cin>>numb;
            graph[i][j] = numb;
            if(numb == 1)
                buildings++;
        }
    }

    // 1 building, 0 empty space an 2 obstacle

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            if(graph[i][j] == 1){
                bfs(i, j, graph, cnt, dist);
            }
        }
    }


    int minDist = INT_MAX;
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            if(graph[i][j] == 0 && minDist > dist[i][j] && cnt[i][j] == buildings)
                minDist = dist[i][j];
        }
    }

    cout<<minDist<<endl;

}
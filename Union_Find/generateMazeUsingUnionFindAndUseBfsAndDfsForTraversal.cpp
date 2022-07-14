#include<bits/stdc++.h>
using namespace std;

int rows, cols;
vector<vector<int>> graph;
vector<int> parent;
vector<int> ranks;

int find(int idx){
    if(parent[idx-1] == idx)
        return idx;
    return parent[idx-1] = find(parent[idx-1]);
}

int getSecondIdx(int idx_1){

    int r = (idx_1-1)/cols;
    int c = (idx_1-1)%cols;

    vector<pair<int, int>> neigh;

    if(r-1>=0)
        neigh.push_back({r-1, c});
    if(c-1>=0)
        neigh.push_back({r, c-1});
    if(c+1<cols)
        neigh.push_back({r, c+1});
    if(r+1<rows)
        neigh.push_back({r+1, c});

    int size = neigh.size();

    int i = rand()%size;

    int idx_2 = neigh[i].first*cols+neigh[i].second+1;

    return idx_2;
}

void Union(int idx1, int idx2){

    idx1 = find(idx1);
    idx2 = find(idx2);

    if(find(idx1) != find(idx2)){
        if(ranks[idx1-1] == ranks[idx2-1]){
            ranks[idx2-1] += 1;
            parent[idx1-1] = idx2;
        }
        else if(ranks[idx1-1] < ranks[idx2-1]){
            parent[idx1-1] = parent[idx2-1];
        }
        else if(ranks[idx2-1] < ranks[idx1-1]){
            parent[idx2-1] = parent[idx1-1];
        }
    }
}

string getDirection(int r1, int c1, int r2, int c2){

    if(r1-1 == r2)
        return "NORTH";
    
    if(r1+1 == r2)
        return "SOUTH";

    if(c1-1 == c2)
        return "WEST";

    if(c1+1 == c2)
        return "EAST";

    return "";

}

void removeCommonWall(int idx_1, int idx_2, vector<vector<int>>& graph){

    int r1 = (idx_1-1)/cols; 
    int c1 = (idx_1-1)%cols;

    int r2 = (idx_2-1)/cols;
    int c2 = (idx_2-1)%cols;

    string direc = getDirection(r1, c1, r2, c2);

    //idx_2 is on north of idx_1
    if(direc == "NORTH"){
        graph[r1][c1] = graph[r1][c1] & ~1; // remove north wall of r1 c1
        graph[r2][c2] = graph[r2][c2] & ~2; // remove south wall of r2 c2
    }
    
    //idx_2 is on south of idx_1
    else if(direc == "SOUTH"){
        graph[r1][c1] = graph[r1][c1] & ~2; // remove south wall of r1 c1
        graph[r2][c2] = graph[r2][c2] & ~1; // remove north wall of r2 c2
    }

    //idx_2 is on east of idx_1
    else if(direc == "EAST"){
        graph[r1][c1] = graph[r1][c1] & ~4; // remove east wall of r1 c1
        graph[r2][c2] = graph[r2][c2] & ~8; // remove west wall of r2 c2
    }

    //idx_2 is on west of idx_1
    else if(direc == "WEST"){
        graph[r1][c1] = graph[r1][c1] & ~8; // remove west wall of r1 c1
        graph[r2][c2] = graph[r2][c2] & ~4; // remove east wall of r2 c2
    }
}

void generateMaze(vector<vector<int>>& graph){

    int cells = rows*cols;

    while(find(1) != find(cells)){

        int idx_1 = rand()%cells+1; 
        int idx_2 = getSecondIdx(idx_1);

        int r1 = (idx_1-1)/cols; 
        int c1 = (idx_1-1)%cols;

        int r2 = (idx_2-1)/cols;
        int c2 = (idx_2-1)%cols;

        string direc = getDirection(r1, c1, r2, c2);

        if(direc == "NORTH" && int(graph[r1][c1] & 1) == 0 && int(graph[r2][c2] & 2) == 0 ||
           direc == "SOUTH" && int(graph[r1][c1] & 2) == 0 && int(graph[r2][c2] & 1) == 0 ||
           direc == "EAST" && int(graph[r1][c1] & 4) == 0 && int(graph[r2][c2] & 8) == 0 ||
           direc == "WEST" && int(graph[r1][c1] & 8) == 0 && int(graph[r2][c2] & 4) == 0)
           continue;

        removeCommonWall(idx_1, idx_2, graph);
        Union(idx_1, idx_2);

    }
}

vector<int> getNeighbours(int src){

    int r = (src-1)/cols; 
    int c = (src-1)%cols;

    vector<int> neigh;

    if(r-1 >= 0 && int(graph[r][c] & 1) == 0 && int(graph[r-1][c] & 2) == 0)
        neigh.push_back((r-1)*cols+c+1);
    if(r+1 < rows && int(graph[r][c] & 2) == 0 && int(graph[r+1][c] & 1) == 0)
        neigh.push_back((r+1)*cols+c+1);
    if(c-1 >= 0 && int(graph[r][c] & 8) == 0 && int(graph[r][c-1] & 4) == 0)
        neigh.push_back(r*cols+c);
    if(c+1 < cols && int(graph[r][c] & 4) == 0 && int(graph[r][c+1] & 8) == 0)
        neigh.push_back(r*cols+c+2);

    return neigh;

}

bool dfs(vector<vector<int>>& graph, int src, vector<vector<int>>& paths, vector<int>& path, vector<int>& visited){

    visited[src-1] = 1;
    path.push_back(src);

    if(src == rows*cols){
        paths.push_back(path);
        return true;
    }

    vector<int> neigh = getNeighbours(src);

    for(int i = 0; i < neigh.size(); i++){
        if(visited[neigh[i]-1] == 0){
            if(dfs(graph, neigh[i], paths, path, visited))
                return true;
            visited[neigh[i]-1] = 0;
            path.pop_back();
        }
    }

    return false;

}

void bfs(vector<vector<int>>& graph, int src, vector<vector<int>>& paths, vector<int>& path, vector<int>& visited){

    queue<int> q;
    q.push(src);

    vector<int> parent(rows*cols, -1);

    while(!q.empty()){

        int top = q.front();
        q.pop();

        if(top == rows*cols)
            break;

        visited[top-1] = 1;

        vector<int> neigh = getNeighbours(top);

        for(int i = 0; i < neigh.size(); i++){
            if(visited[neigh[i]-1] == 0){
                q.push(neigh[i]);
                parent[neigh[i]-1] = top;
            }
        }
    }

    int node = rows*cols;

    while(node != -1){
        path.push_back(node);
        node = parent[node-1];
    }

    reverse(path.begin(), path.end());
    paths.push_back(path);
}

void printPath(vector<vector<int>> paths, string algo){

    ofstream file2;

    file2.open(algo+"_path.txt");

    if(paths.size() != 0){
        cout<<algo<<" Path : ";
        for(auto i : paths[0]){
            cout<<i<<" ";
            file2<<i<<" ";
        }
        file2<<'\n';
        cout<<endl;
    }
    else{
        cout<<"No path found! Check ur logic again"<<endl;
    }

    file2.close();
}

void printGraph(){

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++)
            cout<<graph[i][j]<<" ";
        cout<<endl;
    }
}

int main(){

    cin>>rows>>cols;

    graph = vector<vector<int>>(rows, vector<int>(cols, 15));
    parent = vector<int>(rows*cols, -1);
    for(int i = 0; i < rows*cols; i++)
        parent[i] = i+1;

    ranks = vector<int>(rows*cols, 1);

    generateMaze(graph);

    ofstream file1;
    file1.open("graph.txt");

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            file1<<graph[i][j]<<" ";
        }
        file1<<'\n';
    }

    file1.close();

    vector<vector<int>> paths;
    vector<int> path, visited(rows*cols, 0);

    dfs(graph, 1, paths, path, visited);
    cout<<"Number of DFS paths "<<paths.size()<<endl; // Will always be one
    printPath(paths, "DFS");

    paths = vector<vector<int>>();
    path = vector<int>();
    visited = vector<int>(rows*cols, 0);

    bfs(graph, 1, paths, path, visited);
    cout<<"Number of BFS paths "<<paths.size()<<endl;  // Will always be one
    printPath(paths, "BFS");

    printGraph();

    return 0;
}

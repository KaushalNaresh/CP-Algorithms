/*
    Question : There are n processes to be executed, where the ith process takes execution[i] time. Two
    processes are cohesive if and only if their original execution times are equal. When a process with
    execution time execution[i] is eecuted, it takes execution[i] time to execute and simultaneously 
    reduces the execution time of all its cohesive processes to ceil(execution[i]/2). Given the execution
    time of n processes, find the total amount of time the processor takes to execute all the processes
    if you execute the process in the given orer i.e. from left to right.

    1 <= n <= 2.10^5
    1 <= execution[i] <= 10^9
*/

#include<bits/stdc++.h>
using namespace std;

int main(){

    int n, num;
    cin>>n;
    vector<int> vec(n), temp(n);

    for(int i = 0; i < n; i++){
        cin>>num;
        vec[i] = num;
        temp[i] = num;
    }

    unordered_map<int, deque<int>> neighbour;

    for(int i = 0; i < n; i++){
        if(neighbour.count(vec[i]) == 0)
            neighbour[vec[i]] = {i};
        else
            neighbour[vec[i]].push_back(i);
    }

    vector<int> visited(n, 0);
    int time = 0;

    for(int i = 0; i < n; i++){
        time+=temp[i];
        neighbour[vec[i]].pop_front();

        for(int j = 0; j < neighbour[vec[i]].size(); j++){
            temp[neighbour[vec[i]][j]] = ceil(temp[neighbour[vec[i]][j]]/2.0);
        }
    }

    cout<<time;

}
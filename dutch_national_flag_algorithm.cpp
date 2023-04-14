#include<bits/stdc++.h>
using namespace std;

void swap(vector<int> &arr, int ptr1, int ptr2){

    int temp = arr[ptr1];
    arr[ptr1] = arr[ptr2];
    arr[ptr2] = temp;
}

// Partition algorithm when pivot is not unique
// Input : array and pivot value 'v'
// what it does? [elements less than v, elements equal to v, elements greater than v]
//               [Sl, Sv, Sr]
// return {leftmost index of Sv, rightmost index of Sv}

vector<int> partition(vector<int> &arr, int pivot){

    int lt = 0, current = 0, rt = arr.size()-1;

    while(current <= rt){
        if(arr[current] < pivot){
            swap(arr, current, lt);
            current += 1;
            lt += 1;
        }
        else if(arr[current] == pivot)
            current += 1;
        else if(arr[current] > pivot){
            swap(arr, current, rt);
            rt -= 1;
        }
    }

    return {lt, rt};
}

int main(){

    int n, numb, pivot;
    cin>>n>>pivot;
    vector<int> arr;

    for(int i = 0; i < n; i++){
        cin>>numb;
        arr.push_back(numb);
    }

    vector<int> ptrs = partition(arr, pivot);
}
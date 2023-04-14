#include<bits/stdc++.h>
using namespace std;

void swap(vector<int> &arr, int ptr1, int ptr2){

    int temp = arr[ptr1];
    arr[ptr1] = arr[ptr2];
    arr[ptr2] = temp;
}

// O(n)
// Dutch National Flag Algorithm
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


// T(n)
int findMedian(vector<int> arr, int idx){

    int size = arr.size();

    if(size <= 5){
        sort(arr.begin(), arr.end());
        return arr[idx];
    }

    vector<int> medians;

    for(int i = 0; i < size; i+=5){               // O(n)
        sort(arr.begin(), arr.begin()+5);
        int endIdx = i+4 < size ? i+4 : size-1;
        medians.push_back(arr[(i+endIdx)/2]);
    }

    int median = findMedian(medians, (medians.size()-1)/2);  // T(n/5)

    vector<int> ptrs = partition(arr, median); // O(n)

    int sl = ptrs[0], sv = ptrs[1]-ptrs[0]+1, sr = size - sl - sv;

    //T(7n/10) 

    if(idx < sl){
        vector<int> sl_array(arr.begin(), arr.begin()+sl-1);
        return findMedian(sl_array, idx);
    }
    else if(idx >= sl && idx < sl+sv)
        return arr[idx];
    else{
        vector<int> sr_array(arr.begin()+(sl+sv), arr.end());
        return findMedian(sr_array, idx-sl-sv);
    }
}

int main(){

    int n, numb;
    vector<int> vec;

    cin>>n;

    for(int i = 0; i < n; i++){
        cin>>numb;
        vec.push_back(numb);
    }
    int idx = (n-1)/2;

    cout<<findMedian(vec, idx);
}
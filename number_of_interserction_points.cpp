/* Suppose we are given two sets of n points, one set {p1, p2, . . . , pn} on the line y = 0 and the other
set {q1, q2, . . . , qn} on the line y = 1. Consider the n line segments connecting each point pi to the
corresponding point qi. Describe and analyze a divide-and-conquer algorithm to determine how
many pairs of these line segments intersect, in O(n log n) time. */

#include<bits/stdc++.h>
using namespace std;

void swap(vector<pair<int, int>> &pq, int ptr1, int ptr2){

    pair<int, int> temp = pq[ptr1];
    pq[ptr1] = pq[ptr2];
    pq[ptr2] = temp;
}

// Shell sort O(nlogn)
void merge(vector<pair<int, int>> &pq, int lptr1, int rptr1, int lptr2, int rptr2){

    int length = rptr2-lptr1+1, h = ceil(length/2.0);

    while(h >= 1){
        int ptr = lptr1;
        while(ptr <= rptr2-h){
            if(pq[ptr].second > pq[ptr+h].second)
                swap(pq, ptr, ptr+h);
            ptr++;
        }
        if(h == 1)
            break;

        h = ceil(h/2.0);
    }
}

// Time complexity O(logn*n*logn) extra logn is because of inplace merge sort using shell sort
// Space Complexity O(1)
int findNumberOfIntersections(vector<pair<int, int>> &pq, int lb, int ub){

    if(lb == ub)
        return 0;

    int mid = (lb+ub)/2;

    int inv_left = findNumberOfIntersections(pq, lb, mid);
    int inv_right = findNumberOfIntersections(pq, mid+1, ub);

    int lptr = lb, rptr = mid+1, invs = 0;

    while(lptr <= mid && rptr <= ub){
        if(pq[lptr].second > pq[rptr].second){
            invs += mid-lptr+1;
            rptr++;
        }
        else
            lptr++;
    }
   
    merge(pq, lb, mid, mid+1, ub);

    return invs+inv_left+inv_right;

}

int main(){
    
    int n, numb;
    cin>>n;

    vector<int> p, q;

    for(int i = 0; i < n; i++){
        cin>>numb;
        p.push_back(numb);
    }

    for(int i = 0; i < n; i++){
        cin>>numb;
        q.push_back(numb);
    }

    vector<pair<int, int>> pq;

    for(int i = 0; i < n; i++)
        pq.push_back({p[i], q[i]});

    sort(pq.begin(), pq.end());

    cout<<findNumberOfIntersections(pq, 0, pq.size()-1);

}
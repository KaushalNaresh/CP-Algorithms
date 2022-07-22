# CP-Algorithms
Competitive Programming Algorithms

For practice solve https://leetcode.com/discuss/general-discussion/460599/blind-75-leetcode-questions

Helpful blog : https://hackernoon.com/14-patterns-to-ace-any-coding-interview-question-c5bb3357f6ed


## Quick Notes :

1. Min heap in cpp : 
```cpp
priority_queue <int, vector<int>, greater<int>> pq;
```
2. How to create a Comparator function for sort, queues etc.
- using operator overloading for priority queues
```cpp
struct compare{
  bool operator()(Type val1, Type val2){
    return val1 < val2;
  }
};
```
- using static method for sort function
```cpp
static bool compare(Type val1, Type val2){
  return val1 < val2;
}
```
3. C++ upper_bound function
```cpp
vector<int> vec = {1,2,3,4,5};
int target = 3;
auto it = upper_bound(vec.begin(), vec.end(), target); // returns iterator to index 3
cout<<*it; // prints 4 i.e. value at index 3
```
4. Comparator function of upper_bound function
```cpp
static bool compare(int target, int val){  // first argument must always be target and second must point to forward iterator
  return val >= target;
}

vector<int> vec = {1,2,3,4,5};
int target = 3;
auto it = upper_bound(vec.begin(), vec.end(), target, compare); // returns iterator to index 3
```


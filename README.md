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
- using operator overloading
```cpp
struct compare{
  bool operator()(Type val1, Type val2){
    return val1 < val2;
  }
};
```
- using static method
```cpp
static bool compare(Type val1, Type val2){
  return val1 < val2;
}
```

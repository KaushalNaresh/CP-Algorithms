# CP-Algorithms
Competitive Programming Algorithms

For practice solve https://leetcode.com/discuss/general-discussion/460599/blind-75-leetcode-questions

Helpful blogs 
1. https://hackernoon.com/14-patterns-to-ace-any-coding-interview-question-c5bb3357f6ed
2. https://jeremyaguilon.me/blog/ranking_interview_questions_by_cram_score
3. https://pittcs.wiki/zero-to-offer/ace-your-interview


## Quick Notes :

1. Min heap in cpp : 
```cpp
priority_queue <int, vector<int>, greater<int>> pq;
```
2. How to create a Comparator function.
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
3. C++ upper_bound function : It returns an iterator pointing to the first element in the range \[first, last\] that is greater than value, or last if no such element is found. 
```cpp
vector<int> vec = {1,2,3,4,5};
int target = 3;
auto it = upper_bound(vec.begin(), vec.end(), target); // returns iterator to index 3
cout<<*it; // prints 4 i.e. value at index 3
```
4. C++ lower_bound function : The lower_bound() method is used to return an iterator pointing to the first element in the range \[first, last\] which has a value not less than val. This means that the function returns an iterator pointing to the next smallest number just greater than or equal to that number. If there are multiple values that are equal to val, lower_bound() returns the iterator of the first such value.

5. Comparator function of upper_bound function
```cpp
static bool compare(int target, int val){  // first argument must always be target and second must point to forward iterator
  return val >= target;
}

vector<int> vec = {1,2,3,4,5};
int target = 3;
auto it = upper_bound(vec.begin(), vec.end(), target, compare); // returns iterator to index 3
```

6. Bellman Ford Algorithm. 
Initialise distance of origin as 0. Now using 2 for loops one running for number of vertices and other over edges, you have to check if distance of any node decreases, if yes then update the distance. After this 2 for loop if distance of any node still reduces then there is a negative cycle, otherwise distance array will give minimum distance to all nodes from origin.


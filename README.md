# CP-Algorithms
Competitive Programming Algorithms

For practice solve https://leetcode.com/discuss/general-discussion/460599/blind-75-leetcode-questions

Helpful blogs 
1. https://hackernoon.com/14-patterns-to-ace-any-coding-interview-question-c5bb3357f6ed
2. https://jeremyaguilon.me/blog/ranking_interview_questions_by_cram_score
3. https://pittcs.wiki/zero-to-offer/ace-your-interview
4. https://www.baeldung.com/java-sorting-arrays-with-repeated-entries
5. https://hideoushumpbackfreak.com/


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
There is a catch here, for priority queues comparator function creates heap with top element from the right of sorted array. So if your comp function returns true for < then pq will be maxHeap.

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

6. Bellman Ford Algorithm:  
Initialise distance of origin as 0. Now using 2 for loops one running for number of vertices and other over edges, you have to check if distance of any node decreases, if yes then update the distance. After this 2 for loop if distance of any node still reduces then there is a negative cycle, otherwise distance array will give minimum distance to all nodes from origin.  

7. Flloyd-Warshal method:  
Both Bellman ford and flloyd warshal method detects negative cycle, but Bellman ford gives shortest distance from origin to all nodes whereas as Flloyd Warshal gives shortest between any 2 nodes. 

8. Brief summary on iterators and generators in python:

A generic example example of iterator, it reqires \_\_iter__ method, \_\_next__ method apart from \_\_init__ method
```python
class Counter:
  def __init__(self, n):
    self.i = 0
    self.n = n

  def __iter__(self):
    return self

  def __next__(self):
    while(self.i < self.n)
      self.i += 1
      return self.i
    return -1  # End of iterator
```

Counter is iterable class to convert it into iterator use iter(Counter) and to get the next element use next(Counter).

A generic example of generator

```python
def count(n):
  i = 0
  while i < n:
    i += 1
    yield i
  return -1  # End of generator function
```

count is a generator function and to get the next value from this generator use next(count). We can write a generator in the form of list comprehension by using '()' braces and not '[]'

9. How to make a threadsafe iterator:

In multithreading, we often encounter the challenge of synchronization. It becomes necessary to ensure that iterators are thread-safe because multiple threads can potentially access the next method simultaneously. To address this issue, we can utilize locks in Python.

```python
import threading 
class Counter:
  def __init__(self, n):
    self.i = 0
    self.n = n
    self.lock = threading.Lock()

  def __iter__(self):
    return self

  def __next__(self):
    while(self.i < self.n):
      # acquire/release the lock when updating self.i
      with self.lock:
        self.i += 1
        return self.i
    return -1  # End of iterator
```

The same cannot be done with generators since we don't have direct access to their next method. However, we can employ decorators and encapsulate the generator within a thread-safe iterator to ensure its thread safety.

10. Decaoraters

let's say we have function func()

```python
  def func(a, b, c = 0):
    sum = a+b+c
    return sum
```
Suppose we want to include additional computations before executing func() and utilize its return value in subsequent computations, all without modifying the func() itself. In such cases, we can achieve this by utilizing decorators.

```python
  def decorator(func):
    def wrapper(*args, **kwargs):
      numb = 9
      val = func(*args, **kwargs)
      return val*numb
    return wrapper

  @decorator
  def func(a, b, c = 0):
    sum = a+b+c
    return sum

  print(func(1, 2, c = 3))
```

This will return 54

11. How to make threadsafe generator:

As mentioned in point 9, we cannot create a thread-safe generator in a similar manner as we did for a thread-safe iterator. However, we can achieve thread safety for a generator by creating a thread-safe iterator and encapsulating the generator within it.

```python
import threading
class threadsafe_iter():
  def __init__(self, f):
    self.it = f
    self.lock = threading.Lock()

  def __iter__(self):
    return self

  def __next__(self):
    with self.lock:
      return self.it.__next__()

def threadsafe_generator(f):
  def g(*args, **kwargs):
    return threadsafe_iter(f(*args, **kwargs))
  return g

@threadsafe_generator
def count(n):
  i = 0
  while i < n:
    i += 1
    yield i
  return -1  # End of generator function

```
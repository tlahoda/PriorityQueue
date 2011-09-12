Priority Queue
==============
PriorityQueue is a bi-directional priority queue implemented in
terms of a radix sort. pop, top, empty, and size have a constant
time complexity. pop_all has a O(n) complexity where n is the
number of unique priorities currently in the queue. push has a
typical complexity of O(log k*Np) and a worst case complexity of
O(2*log k*Np) where k is the maximum number of digits a priority
may have and Np is the size of the set of priorities having the
same number of digits as the priority being pushed.

Algorithm Details
-----------------
Radix sort is a multi-pass distribution sort that distributes based
on the individual digits in a key. The first pass distributes based
on the number of digits in the key. The second pass distributes
based on the lexicographic ordering of the keys. The elements are
inserted into the bucket with insertion order maintained.

####Example:
The following code pushes a string "foo" with a priority of "300" onto
the priority queue the elements bucket in with lower priorities being
the highest priorities.

```c++
MinPriorityQueue<string> queue;  
queue.push ("300", "foo");
```

First the bucket for priorities consisting of three digits is located.
Then the bucket for the priority "300" is located in it. Finally "foo" is
pushed onto the end of the priority "300" bucket.

Implementation Details
----------------------

PriorityQueue uses a map of maps of lists as a data store. The
map containing the maps of lists uses the number of digits of the
priorities as its key. 

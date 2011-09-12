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
on the individual digits in a key. The first pass of PriorityQueue's
implementation of radix sort distributes based on the number of
digits in the key. The second pass distributes based on the
lexicographic ordering of the keys. The elements are inserted into
the second bucket with insertion order maintained.

pop has a constant time complexity. This is achieved by caching the
current highest priority and pruning empty buckets from the structure.
Pruning empty buckets allows for the use of C++'s begin and/or end
iterators to locate the new highest priority which are constant time
operations.

####Example:
The following code pushes a string "foo" with a priority of "300"
onto the priority queue where lower priorities are the highest
priorities. Then "bar" with a priority of "400" is pushed onto the
queue.

```c++
MinPriorityQueue<string> queue;  
queue.push ("300", "foo");
queue.push ("400", "bar");
```

For the first push the bucket for priorities consisting of three
digits is first located. Then the bucket for the priority "300" is
located in it. Finally "foo" is pushed onto the end of the priority
"300" bucket.

For the second push the bucket for priorities consisting of three
digits is first located. Then the bucket for the priority "400" is
located in it. Finally "bar" is pushed onto the end of the priority
"400" bucket.

Implementation Details
----------------------

PriorityQueue uses a map of maps of lists as a data store. The
map containing the maps of lists uses the number of digits of the
priorities as its key. 

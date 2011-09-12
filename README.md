Priority Queue
==============
PriorityQueue is a bi-directional priority queue implemented in
terms of a radix sort. 

Algorithm Details
-----------------
Radix sort is a multi-pass distribution sort that distributes based
on the individual digits in a key. The first pass of PriorityQueue's
implementation of radix sort distributes based on the number of
digits in the key. The second pass distributes based on the
lexicographic ordering of the keys. The elements are inserted into
the second bucket with insertion order maintained.

Implementation Details
----------------------

PriorityQueue uses a map of maps of lists as a data store. 

Complexities 
------------

####push - O(log k*n) typical, O(2*log k*Np) worst case
push has a typical complexity of O(log k*n) where k is the maximum
number of digits a priority may have and n is the number of unigue 
priorities currently in the queue having the same length as the
priority being pushed. Worst case complexity is O(2*log k*Np) where
k is the maximum number of digits a priority may have and Np is the
size of the set of priorities having the same number of digits as
the priority being pushed. This occurs when both a digits bucket
has to be created and a priority bucket has to be created. This is 
guaranteed to occur the first time a priority is pushed into the
queue.

####pop - O(1)
pop has a constant time complexity. This is achieved by caching the
current highest priority, as well as the buckets in which it resides,
and pruning empty buckets from the structure. Pruning empty buckets
allows for the use of C++'s begin and/or end iterators (constant
time operations) to locate the new highest priority.

If desirable pop can be degraded to O(log k*Np) by not removing empty
buckets. Doing so will improve push's worst case performance to
O(log k*Np) but leave the typical case unchanged. This change will
also leave top as a constant time operation but degrade pop_all to a
worst case O(log n) where n is the size of the set of all priorities.

####top - O(1)
top has a constant complexity. This is acheived by caching the current
highest priority element, the priority bucket it is in and the digits
bucket it is in.

####pop_all - O(n)
pop_all has a O(n) complexity where n is the number of unique
priorities currently in the queue. This is independent of the number
of elements held in the queue and is achieved pruning empty buckets
from the structure and by splicing the remaining element lists then
returning the result.

####empty - O(1)
empty has a constant complexity.

####size - O(1)
size has a constant complexity.

####Example:
The following code pushes a string "bar" with a priority of "400" onto
the priority queue where priorities are in decreasing order.Then "foo"
with a priority of "300" is pushed onto the queue. Finally the highest
priority element is removed from the queue.

```c++
MinPriorityQueue<string> queue;  
queue.push ("400", "bar");
queue.push ("300", "foo");
queue.pop ();
```

For the first push the bucket for priorities consisting of three digits
is first searched for and then when not found created and inserted into
the digits bucket map. Then the bucket for the priority "400" is 
searched for and when not found created and inserted into the three 
digits bucket. Finally "bar" is pushed onto the end of the priority
"400" bucket.

For the second push the bucket for priorities consisting of three digits
is first located (it was created during the first push). Then the bucket
for the priority "300" is searched for and when not found created in the
three digits bucket. Finally "foo" is pushed onto the end of the priority
"300" bucket.

The pop returns the element with the highest priority which is "foo"
having a priority of "300". "foo" is cached so retrieving and returning
it are a constant time operation. Since the priority bucket in which
"foo" resides is also cached and now empty, it is pruned which is a
constant time operation. Determining the next highest priority is done by
grabbing the first digits bucket in the map, then the first priority
bucket, finally grabbing the first element on the element list.

examples/priority_queue.cpp
---------------------------

priority_queue.cpp contains a usage example of both the MinPriorityQueue
and the MaxPriorityQueue. So far I have only tried building the example on
g++ version 4.5.2 with C++0x enabled. The following command line should
work to compile the example:

```bash
g++ -Wall -std=gnu++0x examples/priority_queue.cpp -I. -o example
```

You can run the resultant executab;e with the following command:

```bash
./example
```

#####output:
```
MinPriorityQueue internal structure:  
1  
        1  
                1  
2  
        20  
                2a  
                2b  
                2c  
        30  
                3  
        40  
                4  
3  
        500  
                5  
        600  
                6c  
                6a  
                6b  

Min pop_all:  
1  
2a  
2b  
2c  
3  
4  
5  
6c  
6a  
6b  

  MaxPriorityQueue internal structure:  
  1  
  1  
  1  
  2  
  20  
  2a  
  2b  
  2c  
  30  
  3  
  40  
  4  
  3  
  500  
  5  
  600  
  6c  
  6a  
  6b  

Max pop:
6c
6a
6b
5
4
3
2a
2b
2c
1
```


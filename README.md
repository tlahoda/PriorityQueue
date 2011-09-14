Priority Queue
==============
PriorityQueue is a bi-directional priority queue implemented in terms of
a radix sort. 

Algorithm Details
-----------------
Most radix sorts are multi-pass distribution sorts that distribute based
on the individual digits in a key. PriorityQueue distributes based on the
number of digits in a priority and the lexicographic order of the
priorities. 

The first level of buckets is a vector. Indexing into a vector is a
constant time operation so this level of buckets does not effect the
complexity. The next level is a map which introduces the logarithmic
component to the comlexity. The final level of buckets is a list. Since a
list's insert and erase operations are constant time this last level of
buckets does not effect the complexity.

The elements are pushed onto the end of the lists which allows for
stability to be maintained.

Implementation Details
----------------------
PriorityQueue uses a vector of maps of lists as a data store. 

Complexities 
------------

####push - O(log p)
push has a complexity of O(log p) where p is the number of unique 
priorities currently in the queue having the same length as the
priority being pushed. 

####pop - O(k)
pop has a complexity of O(k) where k is the maximum number of digits
a priority will have. This is achieved by caching the current highest
priority, as well as the priority bucket in which it resides, and
pruning empty priority buckets from the structure. Pruning empty
priority buckets allows for the use of C++'s begin and/or end
iterators (constant time operations) to help locate the new highest
priority.

####top - O(1)
top has a constant complexity. This is acheived by caching the current
highest priority element and the priority bucket it is in.

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
is located in the digits bucket vector. Then the bucket for the priority
"400" is searched for. When it is not found a new bucket is created in 
the correct place in the priority map. Finally "bar" is pushed onto the
end of the priority "400" bucket.

For the second push the bucket for priorities consisting of three digits
is first located in the digits vector. Then the bucket for the priority
"300" is searched for. When not found it is created in the correct place
in the three digits bucket. Finally "foo" is pushed onto the end of the
priority "300" bucket.

The pop returns the element with the highest priority which is "foo"
having a priority of "300". "foo" is cached so retrieving and returning
it are a constant time operation. Since the priority bucket in which
"foo" resides is also cached and now empty, it is pruned which is a
constant time operation. Determining the next highest priority is done by
searching for the first digits bucket that is not empty then grabbing the
first priority bucket in it and caching the first element in its list.

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
  digits - 0
    priority - 1
      element - 1

  digits - 1
    priority - 20
      element - 2a
      element - 2b
      element - 2c
    priority - 30
      element - 3
    priority - 40
      element - 4

  digits - 2
    priority - 500
      element - 5
    priority - 600
      element - 6c
      element - 6a
      element - 6b

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
  digits - 0
    priority - 1
      element - 1

  digits - 1
    priority - 20
      element - 2a
      element - 2b
      element - 2c
    priority - 30
      element - 3
    priority - 40
      element - 4

  digits - 2
    priority - 500
      element - 5
    priority - 600
      element - 6c
      element - 6a
      element - 6b

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


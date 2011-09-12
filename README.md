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

PriorityQueue uses a map of maps of lists as a data store. The
map containing the maps of lists uses the number of digits of the
priorities as its key. 

Complexities 
------------

####push
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

####pop
pop has a constant time complexity. This is achieved by caching the
current highest priority and pruning empty buckets from the structure.
Pruning empty buckets allows for the use of C++'s begin and/or end
iterators (constant time operations) to locate the new highest
priority.

####top
top has a constant complexity. This is achieved as a result of caching
the current highest priority element.

####pop_all
pop_all has a O(n) complexity where n is the number of unique
priorities currently in the queue. This is independent of the number
of elements held in the queue and is achieved by splicing the element
lists and returning the result.

####empty
empty has a constant complexity.

####size
size has a constant complexity.

####Example:
The following code pushes a string "foo" with a priority of "300"
onto the priority queue where lower priorities are the highest
priorities. Then "bar" with a priority of "400" is pushed onto the
queue. Finally the highest priority element is removed from the queue.

```c++
MinPriorityQueue<string> queue;  
queue.push ("400", "bar");
queue.push ("300", "foo");
queue.pop ();
```

For the first push the bucket for priorities consisting of three
digits is first located or created. Then the bucket for the priority
"400" is located or created in it. Finally "bar" is pushed onto the
end of the priority "400" bucket.

For the second push the bucket for priorities consisting of three
digits is first located (it was created during the first push). Then
the bucket for the priority "300" is located or created in it. Finally
"foo" is pushed onto the end of the priority "300" bucket.

The pop returns the first element highest priority which is "foo"
having a priority of "300". "foo" is cached so retrieving and
returning it are a constant time operation. The priority bucket and
the digits bucket in which "foo" is cached are also cached so removing
them is a constant time operation. Determining the next highest
priority is done using C++'s begin and/or end iterators which are
contant time operations.


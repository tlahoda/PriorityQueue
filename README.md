Priority Queue
==============

PriorityQueue is a bi-directional priority queue implemented in
terms of a least significant digit radix sort. pop, top, empty,
and size have a constant time complexity. pop_all has a O(n) 
complexity where n is the number of unique priorities currently
in the queue. push has a typical complexity of O(log k*Np) and a 
worst case complexity of O(2*log k*Np) whre k is the maximum
number of digits a priority may have and Np is the size of the set
of priorities having the same number of digits as the priority 
being pushed.

Implementation Details
----------------------

PriorityQueue uses a map of maps of lists as a data store. The
map containing the maps of lists uses the number of digits of the
priorities as its key. 

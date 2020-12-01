# Interview Prep
Data Structures, Sorting Algorithms, Runtimes, Interview Questions and overall prep for coding interviews.

---
## Data Structures

### BINARY SEARCH TREE
#### Useful for: 
Sorting data and everything, including rebalancing, can be done in O(log n).
#### Notes: 
Generally use unique values (don't want duplicates).

#### Time Complexity:
| Operation   | Average     | Worst       | 
| ----------- | ----------- | ----------- |
| Insert      | O(log n)    | O(n)        |      like if we have a linked-list
| Remove      | O(log n)    | O(n)        |
| Search      | O(log n)    | O(n)        |

-
### ARRAYS
#### Useful for: 
Storing and accessing sequential data, temporarily storing, as an IO buffer
(when reading from a file), lookup table, and hack for multiple return values.

#### Notes: 
Can implement a dynamic arrays from static ones by continuously allocating double the space
once the array is full.

#### Time Complexity:
| Operation   | Average     | Worst       | 
| ----------- | ----------- | ----------- |
| Access      | O(1)        | O(1)        |
| Append      | ---         | O(1)        | scales well
| Insert      | ---         | O(n)        | if insert to front, have to shove everything over
| Remove      | ---         | O(n)        | to remove an item, create new array and copy over vals to keep
| Search      | O(n)        | O(n)        |


### LINKED-LISTS
#### Useful for: 
Useful in lists, queues, and stacks. Often used for circular (round robin) or adjacency lists.

#### Notes: 
Singly-linked will save up on space and it's simpler to implement 
but it can make it more difficult to access previous nodes.
Doubly-linked takes up double the space since we have 2x the pointers but easier to traverse backwards.

#### Time Complexity:
| Operation   | Average     | Worst       | 
| ----------- | ----------- | ----------- |
| Insert (T/H)| O(1)        | O(1)        | for inserting at the head or tail
| Insert      | O(n)        | O(n)        | for items in the middle, need to traverse
| Remove      | O(n)        | O(n)        | 
| Search      | O(n)        | O(n)        |


### STACKS
#### Useful for: 
Useful for undo functions, checking for matching braces, other syntax (or TMs), supports recursion 
behind the scenes, and is used in DFS on a graph.

#### Notes: 
Has 2 primary operations: push and pop. Last in, first out: what you most recently pushed will be
what comes out when you pop.

#### Time Complexity:
| Operation   | Average     | Worst       | 
| ----------- | ----------- | ----------- |
| Push        | O(1)        | O(1)        | 
| Pop         | O(1)        | O(1)        | 
| Peek/Top    | O(1)        | O(1)        | 
| Search      | O(n)        | O(n)        | scan all elements if not on top


### QUEUES
#### Useful for: 
Used to model a real-world queue like standing in line, a sequence of elements, web server 
manager for first come, first serve, or BFS graph traversal.

#### Notes: 
It's a linear data structure with has 2 main operations: dequeue ("polling") and enqueue ("offering"). 
You remove elements from the front and add elements to the back. Often done via singly-linked list since
arrays (static) might not be big enough.

#### Time Complexity:
| Operation   | Average     | Worst       | 
| ----------- | ----------- | ----------- |
| Enqueue     | O(1)        | O(1)        | 
| Dequeue     | O(1)        | O(1)        | 
| Peek/Top    | O(1)        | O(1)        | 
| Contains    | O(n)        | O(n)        | might need to scan thru all elements
| Remove      | O(n)        | O(n)        |


### HASH MAP
#### Useful for: 
Helpful for tracking item frequencies, if large files have equal contents (without opening files), 

#### Notes: 
Provides a mapping from keys to values via hashing (called a "key-value" pair where keys are unique). 
Keys are immutable.

#### Collision Resolution Methods:
1. Open Addressing: Find another place within hash table by using an offset from original hash.

2. Separate Chaining: Use a separate data structure like a list to hold all different values (key-value pairs).


#### Time Complexity:
| Operation   | Average     | Worst       | 
| ----------- | ----------- | ----------- |
| Lookup      | O(1)        | O(n)        | lots of hash collisions
| Remove      | O(1)        | O(n)        | 
| Insert      | O(1)        | O(n)        | 

---
## Sorting Algorithms

### Insertion Sort
#### Useful for: 
...
#### Time Complexity:
| Best        | Average     | Worst       | Space       | 
| ----------- | ----------- | ----------- | ----------- |
| O(n)        | O(n^2)      | O(n^2)      | O(1)        | 

### Selection Sort
#### Useful for: 
...
#### Time Complexity:
| Best        | Average     | Worst       | Space       | 
| ----------- | ----------- | ----------- | ----------- |
| O(n^2)      | O(n^2)      | O(n^2)      | O(1)        | 

### Merge Sort
#### Useful for: 
Ideal for combining lists.
#### Time Complexity:
| Best        | Average     | Worst       | Space       | 
| ----------- | ----------- | ----------- | ----------- |
| O(nlogn)    | O(nlogn)    | O(nlogn)    | O(n)        | 

### Quick Sort
#### Useful for: 
...
#### Time Complexity:
| Best        | Average     | Worst       | Space       | 
| ----------- | ----------- | ----------- | ----------- |
| O(nlogn)    | O(nlogn)    | O(n^2)      | O(logn)     | 

### Heap Sort
#### Useful for: 
Can be chosen over quick sort because, in the case of a partially sorted array, it's worst case will always be O(nlogn) not O(n^2).
#### Time Complexity:
| Best        | Average     | Worst       | Space       | 
| ----------- | ----------- | ----------- | ----------- |
| O(n)        | O(nlogn)    | O(nlogn)    | O(1)        | 

---
## Other Notes
#### BFS Graph:
Start at a node, add its neighbors to queue, and visit their neighbors (add to queue). 
We know if all nodes have been visited by marking them as visited (bool).

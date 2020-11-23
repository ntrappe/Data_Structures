# Data_Structures
Prep for coding interviews

## Binary Search Tree
#### Useful for: 
Sorting data and everything, including rebalancing, can be done in O(log n).
#### Notes: 
Generally use unique values (don't want duplicates).

#### Time Complexity:
| Operation   | Average     | Worst       | 
| ----------- | ----------- | ----------- |
| Insert      | O(log n)    | O(n)        | like if we have a linked-list
| Remove      | O(log n)    | O(n)        |
| Search      | O(log n)    | O(n)        |


## Arrays
#### Useful for: Storing and accessing sequential data, temporarily storing, as an IO buffer
(when reading from a file), lookup table, and hack for multiple return values.

#### Notes: 

#### Time Complexity:
| Operation   | Average     | Worst       | 
| ----------- | ----------- | ----------- |
| Access      | O(1)        | O(1)        |
| Append      | ---         | O(1)        | scales well
| Insert      | ---         | O(n)        | if insert to front, have to shove everything over
| Remove      | ---         | O(n)        | to remove an item, create new array and copy over vals to keep
| Search      | O(n)        | O(n)        |

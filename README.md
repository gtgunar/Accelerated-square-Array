# Accelerated-square-Array
Sequential data structure

A new data structure, aimed to have a constant peek time, and sqrt(n) mutation time*, where n is the number of contained elements.
It works by instead of storing a single vector of elements, it stores a vector of vector-s.
The "upper" vector (which stores the references) approximately contains sqrt(n) amount of elements, and the lower vectors also have
Approximately sqrt(n) elements. This makes sqrt(n) mutation time possible, by only needing to mutationt in the middle
of one sqrt(n) long vectors, and then carry at most sqrt(n) changes trough.

a,b,c,d are vectors stored by address in the upper vector, with their respective content below them, from bottom up (underscore being the next insertion point and 11 being the next deletion point in both cases).

order of growth:

a b c d

7 8 9 _

3 4 6 11

1 2 5 10 

order of data:

a b c d

3 6 9 _

2 5 8 11

1 4 7 10

Balancing:
since elements are considered to be in the order of the containing vectors, and then, in the order within those vectors,
One can pop off an element from the end of a vector, and push it onto the beginning of the next in line**, without changing the order.
Likewise, the same can be done by popping at the front, and then pushing to the end of the one earlier element within the upper array.
By doing this if necessary, any arbitrary insertion can be followed by shifting the extra element, to the proper place for insertion
without changing order.

preffered shape:
The preffered shape is a square that grows first to a new array to the right (new array at the end), then increments every member in order***. When the new array is at last incremented, a new square shape is reached. 
x is the integer part (downround/floor) of the square root of n.
Assuming an x long, x tall perfect square, it takes x new elements for the next vector to reach the height of the other vectors, and then, 
it takes x+1 elements, to increment each of the member vectors, corresponding to the relation between an x and x+1 sided square:
x^2+2*x+1=(x+1)^2.

Insertion:
insertion happens by finding the vector where the insertion index belongs, then inserting there, to the correct place, 
and then doing a balancing as necesseary.
Since the number of blocks, and the amount of them being incremented is only dependent on n, 

  one can easily find the correct insertion point:
  division of index by x, if the loading is happening at the x+1-th vector(it is the case if n-x*x<x).
  in other case: division by x+1. If the correct block is less than the increment count, then the division gives the correct block.
  if it is bigger, the incremented part's total population should be subtracted from the index,
  and the rest should be divided by x, then the incrementcount added to it.
  by instead of divisions, using modulo, one can get the place within the correct vector as well.

Deletion:
happens in a similar manner as insertion, but looks for the place of balance, at a 1 earlier position.

Access/Peek:
Correct place is calculated like in insertion, but no balancing is needed, not even on writing.

notes:
  -Since many intermediate calculation only depends on n, 
  one can easily cache them, and even check if they need updating at all.
  -since serial peek means accessing a member vector serially, it has an almost equal cache coherence compared to a regular vector.
  -mutation at the end is either constant time, or sqrt(n)/2 on average( both cases have 50% chance).
  -the accelerated square array is faster than the hashed array tree, as insertion in the middle is linear time for the latter.
  
*The same concept can be taken further, by using more, C amount of indirection, 
to have constant C access time and C-th root of N delete/insert time.
  Doing so, dynamically, can make the balance&tradeoffs, between access and insert/delete by modified on the fly.
  For eg.:C=1 amount of indirection leads to an ordinary vector.

**Assuming proper memory management, just in time creation of new members or some other means of handling the special case of balancing
to beyond the last element.

***incrementing a vector:here it means, adding 1 element



Illustration for theoretical speed comparison, between: the accelerated square array, ordinary vectors, and balanced trees, assuming worst case,with manually adjustable relative commonness, of peek, and imutation:

https://www.desmos.com/calculator/v7auxvylnh

S=1.0:peek only

S=0.0:mutation only


Márton Attila,2023

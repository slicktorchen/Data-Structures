HOMEWORK 8: QUAD TREES AND TREE ITERATION


NAME:  Victor Chen


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

Philip Kamei, Euan McInally

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  20 hours



ORDER NOTATION ANALYSIS: 
Give the big O notation of each of the QuadTree operations and justify
your answer for the non trivial operations (please be concise!)
Analyze both the running time and the additional memory usage needed
(beyond the space allocated for the existing tree structure).  You may
assume that the tree is reasonably well balanced for all operations.


n = the number of elements in the tree


size()
  running time: O(1)  
  memory usage: O(1)

insert()
  running time: O(logn) when searching the tree for the right location to place a point
	in the tree, it follows a single path down a tree to find this location
  memory usage: O(logn) since this function is recursive, each time the function is called
	memory is taken up on the call stack

find()
  running time: O(logn) when searching the tree for a point, it follows a single path 
	down a tree to find the point
  memory usage: O(logn) since this function is recursive, each time the function is called
	memory is taken up on the call stack

height()
  running time: O(nlogn) to determine the longest path to a leaf node, the function 
	needs consider all possible paths to each of the 
  memory usage: O(logn) although the function checks each of the nodes, the memory used
	in the call stack never exceeds the size of the height of the tree as recursive 
	function calls are removed after completion 

begin()
  running time: O(n) when begin is called and an iterator is constructed, the iterator
	constructor calls the depth_first function which recurses through each node of the
	tree and creates a list sorted in depth first order of the tree
  memory usage: O(n) the resulting list created takes up new allocated memory

end()
  running time: O(1)
  memory usage: O(1)

bf_begin()
  running time: O(n) when bf_begin is called and an iterator is constructed, the iterator
	constructor calls the breadth_first function which iterates through each node of the
	tree and creates a list sorted in breadth first order of the tree
  memory usage: O(n) the resulting list created takes up new allocated memory

bf_end()
  running time: O(1)
  memory usage: O(1)

operator++()
  running time: O(n) the operator iterates through either the df_list or bf_list and finds
	where the current pointer is pointing. the operator then moves the pointer one node over
  memory usage: O(1) no new data is created in this process

operator*()
  running time: O(1)
  memory usage: O(1)

getLabel()
  running time: O(1)
  memory usage: O(1)

getDepth()
  running time: O(logn) the function follows parent pointers up the tree to the root
  memory usage: O(1) no new data is created in this process

copy constructor
  running time: O(n) the copy function must travel to each of the nodes in the tree 
	in order to make a complete copy of the tree
  memory usage: O(n) since this function is recursive, each time the function is called
	memory is taken up on the call stack. since this function is called the number of 
	times equivalent to the number of nodes in the tree, the order is O(n)

assignment operator
  running time: O(n) the assignment operator calls both copy constructor and destructor,
	but at separate instances so the running times and memory usage is same
  memory usage: O(n) ^same reason 

destructor
  running time: O(n) the destructor must travel to each of the nodes in the tree 
	in order to delete each of the nodes of the tree
  memory usage: O(n) since this function is recursive, each time the function is called
	memory is taken up on the call stack. since this function is called the number of 
	times equivalent to the number of nodes in the tree, the order is O(n)



EXTRA CREDIT:  TREE BALANCING
How does the point insertion order affect the shape of the resulting
QuadTree object? What are specific examples of the worst case and best
case?  Discuss your stratgy for reordering the input to rebalance the
tree.  Paste example output with and without your rebalancing.






MISC. COMMENTS TO GRADER:  
(optional, please be concise!)



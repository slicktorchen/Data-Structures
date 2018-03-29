HOMEWORK 5: MULTI LINKED LISTS


NAME:  Victor Chen


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

Pierre Fabris

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  20 hours



TESTING & DEBUGGING STRATEGY:
Please be concise!  



ORDER NOTATION of the member functions of MultiLL?
(in terms of n, the number of elements currently in the list)

default constructor
O(1) since the only operation is setting 6 variables to their default values

copy constructor
O(n^2) when a copy is made, a while loop traverses the old MultiLL and copies the
value of the old Node by calling add function which creates and places a new Node 
in the new MultiLL. The add function also uses a while loop to fix the sort pointers. 
Thus, this involves a nested loop which is O(n^2)

assignment operator
O(n^2) the assignment operator calls the copy operator and the destroy operator and they
are O(n^2) and O(n) respectively, but are called on separate instances. The assignment operator copies 
the old MultiLL into a new MultiLL and destroys the old MultiLL. Since O(n^2) is the 
greatest order, the entire function falls into O(n^2).

destructor
O(n) the destructor traverses the list chronologically and deletes each Node as the
function passes each Node.

size
O(1) the function just returns the value of one MultiLL class variable.

empty
O(1) the function just returns the value of one MultiLL class variable.

clear
O(n) calls the destructor function which is O(n)

add
O(n) inserting the new Node at the end of the chronological list is O(1) because no 
searching is required, but to find the right location to put the new Node in the sorted 
list, function traverses the list [O(n)] to the right position and arranges the sorted_next 
and sorted_prev pointers accordingly.

erase
O(n) to set the random_next pointer, the function needs to traverse the list until it 
returns back to the Node the iterator is pointing to because the random list is a
singly linked circular list. The rearranging of pointers for the chrono and sorted list
is only O(1) since no list traversing is required.

begin_chronological
O(1) the function just returns the value of one MultiLL class variable.


end_chronological
O(1) the function just returns the value of one MultiLL class variable.

begin_sorted
O(1) the function just returns the value of one MultiLL class variable.

end_sorted
O(1) the function just returns the value of one MultiLL class variable.

begin_random
O(n^2) first the function traverses the random list and resets all of the random_next 
pointers in the random list to NULL. This for loop is O(n). But in creating a new
random order, a nested for loop is used. The first for loop loops the number of times
corresponding to the number of items in the list, for each item needs to have their
random_next pointer set. The nested while loop traverses the chrono list the number of 
times the random number generator generates.

ITERATOR INVALIDATION:
In what cases will iterators of the MultiLL be invalidated?  Justify
the need for each of the restrictions placed on your implementation.

Some cases in which iterators will be invalidated is in the erase function where two
iterators pointing to the same item and one of the iterators is erased and now one 
of the iterators is now pointing to invalid data. Another case could be in the add
function when a random iterator is created pointing to a new Node is added to the list. 
This iterator is invalidated because this new Node is not a part of the random list 
yet because the add function does not create a pointer to and from this new Node.




EXTRA CREDIT: 
Which function in your implementation can be improved by a
non-insertion sort sorting method?  Describe.




MISC. COMMENTS TO GRADER:  

When submitting my code to the HW server, there appears to be a memory error that does
not occur when I test the code on Dr. Memory on my computer. It has really been bugging
me and I'm curious if you would know what is causing the issue.



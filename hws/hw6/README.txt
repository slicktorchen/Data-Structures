HOMEWORK 6: BATTLESHIP RECURSION


NAME:  Victor Chen



COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

Pierre Fabris

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  30 hours



ANALYSIS OF PERFORMANCE OF YOUR ALGORITHM:
(order notation & concise paragraph, < 200 words)

The dimensions of the board (w and h) :
O(s*(w^2)*(h^2)) the place_ships function traverses all points in the board twice
using two nested for loops. One nested for loop in finding a location to 
place the ship and another nested for loop called by print_result within 
the first nested for loop to print out the board.
Since this is done recursively, the for loops are nested s times where s is the 
total number of ships

The number of ships (s)? 
Same as the case above O(s*(w^2)*(h^2)) for the exact same reasons

The total number of occupied cells (o) or open water (w)? 
Has no especially significant affect on the order notation of the algorithm

The number of constraints (c)? 
O(s*(w^2)*(h^2)) while checking the constraints in the save_results function,
a for loop checks each of the positions of the board, but this nested loop 
does not raise the order as much as the nested for loop in the print_result 
function

The number of unknown sums (u) or unspecified ship types (t)? 
N/A did not do unknowns




SUMMARY OF PERFORMANCE OF YOUR PROGRAM ON THE PROVIDED PUZZLES:
# of solutions & approximate wall clock running time for different
puzzles for a single solution or all solutions.



MISC. COMMENTS TO GRADER:  
(optional, please be concise!)



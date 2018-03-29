HOMEWORK 9:  PRIORITY QUEUES FOR MESH SIMPLIFICATION


NAME:  Victor Chen


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

Philip Kamei, LMS, Office Hours, Prof Thompson, Pierre Fabris

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  30 hours


ALGORITHM ANALYSIS: 
Assume v_0 vertices, e_0 edges, and e_0 triangles in the initial mesh,
reduced to t_final triangles using the -shortest criteria.  What is
the overall order notation for the program?  Analyze the separate
compoenents of the program to justify your answer.

ALGORITHM ANALYSIS -- LINEAR:

O(e_0) this is the overall order notation for the program because program will iterate
throughout the entire mesh to find the shortest edge to collapse




ALGORITHM ANALYSIS -- PRIORITY QUEUE:

O(log(e_0)) this is the overal order notation for the program because instead of iterating
through the entire mesh, it just takes the top value in the priority queue which takes O(1),
but in doing so, it takes out the min value of the priority queue using the function pop. 
Since the priority queue structure needs to be updated, percolate down is called to 
reset the elements of the queue with the next shortest Edge at the top, ready to be used. 
This percolating down each takes O(logn), and since this is the most expensive function used
in priority queue, the program is order O(log(e_0))



EXTRA CREDIT:  COLOR & OVERALL APPERANCE
Discuss the quality of your results in your README.txt and include
screenshots of your more impressive results.  If you have submitted
screenshots, give the file names and describe the results.



MISC. COMMENTS TO GRADER:  
Optional, please be concise!







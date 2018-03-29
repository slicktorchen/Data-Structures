HOMEWORK 7: MINIBLAST


NAME:  Victor Chen


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

Pierre Fabris, Philip Kamei

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  8 hours



ANALYSIS OF PERFORMANCE OF YOUR ALGORITHM:
(order notation & concise paragraph, < 200 words)

L = length of the genome sequence
q - query length
p - number of different locations where key is found
k - key size (k-mer size)
n - number of queries


How much memory will the map data structure require (order notation for memory use)?
	
	O(n) size of the map depends on the number of queries that are being searched 
	For each query that is being searched in the sequence, a new pair is created in
	the map 


What is the order notation for performance (running time) of each of
the commands?

	read genome from filename: O(L) as the sequence is read by lines of sequence segments

	find kmer indices in sequence: O(L) a for loop iterates through the entire sequence string
	finding the locations of a kmer

	find query allowing m mismatches: O(p * (q - k)) a nested for loop is used to find queries;
	the first for loop iterates through the indices of kmer locations and the second for loop 
	nested within this loop checks all the characters after the kth character of the query with 
	the actual sequence.

	quit: O(1) program ending independent of the size of the data


EXTRA CREDIT
Add a new command to implement the database using one of the other
 data structures that we have covered so far in the course: 
vectors, lists, arrays etc. 

Compare the performance your alternative method to the homework method
by making a table of run times for each of the genomes and query 
sets provided with the homework  and compare the times to build
the index and the times to process the queries. 
Document any new commands you have added in your README file.



MISC. COMMENTS TO GRADER:  
(optional, please be concise!)



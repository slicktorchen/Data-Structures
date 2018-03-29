HOMEWORK 4: GROCERY LISTS


NAME:  Victor Chen


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

TA and Mentors at Wednesday 4-6 office hours

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  30 hours



ORDER NOTATION:
For each request/command,

i = # of different ingredients in the kitchen
u = maximum units of a single ingredient in the kitchen
r = # of different recipes
k = maximum # of different ingredients in a single recipe
v = maximum units of single ingredient in a single recipe
a = maximum # of different ingredients added with a single ’a’ command 
w = maximum units of a single ingredient added with a single ’a’ command


command 'r' / add a recipe:
O(n^2) because there is a for loop nested in a for loop, one included in the Recipe function "addIngredient"
O(k * k) because one for loop goes through the ingredients of a recipe and loops through the ingredients of 
	the recipe to make sure the ingredient doesn't already exist

command 'a' / add ingredients to the kitchen:
O(n^2) because there is a for loop nested in a for loop, one included in the Kitchen function "addIngredient"
O(k * k) the for loops iterate through the k different ingredients twice

command 'p' / print a recipe:
O(n) although in the function "printRecipe" within the Recipe class, a sort is done, a the for loop
	through the list of recipes is more expensive
O(r) because the for loop goes through a list of recipes

command 'm' / make a recipe:
O(n^2) because there are two independent nested for loops, one included in the Kitchen function
	"checkEnough" and another in "amountNeeded"
O(k * i) because in checking whether there are enough ingredients in the kitchen for the recipe,
	a for loop going through the list of ingredients of the recipe and compares each corresponding 
	ingredient in the kitchen using another for loop

command 'k' / print the contents of the kitchen:
O(n) although in the function "printRecipe" within the Recipe class, a sort is done, a the for loop
	through the list of recipes is more expensive
O(i) because the for loop goes through a list of different ingredients in the kitchen

command 's' / suggest recipes:
O(n^3) because there is a for loop nested in a for loop nested in a for loop, one is in the "recipeSuggestions" 
	function which calls a nested for loop is in the Kitchen "checkEnough" function
O(r * k * i) because a for loop goes through a list of recipes, another loop goes through the ingredients of the recipe,
	and another loop goes through the ingredients in the kitchen

(extra credit) command 'd' / suggest dinner menu:



EXTRA CREDIT:
Describe your implementation of the "suggest dinner menu" option.



MISC. COMMENTS TO GRADER:  
(optional, please be concise!)



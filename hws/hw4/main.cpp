// File:     main.cpp
// Purpose:  To read input file and write to output file using classes
//			 Ingredient, Recipe, and Kitchen


#include <cassert>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <list>
#include <iterator>
#include <string>

#include "recipe.h"
#include "kitchen.h"
#include "ingredient.h"

using namespace std;

// Helper functions
void readRecipe(std::istream &istr, std::ostream &ostr, std::list<Recipe> &recipes);
void addIngredients(std::istream &istr, std::ostream &ostr, Kitchen &kitchen);
void printRecipe(std::istream &istr, std::ostream &ostr, const std::list<Recipe> &recipes);
void makeRecipe(std::istream &istr, std::ostream &ostr, const std::list<Recipe> &recipes, Kitchen &kitchen);
void recipeSuggestions(std::ostream &ostr, const std::list<Recipe> &recipes, Kitchen &kitchen);
void dinnerSuggestions(ostream &ostr, const list<Recipe> &recipes, Kitchen &kitchen);

// The main loop parses opens the files for I/O & parses the input
int main(int argc, char* argv[]) {

  // Check the number of arguments.
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " in-file out-file\n";
    return 1;
  }
  // Open and test the input file.
  std::ifstream istr(argv[1]);
  if (!istr) {
    std::cerr << "Could not open " << argv[1] << " to read\n";
    return 1;
  }
  // Open and test the output file.
  std::ofstream ostr(argv[2]);
  if (!ostr) {
    std::cerr << "Could not open " << argv[2] << " to write\n";
    return 1;
  }

  // the kitchen & recipe list
  Kitchen kitchen;
  std::list<Recipe> recipes;

  // some variables to help with parsing
  char c;
  while (istr >> c) {
    if (c == 'r') {
      // READ A NEW RECIPE
      readRecipe(istr,ostr,recipes);

    } else if (c == 'a') {
      // ADD INGREDIENTS TO THE KITCHEN
      addIngredients(istr,ostr,kitchen);
      
    } else if (c == 'p') {
      // PRINT A PARTICULAR RECIPE
      printRecipe(istr,ostr,recipes);

    } else if (c == 'm') {
      // MAKE SOME FOOD
      makeRecipe(istr,ostr,recipes,kitchen);

    } else if (c == 'k') {
      // PRINT THE CONTENTS OF THE KITCHEN
      kitchen.printIngredients(ostr);

    } else if (c == 's') {
      // SUGGEST ALL RECIPES THAT CAN BE MADE INDIVIDUALLY FROM THE
      //   CURRENT CONTENTS OF THE KITCHEN
      recipeSuggestions(ostr,recipes,kitchen);

    } else if (c == 'd') {
      // EXTRA CREDIT: SUGGEST THE COLLECTION OF RECIPES THAT CAN BE
      // MADE TOGETHER THAT USE THE MAXIMUM NUMBER OF UNITS OF
      // INGREDIENTS
		dinnerSuggestions(ostr,recipes,kitchen);
    } else {
      std::cerr << "unknown character: " << c << std::endl;
      exit(0);
    }
  }  
}


void readRecipe(std::istream &istr, std::ostream &ostr, std::list<Recipe> &recipes) {
  int units;
  std::string name, name2;  
  istr >> name;
  // check if recipe exists
  list<Recipe>::const_iterator it;
  bool found = false;
  for (it = recipes.begin(); it != recipes.end(); ++it) {
	  if ((*it).getRecipeName() == name) {
		  found = true;
		  break;
	  }
  }
  if (found == false) {
  // build the new recipe
	  Recipe r(name);
	  while (1) {
		istr >> units;
		if (units == 0) break;
		assert (units > 0);
		istr >> name2;
		r.addIngredient(name2,units);
	  }
	  // add it to the list
	  recipes.push_back(r);
	  ostr << "Recipe for " << name << " added" << std::endl;
	// If recipe exists, skip over the next lines 
  } else {
	  while (1) {
		  istr >> units;
		  if (units == 0) break;
		  istr >> name2;
	  }
	  ostr << "Recipe for " << name << " already exists" << endl;
  }		
}


void addIngredients(std::istream &istr, std::ostream &ostr, Kitchen &kitchen) {
  int units;
  std::string name;
  int count = 0;
  while (1) {
    istr >> units;
    if (units == 0) break;
    assert (units > 0);
    istr >> name;
    // add the ingredients to the kitchen
    kitchen.addIngredient(name,units);
    count++;
  }
  if (count == 1) {
	  ostr << count << " ingredient added to kitchen" << std::endl;
  } else {
	  ostr << count << " ingredients added to kitchen" << std::endl;
  }
}


void printRecipe(std::istream &istr, std::ostream &ostr, const std::list<Recipe> &recipes) {
  std::string name;
  istr >> name;
  list<Recipe>::const_iterator it;
  bool found = false;
  // Checks if the recipe exists 
  for (it = recipes.begin(); it != recipes.end(); ++it) {
	  if ((*it).getRecipeName() == name) {
		  found = true;
		  break;
	  } else {
		  found = false;
	  }
  }
  // Prints recipe if it exists
  if (found == true) {
	  (*it).printRecipe(ostr);
  } else {
	  ostr << "No recipe for " << name << endl;
  }
}


void makeRecipe(std::istream &istr, std::ostream &ostr, const std::list<Recipe> &recipes, Kitchen &kitchen) {
  std::string name;
  istr >> name;
  list<Recipe>::const_iterator it_rcp;
  list<Ingredient>::const_iterator it_ing_rcp, it_ing_kit;
  list<Ingredient> ingredients_rcp, ingredients_needed;
  bool found;
  // Identify the recipe to make and store ingredients in a list
  for (it_rcp = recipes.begin(); it_rcp != recipes.end(); ++it_rcp) {
	  if ((*it_rcp).getRecipeName() == name) {
		  found = true;
		  break;
	  } else {
		  found = false;
	  }
  } 
  if (found == true) {
	  ingredients_rcp = (*it_rcp).getIngredients();
  } else {
	  ostr << "Don't know how to make " << name << endl;
	  return;
  }
  // Makes sure there are enough ingredients in the kitchen before removing items from the kitchen
  bool enough;
  enough = kitchen.checkEnough(ingredients_rcp);

  // If there is enough, remove the ingredients from the kitchen
  if (enough == true) { 
	  for (it_ing_rcp = ingredients_rcp.begin(); it_ing_rcp != ingredients_rcp.end(); ++it_ing_rcp) {
		kitchen.removeIngredients(*it_ing_rcp);
	  }
	  ostr << "Made " << name << endl;
	// If there is not enough, find out which ingredients and how much of each are needed
  } else {
	  ingredients_needed = kitchen.amountNeeded(ingredients_rcp,ingredients_needed);
	  ostr << "Cannot make " << name << ", need to buy:" << endl;
	  for (it_ing_rcp = ingredients_needed.begin(); it_ing_rcp != ingredients_needed.end(); ++it_ing_rcp) {
		  ostr << "  " << (*it_ing_rcp).getAmount(); 
		  if ((*it_ing_rcp).getAmount() == 1) {
			  ostr << " unit of ";
		  } else { 
			  ostr << " units of ";
		  } 
		  ostr << (*it_ing_rcp).getName() << endl;
	  }  
  }
}



void recipeSuggestions(std::ostream &ostr, const std::list<Recipe> &recipes, Kitchen &kitchen) {
	list<Recipe>::const_iterator it_rcp, it_poss;
	list<Recipe> possible;
	list<Ingredient> ingredients_rcp; 
	bool enough;
	// Checks if there are enough ingredients to make recipe. If enough, put possible recipes in list of possibles
	for (it_rcp = recipes.begin(); it_rcp != recipes.end(); ++it_rcp) {
		enough = false;
		ingredients_rcp = (*it_rcp).getIngredients();
		enough = kitchen.checkEnough(ingredients_rcp);
		if (enough == true) {
			possible.push_back(*it_rcp);
		}
	}
	possible.sort(sort_rcp);
	// If there are recipes that can be prepared, print them
	if (possible.size() != 0) {
		if (possible.size() == 1) {
			ostr << "Recipe that can be prepared:" << endl;
		} else {
			ostr << "Recipes that can be prepared:" << endl;
		}
		for (it_poss = possible.begin(); it_poss != possible.end(); ++it_poss) {
			ostr << "  " << (*it_poss).getRecipeName() << endl;
		}
	// If there are no recipes that can be prepared, print message
	} else {
		ostr << "No recipes can be prepared" << endl;
	}

}

void dinnerSuggestions(ostream &ostr, const list<Recipe> &recipes, Kitchen &kitchen) {
	list<Recipe>::const_iterator it_rcp, it_poss, it;
	list<Recipe> possible,suggested;
	Recipe total_rcp("total_rcp"), copy("copy");
	list<Ingredient> ingredients_rcp, ingredients_kit = kitchen.getIngredients(), total, copy; 
	list<Ingredient>::const_iterator it_ing1, it_ing2, it_total;
	bool enough;
	for (it = recipes.begin(); it != recipes.end(); ++it) {
		ingredients_rcp = (*it).getIngredients(); 
		for (it_ing1 = ingredients_rcp.begin(); it_ing1 != ingredients_rcp.end; ++it_ing1) {
			for (it_ing2 = total.begin(); it_ing2 != total.end(); ++it_ing2) {
				if ((*it_ing1).getName() == (*it_ing2).getName()) {
					(*it_ing2).addAmount((*it_ing1).getAmount());
				}
			}
			Ingredient newIng((*it_ing1).getName(),(*it_ing1).getAmount());
			total.push_back(newIng);
		}
	}
	
	enough = kitchen.checkEnough(total);
	int min_val = 100;
	while(enough != true && it_total != copy.end()) {
		copy = total
		for (it_total = copy.begin(); it_total != copy.end(); ++it_total) {
			for (it = recipes.begin(); it != recipes.end(); ++it) {
				ingredients_rcp = (*it).getIngredients();
				for (it_ing1 = ingredients_rcp.begin(); it_ing1 != ingredients_rcp.end; ++it_ing1) {
					if ((*it_total).getName() == (*it_ing1).getName()) {
						(*it_total).removeAmount((*it_ing1).getAmount())
					}
				}
			}
		}
		enough = kitchen.checkEnough(copy);
		if (totalIngredients(copy) < min_val) {
			min_val = totalIngredients(copy);
	}


	// Checks if there are enough ingredients to make recipe. If enough, put possible recipes in list of possibles
	//for (it_rcp = recipes.begin(); it_rcp != recipes.end(); ++it_rcp) {
	//	enough = false;
	//	ingredients_rcp = (*it_rcp).getIngredients();
	//	enough = kitchen.checkEnough(ingredients_rcp);
	//	if (enough == true) {
	//		possible.push_back(*it_rcp);
	//	}
	//}
	//possible.sort(sort_rcp);
	//if (possible.size() != 0) {
	//	for (it_poss = possible.begin(); it_poss != possible.end(); ++it_poss) {
	//		ingredients_rcp = (*it_poss).getIngredients();
	//		for (it_ing = ingredients_rcp.begin(); it_ing != ingredients_rcp.end(); ++it_ing) {
	//			total_rcp.addIngredient((*it_ing).getName(),(*it_ing).getAmount());
	//		}
	//	}
	//}
	//list<int> totals;
	//list<int>::iterator it;
	//int total_ing;
	//enough = kitchen.checkEnough(total_rcp.getIngredients());
	//if (enough == false) {
	//	for (it_poss = possible.begin(); it_poss != possible.end(); ++it_poss) {
	//		enough = false;
	//		ingredients_rcp = (*it_poss).getIngredients();
	//		copy = total_rcp;
	//		for (it_ing = ingredients_rcp.begin(); it_ing != ingredients_rcp.end(); ++it_ing) {
	//			copy.removeIngredients(*it_ing);	
	//		}
	//		enough = kitchen.checkEnough(total_rcp.getIngredients());
	//		if (enough == true) {
	//			total_ing = copy.totalIngredients();
	//			totals.push_back(total_ing);
	//			suggested.push_back(*it_poss);
	//		}
	//	}
	//}
	//int min_val = 100;
	//for (it = totals.begin(); it != totals.end(); ++it) {
	//	if (*it < min_val) {
	//		min_val = *it;
	//	}
	//}
	//for (it_poss = suggested.begin(); it_poss != suggested.end(); ++it_poss) {


}


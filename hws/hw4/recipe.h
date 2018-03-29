// File:      recipe.h
// Purpose:   Define and implement the class Recipe

#ifndef recipe_h_
#define recipe_h_

#include <string>
#include <iterator>
#include <list>
#include <fstream>
#include <algorithm>

#include "ingredient.h"

using namespace std;

class Recipe {
public: 
	Recipe(string name) {
		name_ = name;
	}
	Recipe() {
		name_ = "NONE";
	}

	string getRecipeName() const { return name_;}
	list<Ingredient> getIngredients() const { return ingredients_; }

	// Used in creation of a new recipe
	void addIngredient(string item, int units);

	// Used for dinnerSuggestions function
	void removeIngredients(const Ingredient item);

	
	// Prints recipe
	void printRecipe(ostream &ostr) const;
	
private:
	string name_;
	list<Ingredient> ingredients_;
};


void Recipe::addIngredient(string item, int units) {
	list<Ingredient>::iterator it;
	bool found = false;
	// Checks if an ingredient has already been added to the recipe
	for (it = ingredients_.begin(); it != ingredients_.end(); ++it) {
		if ((*it).getName() == item) {
			found = true;
			break;
		}
	}
	// If not in recipe, create a new ingredient and put in the recipe list of ingredients
	if (found == false) {
		Ingredient newIng(item,units);
		ingredients_.push_back(newIng);
		ingredients_.sort(sort_quantity);
	// If exists in recipe, just add quantity to the ingredients in recipe
	} else {
		(*it).addAmount(units);
	}		
}

void Recipe::printRecipe(ostream &ostr) const {
	list<Ingredient>::const_iterator it;
	ostr << "To make " << name_ << ", mix together:" << endl;
	list<Ingredient> sorted_ing = ingredients_;
	sorted_ing.sort(sort_name);
	// Iterates through recipe ingredients and prints out the name/quantity of ingredients
	for (it = sorted_ing.begin(); it != sorted_ing.end(); ++it) {
		ostr <<  "  " << (*it).getAmount() ;
		if ((*it).getAmount() == 1) { 
			ostr << " unit of ";
		} else {
			ostr << " units of ";
		}
		ostr << (*it).getName() << endl;
	}

}

void Recipe::removeIngredients(const Ingredient item) {
	list<Ingredient>::iterator it;
	for (it = ingredients_.begin(); it != ingredients_.end(); ++it) {
		if ((*it).getName() == item.getName()) {
			if ((*it).getAmount() >= item.getAmount()) {
				// Removes amount
				(*it).removeAmount(item.getAmount());

			} 
		}
	}
}

int totalIngredients(const list<Ingredient> ingredients) const {
	list<Ingredient>::const_iterator it;
	int total = 0;
	for (it = ingredients.begin(); it != ingredients.end(); ++it) {
		total += (*it).getAmount();
	}
	return total;
}

// Sorts recipes by name
bool sort_rcp(const Recipe& rcp1, const Recipe& rcp2) {
	if (rcp1.getRecipeName() < rcp2.getRecipeName()) {
		return true;
	} else {
		return false;
	}
}

#endif
// File:     kitchen.h
// Purpose:  Define and implement the class Kitchen

#ifndef kitchen_h_
#define kitchen_h_

#include <string>
#include <iterator>
#include <list>
#include <fstream>

#include "ingredient.h"

using namespace std;

class Kitchen {

public:
	Kitchen() {}

	list<Ingredient> getIngredients() const { return ingredients_; }

	void printIngredients(ostream &ostr) const;
	void addIngredient(string item, int units);

	// Checks if there are enough ingredients to make a recipe
	bool checkEnough (const list<Ingredient> recipe_ing);
	
	// Removes ingredients from the kitchen 
	void removeIngredients(const Ingredient item);

	// Returns a list of Ingredient objects and their corresponding amounts needed 
	list<Ingredient> amountNeeded(const list<Ingredient> recipe_ing, list<Ingredient> needed);

private:
	list<Ingredient> ingredients_;
};

//////////////////////////////////////////////////////////////////////////////////////////////

void Kitchen::printIngredients(ostream &ostr) const {
	list<Ingredient>::const_iterator it;
	list<Ingredient> sorted_ing = ingredients_;
	sorted_ing.sort(sort_quantity);
	ostr << "In the kitchen:" << endl;
	// Iterates through kitchen and prints out the ingredients and their quantities
	for (it = sorted_ing.begin(); it != sorted_ing.end(); ++it) {
		if ((*it).getAmount() == 1) {
			ostr << "  " << (*it).getAmount() << " unit of " << (*it).getName() << endl;
		} else {
			ostr << "  " << (*it).getAmount() << " units of " << (*it).getName() << endl;
		}
	}
}

void Kitchen::addIngredient(string item, int units) {
	list<Ingredient>::iterator it;
	bool found = false;
	// Checks if an ingredient already exists in the kitchen
	for (it = ingredients_.begin(); it != ingredients_.end(); ++it) {
		if ((*it).getName() == item) {
			found = true;
			break;
		}
	}
	// If not found, create a new Ingredient object and put in the kitchen
	if (found == false) {
		Ingredient newIng(item,units);
		ingredients_.push_back(newIng);
		ingredients_.sort(sort_quantity);
	// If found, just add the quantity of ingredients to the kitchen
	} else {
		(*it).addAmount(units);
	}		
}

bool Kitchen::checkEnough (const list<Ingredient> recipe_ing) {
	list<Ingredient>::const_iterator it_rcp, it_kit;
	list<bool> enough;
	list<bool>::const_iterator it;
	bool isEnough;
	// Checks if there are enough ingredients in kitchen to make recipe
	for (it_rcp = recipe_ing.begin(); it_rcp != recipe_ing.end(); ++it_rcp) {
		for (it_kit = ingredients_.begin(); it_kit != ingredients_.end(); ++it_kit) {
			if ((*it_kit).getName() == (*it_rcp).getName()) {
				// Check made here
				if ((*it_kit).getAmount() >= (*it_rcp).getAmount()) {
					isEnough = true;
				} else {
					isEnough = false;
				}
				// Puts true or false in a list
				enough.push_back(isEnough);
			}
		}
	}
	// If the size of enough is smaller than the list of ingredients, that means there
	// are ingredients missing in the kitchen
	if (enough.size() < recipe_ing.size()) {
		return false;
	}
	// Goes through list of bools, if there is one false, return false
	for (it = enough.begin(); it != enough.end(); ++it) {
		if ((*it) == false) {
			return false;
		}
	}
	return true;
}

void Kitchen::removeIngredients(const Ingredient item) {
	list<Ingredient>::iterator it;
	for (it = ingredients_.begin(); it != ingredients_.end(); ++it) {
		if ((*it).getName() == item.getName()) {
			if ((*it).getAmount() >= item.getAmount()) {
				// Removes amount
				(*it).removeAmount(item.getAmount());

			} 
		}
	}
	// If the amount of an ingredient is 0, it is removed from the list of 
	// ingredients in the kitchen
	for (it = ingredients_.begin(); it != ingredients_.end(); ) {
		if ((*it).getAmount() == 0) {
			ingredients_.erase(it++);
		} else {
			++it;
		}
	}
}


list<Ingredient> Kitchen::amountNeeded(const list<Ingredient> recipe_ing, list<Ingredient> needed) { 
	list<Ingredient>::const_iterator it_rcp, it_kit;
	// If a recipe ingredient is not found in the Kitchen, create a new Ingredient with the amount needed
	bool found;
	for (it_rcp = recipe_ing.begin(); it_rcp != recipe_ing.end(); ++it_rcp) {
		found = false;
		for (it_kit = ingredients_.begin(); it_kit != ingredients_.end(); ++it_kit) {
			if ((*it_kit).getName() == (*it_rcp).getName()) {
				found = true;
				// Checks if the amount in the kitchen is less than needed for the recipe
				if ((*it_kit).getAmount() < (*it_rcp).getAmount()) {
					// Create a new Ingredient and put it in the list of needed ingredients
					Ingredient newIng((*it_rcp).getName(),(*it_rcp).getAmount() - (*it_kit).getAmount());
					needed.push_back(newIng);
				}
			} 
		}
		// New Ingredient is created 
		if (found == false) {
			Ingredient newIng((*it_rcp).getName(),(*it_rcp).getAmount());
			needed.push_back(newIng);
		}
	}
	needed.sort(sort_name);
	return needed;
}

#endif
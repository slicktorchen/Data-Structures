// File:     ingredient.h
// Purpose:  Define and implement the class Ingredient

#ifndef ingredient_h_
#define ingredient_h_

#include <string>

using namespace std;

class Ingredient {

public:
	Ingredient(string name, int amount) {
		name_ = name;
		amount_ = amount;
	}

	string getName() const { return name_;}
	int getAmount() const { return amount_;}

	void addAmount(int amount) {
		amount_ += amount;
	}
	void removeAmount(int amount) {
		amount_ -= amount;
	}


private:
	string name_;
	int amount_;
};

// Sort function sorts by QUANTITY, then by alphabetical order if equal
// For use in kitchen
bool sort_quantity(const Ingredient& ing1, const Ingredient& ing2) {
	if (ing1.getAmount() < ing2.getAmount()) {
		return true;
	} else if (ing1.getAmount() > ing2.getAmount()) {
		return false;
	} else {
		if (ing1.getName() < ing2.getName()) {
			return true;
		} else {
			return false;
		}
	}
}

// Sort function sorts ALPHABETICALLY
// For use in printing recipe and list of needed ingredients
bool sort_name(const Ingredient& ing1, const Ingredient& ing2) {
	if (ing1.getName() < ing2.getName()) {
		return true;
	} else {
		return false;
	}
}

#endif
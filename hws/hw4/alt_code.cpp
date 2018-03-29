#ifndef recipe_h_
#define recipe_h_

#include <string>
#include <iterator>
#include <list>
#include <fstream>

#include "ingredient.h"

using namespace std;

class Recipe {
public: 
	Recipe(string name) {
		name_ = name;
	}

	string getName() const { return name_;}
	list<string> getIngredients() const { return ingredients_; }
	list<int> getAmounts() const { return amounts_; }

	void addIngredient(string item, int units) {
		ingredients_.push_back(item);
		amounts_.push_back(units);
	}

	void printRecipe(ostream &ostr) const {
		list<string>::const_iterator it_ing;
		list<int>::const_iterator it_amt;
		ostr << "To make " << name_ << ", mix togther:" << endl;
		for (it_ing = ingredients_.begin(), it_amt = amounts_.begin() ; it_ing != ingredients_.end(), it_amt != amounts_.end(); ++it_ing, ++it_amt) {
			ostr <<  "  " << *it_amt << " units of " << *it_ing << endl;
		}
	}


	

private:
	string name_;
	list<string> ingredients_;
	list<int> amounts_;

};


#endif



void makeRecipe(std::istream &istr, std::ostream &ostr, const std::list<Recipe> &recipes, Kitchen &kitchen) {
  std::string name;
  istr >> name;
  list<Recipe>::const_iterator it_rcp;

  list<int>::const_iterator it_amt_rcp;
  list<string>::const_iterator it_ing_rcp;
  list<int>::iterator it_amt_kit;
  list<string>::const_iterator it_ing_kit;

  list<int> amounts_rcp;
  list<string> ingredients_rcp;
  list<int> amounts_kit;
  list<string> ingredients_kit;
  list<int> amount_needed;
  list<string> ingredients_needed;

  const Recipe *toMake;
  for (it_rcp = recipes.begin(); it_rcp != recipes.end(); ++it_rcp) {
	  if ((*it_rcp).getName() == name) {
		  toMake = &(*it_rcp);
	  }
  } 
  ingredients_rcp = toMake->getIngredients();
  amounts_rcp = toMake->getAmounts();
  ingredients_kit = kitchen.getIngredients();
  amounts_kit = kitchen.getAmounts();
  bool enough;
  for (it_ing_rcp = ingredients_rcp.begin(), it_amt_rcp = amounts_rcp.begin() ; it_ing_rcp != ingredients_rcp.end(), it_amt_rcp != amounts_rcp.end(); ++it_ing_rcp, ++it_amt_rcp) {
	  enough = true;
	  enough = kitchen.removeIngredients(*it_ing_rcp,*it_amt_rcp,enough);
	  if (enough == false) {
		  for (it_ing_kit = ingredients_kit.begin(), it_amt_kit = amounts_kit.begin() ; it_ing_kit != ingredients_kit.end(), it_amt_kit != amounts_kit.end(); ++it_ing_kit, ++it_amt_kit) {
			  amount_needed.push_back(*it_amt_rcp - *it_amt_kit);
			  ingredients_needed.push_back(*it_ing_rcp);
		  }
		  ostr << "Cannot make " << name << ", need to buy:" << endl;
		  for (it_ing_kit = ingredients_needed.begin(), it_amt_kit = amount_needed.begin(); it_ing_kit != ingredients_needed.end(), it_amt_kit != amount_needed.end(); ++it_ing_kit, ++it_amt_kit) {
			  ostr << "  " << *it_amt_kit << " units of " << *it_ing_kit << endl;
		  }
	  } 
  }
  /*for (it_ing_rcp = ingredients_rcp.begin(), it_amt_rcp = amounts_rcp.begin() ; it_ing_rcp != ingredients_rcp.end(), it_amt_rcp != amounts_rcp.end(); ++it_ing_rcp, ++it_amt_rcp) {
	  for (it_ing_kit = ingredients_kit.begin(), it_amt_kit = amounts_kit.begin() ; it_ing_kit != ingredients_kit.end(), it_amt_kit != amounts_kit.end(); ++it_ing_kit, ++it_amt_kit) {
		  if ((*it_ing_rcp) == (*it_ing_kit)) {
			  if ((*it_amt_rcp) <= (*it_amt_kit)) {
				  kitchen.removeIngredients(*it_ing_rcp,*it_amt_rcp);
			  } else {
				  amount_needed.push_back(*it_amt_rcp - *it_amt_kit);
				  ingredients_needed.push_back(*it_ing_rcp);
				  enough = false;
			  }
			  break;
		  }
	  }
  }*/
  if (enough == true) {
	  ostr << "Make " << name << endl;
  }
  /*if (enough == false) {
	  ostr << "Cannot make " << name << ", need to buy:" << endl;
	  for (it_ing_rcp = ingredients_needed.begin(), it_amt_rcp = amount_needed.begin(); it_ing_rcp != ingredients_needed.end(), it_amt_rcp != amount_needed.end(); ++it_ing_rcp, ++it_amt_rcp) {
		  ostr << "  " << *it_amt_rcp << " units of " << *it_ing_rcp << endl;
	  }
  } else {
	  ostr << "Make " << name << endl;
  }*/
}



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

	list<string> getIngredients() const { return ingredients_; }
	list<int> getAmounts() const { return amounts_; }

	void const printIngredients(ostream &ostr) {
		list<string>::const_iterator it_ing;
		list<int>::const_iterator it_amt;
		ostr << "In the kitchen:" << endl;
		for (it_ing = ingredients_.begin(), it_amt = amounts_.begin() ; it_ing != ingredients_.end(), it_amt != amounts_.end(); ++it_ing, ++it_amt) {
			if (*it_amt == 1) {
				ostr << "  " << *it_amt << " unit of " << *it_ing << endl;
			} else {
				ostr << "  " << *it_amt << " units of " << *it_ing << endl;
			}
		}
	}

	void addIngredient(string item, int amount) {
		ingredients_.push_back(item);
		amounts_.push_back(amount);
	}

	bool removeIngredients(string item, int amount, bool enough) {
		list<string>::const_iterator it_ing;
		list<int>::iterator it_amt;
		for (it_ing = ingredients_.begin(), it_amt = amounts_.begin() ; it_ing != ingredients_.end(), it_amt != amounts_.end(); ++it_ing, ++it_amt) {
			if (*it_ing == item) {
				if (*it_amt >= amount) {
					*it_amt -= amount;
				} else {
					enough = false;
					break;
				}
			}
		}
		if (enough == false) { cout << "not enough" << endl; }
		return enough;
	}


private:
	list<string> ingredients_;
	list<int> amounts_;
};


#endif
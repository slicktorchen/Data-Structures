#ifndef _SUPERHERO_H_
#define _SUPERHERO_H_

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Superhero {
public:
	Superhero(const string name, const string identity, const string power) : name_(name), identity_(identity), power_(power), good_(true) {}
	string getName() const { return name_; }
	string getPower() const { return power_; }
	
	friend class Team;
	
	bool operator==(string guess) {
		if (guess == identity_) {
			return true;
		} 
		return false;
	}
	bool operator!=(string guess) {
		if (guess != identity_) {
			return true;
		}
		return false;
	}

	void operator-() { 
		if ( good_ == true) {
			good_ = false; 
		} else {
			good_ = true;
		}
	}

	friend bool operator>(const Superhero &hero1, const Superhero &hero2) {
		if (hero1.getPower() == "Fire" && hero2.getPower() == "Wood") {
			return true;
		} else if (hero1.getPower() == "Wood" && hero2.getPower() == "Fire") {
			return false;
		} else if (hero1.getPower() == "Wood" && hero2.getPower() == "Water") {
			return true;
		} else if (hero1.getPower() == "Water" && hero2.getPower() == "Wood") {
			return false;
		} else if (hero1.getPower() == "Water" && hero2.getPower() == "Fire") {
			return true;
		} else if (hero1.getPower() == "Fire" && hero2.getPower() == "Water") {
			return false;
		}
		return false;
	}

	bool isGood() const { return good_; }

private:
	string name_;
	string identity_;
	string power_;
	bool good_;
	string getTrueIdentity() const { return identity_; }
};

ostream& operator<<(ostream &ostr, const Superhero &hero);


#endif
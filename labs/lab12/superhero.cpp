#include <iostream>
#include "superhero.h"

using namespace std;

ostream& operator<<(ostream &ostr, const Superhero &hero) {
	if (hero.isGood()) {
		ostr << "Superhero "; 
	} else {
		ostr << "Supervillain ";
	}
	ostr << hero.getName() << " has superpower " << hero.getPower() << endl ;
	return ostr;
}
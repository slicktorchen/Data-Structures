#ifndef ship_h_
#define ship_h_

// Defines the Ship and Constraint classes
#include <string>
using namespace std;

// The Constraint class stores the character and location of the constraint
class Constraint {
public:
	Constraint(char constr, int row, int col) {
		constr_ = constr;
		row_ = row;
		col_ = col;
	}
	char constr_;
	int row_;
	int col_;
};

// The Ship class stores the name, location, and orientation of a ship
class Ship {
public:
	Ship(string name, string orientation = "horizontal", int row = 0, int col = 0){ 
		name_ = name;
		if (name == "submarine") {
			size_ = 1;
		} else if (name == "destroyer") {
			size_ = 2;
		} else if (name == "cruiser") {
			size_= 3;
		} else if (name == "battleship") {
			size_ = 4;
		} else if (name == "carrier") {
			size_ = 5;
		} else if (name == "cargo") {
			size_ = 6;
		} else if (name == "tanker") {
			size_ = 7;
		}
		orientation_ = orientation;
		row_ = row;
		col_ = col;
	}
	string getName() const { return name_; }
	string getOrient() const { return orientation_; }
	int getSize() const { return size_; }
	int getRow() const { return row_; }
	int getCol() const { return col_; }
	void setOrient(string orientation) {
		orientation_ = orientation;
	}
	void setRow(int row) {
		row_ = row;
	}
	void setCol(int col) {
		col_ = col;
	}

private:
	string name_;
	string orientation_;
	int size_;
	int row_, col_;
};

bool sort_size(const Ship &ship1, const Ship &ship2) {
	if (ship1.getSize() > ship2.getSize()) {
		return true;
	} else {
		return false;
	}
}

bool sort_coord(const Ship &ship1, const Ship &ship2) {
	if (ship1.getRow() < ship2.getRow()) {
		return true;
	} else if (ship1.getRow() > ship2.getRow()) {
		return false;
	} else {
		if (ship1.getCol() < ship2.getCol()) {
			return true;
		} else {
			return false;
		}
	}
}


#endif
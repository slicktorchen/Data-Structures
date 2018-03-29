#include <iostream>
#include <string>
#include <vector>

#include "polygons.h"
#include "utilities.h"

using namespace std;

/////////////////////////// DEFINITIONS OF POLYGON MEMBER FUNCTIONS ////////////////////////////

bool Polygon::HasAllEqualSides() {
	// Pick one side and get its length
	double length = DistanceBetween(points_[0],points_[1]);
	for (unsigned int i = 0; i < points_.size(); ++i) {
		// If any of the sides do not equal 'length', return false
		if (i + 1 == points_.size()) {
			// Boundary check
			if (EqualSides(DistanceBetween(points_[i],points_[0]), length) == false) {
				return false;
			}
		} else { 
			if (EqualSides(DistanceBetween(points_[i],points_[i+1]), length) == false) {
				return false;
			}
		}
	}
	// If all sides equal 'length', return true
	return true;
}

bool Polygon::HasAllEqualAngles() {
	// Pick one angle and get its measure
	double angle = Angle(points_[0],points_[1],points_[2]);
	for (unsigned int i = 0; i < points_.size(); ++i) {
		// If any of the sides do not equal 'angle', return false
		if (i + 2 == points_.size()) {
			// Boundary check 1
			if (EqualAngles(Angle(points_[i],points_[i+1],points_[0]), angle) == false) {
				return false;
			}
		} else if (i + 1 == points_.size()) {
			// Boundary check 2
			if (EqualAngles(Angle(points_[i],points_[0],points_[1]), angle) == false) {
				return false;
			}
		} else { 
			if (EqualAngles(Angle(points_[i],points_[i+1],points_[i+2]), angle) == false) {
				return false;
			}
		}
	}
	// If all angles equal 'angle', return true
	return true;
}

bool Polygon::HasARightAngle() {
	for (unsigned int i = 0; i < points_.size(); ++i) {
		// If any of the angles are right angles, return true
		if (i + 2 == points_.size()) {
			// Boundary check 1
			if (RightAngle(Angle(points_[i],points_[i+1],points_[0])) == true) {
				return true;
			}
		} else if (i + 1 == points_.size()) {
			// Boundary check 2
			if (RightAngle(Angle(points_[i],points_[0],points_[1])) == true) {
				return true;
			}
		} else { 
			if (RightAngle(Angle(points_[i],points_[i+1],points_[i+2])) == true) {
				return true;
			}
		}
	}
	// If none of the angles are right angles, return false
	return false;
}

bool Polygon::HasAnObtuseAngle() {
	for (unsigned int i = 0; i < points_.size(); ++i) {
		// If any of the angles are obtuse angles, return true
		if (i + 2 == points_.size()) {
			// Boundary check 1
			if (ObtuseAngle(Angle(points_[i],points_[i+1],points_[0])) == true) {
				return true;
			}
		} else if (i + 1 == points_.size()) {
			// Boundary check 2
			if (ObtuseAngle(Angle(points_[i],points_[0],points_[1])) == true) {
				return true;
			}
		} else { 
			if (ObtuseAngle(Angle(points_[i],points_[i+1],points_[i+2])) == true) {
				return true;
			}
		}
	}
	// If none of the angles are obtuse angles, return false
	return false;
}

bool Polygon::HasAnAcuteAngle() {
	for (unsigned int i = 0; i < points_.size(); ++i) {
		// If any of the angles are acute angles, return true
		if (i + 2 == points_.size()) {
			// Boundary check 1
			if (AcuteAngle(Angle(points_[i],points_[i+1],points_[0])) == true) {
				return true; 
			} 
		} else if (i + 1 == points_.size()) {
			// Boundary check 2
			if (AcuteAngle(Angle(points_[i],points_[0],points_[1])) == true) {
				return true;
			} 
		} else { 
			if (AcuteAngle(Angle(points_[i],points_[i+1],points_[i+2])) == true) {
				return true;
			} 
		}
	}
	// If none of the angles are acute angles, return false
	return false;
}

bool Polygon::IsConvex() {
	for (unsigned int i = 0; i < points_.size(); ++i) {
		// If any of the angles are reflex angles, return false
		if (i + 2 == points_.size()) {
			// Boundary check 1
			if (ReflexAngle(Angle(points_[i],points_[i+1],points_[0])) == true) {
				return false; 
			} 
		} else if (i + 1 == points_.size()) {
			// Boundary check 2
			if (ReflexAngle(Angle(points_[i],points_[0],points_[1])) == true) {
				return false;
			} 
		} else { 
			if (ReflexAngle(Angle(points_[i],points_[i+1],points_[i+2])) == true) {
				return false;
			} 
		}
	}
	// If none of the angles are reflex angles, then shape is convex
	return true;
}

bool Polygon::IsConcave() {
	// If the shape is convex, then the shape is not concave
	return !IsConvex();
}

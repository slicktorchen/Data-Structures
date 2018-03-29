#ifndef _polygons_h_
#define _polygons_h_

#include <iostream>
#include <vector>
#include <string>

#include "utilities.h"

using namespace std;

/////////////////////////////// POLYGON CLASS ////////////////////////////////
class Polygon {
public:
	// CONSTRUCTOR/ASSIGNMENT/DESTRUCTOR
	Polygon(const string &name,const vector<Point> points) : name_(name), points_(points) {}
	Polygon(const Polygon &poly) : name_(poly.getName()), points_(poly.getPoints()) {}
	virtual ~Polygon() {}

	// MEMBER FUNCTIONS
	bool HasAllEqualSides();
	bool HasAllEqualAngles();
	bool HasARightAngle();
	bool HasAnObtuseAngle();
	bool HasAnAcuteAngle(); 
	bool IsConcave();
	bool IsConvex();

	// ACCESSORS
	string getName() const { return name_; }
	vector<Point> getPoints() const { return points_; }

protected:
	// MEMBER VARIABLES
	string name_;
	vector<Point> points_;
};

//////////////////////////// TRIANGLE CLASSES /////////////////////////////////

class Triangle : public Polygon {
public:
	Triangle(const string &name, const vector<Point> &points) : Polygon(name,points) {
		// If there aren't 3 points, throw an exception
		if (points.size() != 3) {
			throw 0;
		}
	}
};

class RightTriangle : virtual public Triangle {
public:
	RightTriangle(const string &name,const vector<Point> &points) : Triangle(name,points) {
		// If none of the angles are right angles, throw an exception
		if (HasARightAngle() == false) {
			throw 0;
		}
	}

};

class IsoscelesTriangle : virtual public Triangle {
public:
	IsoscelesTriangle(const string &name,const vector<Point> &points) : Triangle(name,points) {
		// If no two pairs of sides are equal to each other, throw an exception
		if (EqualSides(DistanceBetween(points[0],points[1]), DistanceBetween(points[1],points[2])) == false && 
			EqualSides(DistanceBetween(points[0],points[2]), DistanceBetween(points[0],points[1])) == false && 
			EqualSides(DistanceBetween(points[0],points[2]), DistanceBetween(points[1],points[2])) == false) {
				throw 0;
		}
	}
};

class ObtuseTriangle : virtual public Triangle {
public:
	ObtuseTriangle(const string &name,const vector<Point> &points) : Triangle(name,points) {
		// If none of the angles are obtuse angles, throw an exception
		if (HasAnObtuseAngle() == false) {
			throw 0;
		}
	}
};

class EquilateralTriangle : public IsoscelesTriangle {
public:
	EquilateralTriangle(const string &name,const vector<Point> &points) : Triangle(name,points), IsoscelesTriangle(name,points) {
		// If not all of the angles equal 60 degrees, throw an exception
		if (HasAllEqualSides() == false) {
			throw 0;
		}
	}
};

class IsoscelesObtuseTriangle : public ObtuseTriangle, public IsoscelesTriangle {
public:
	// Both exceptions in the ObtuseTriangle and IsoscelesTriangle constructors covers the exceptions for the IsoscelesObtuseTriangle
	IsoscelesObtuseTriangle(const string &name,const vector<Point> &points) : Triangle(name,points), ObtuseTriangle(name,points), IsoscelesTriangle(name,points) {}
};

class IsoscelesRightTriangle : public IsoscelesTriangle, public RightTriangle {
public:
	// Both exceptions in the RightTriangle and IsoscelesTriangle constructors covers the exceptions for the IsoscelesRightTriangle
	IsoscelesRightTriangle(const string &name,const vector<Point> &points) : Triangle(name,points), IsoscelesTriangle(name,points), RightTriangle(name,points) {}
};



///////////////////////////// QUADRILATERALS ////////////////////////////////

class Quadrilateral : public Polygon {
public:
	Quadrilateral(const string &name, const vector<Point> &points) : Polygon(name,points) {
		// If there aren't 4 points, throw an exception
		if (points.size() != 4) {
			throw 0;
		}
	}
};

class Kite : virtual public Quadrilateral {
public:
	Kite(const string &name,const vector<Point> &points) : Quadrilateral(name,points) {
		// If there are not two unique pairs of equal adjacent sides, throw an exception
		if ((EqualSides(DistanceBetween(points[0],points[1]), DistanceBetween(points[1],points[2])) == false && 
			EqualSides(DistanceBetween(points[1],points[2]), DistanceBetween(points[2],points[3])) == false) ||
			(EqualSides(DistanceBetween(points[1],points[2]), DistanceBetween(points[2],points[3])) == false &&
			EqualSides(DistanceBetween(points[2],points[3]), DistanceBetween(points[0],points[3])) == false) ||
			(EqualSides(DistanceBetween(points[2],points[3]), DistanceBetween(points[0],points[3])) == false &&
			EqualSides(DistanceBetween(points[0],points[3]), DistanceBetween(points[0],points[1])) == false)) {
				throw 0;
		}
	}
};

class Trapezoid : virtual public Quadrilateral {
public:
	Trapezoid(const string &name,const vector<Point> &points) : Quadrilateral(name,points) {
		// If there is not at least one set of parallel lines, throw an exception
		if (Parallel(Vector(points[0],points[1]),Vector(points[2],points[3])) == false && 
			Parallel(Vector(points[1],points[2]),Vector(points[0],points[3])) == false) {
				throw 0;
		}
	}
};

class Parallelogram : virtual public Trapezoid {
public:
	Parallelogram(const string &name,const vector<Point> &points) : Quadrilateral(name,points), Trapezoid(name,points) {
		// If both pairs of opposite sides are not equal, throw an exception
		if (EqualSides(DistanceBetween(points[0],points[1]),DistanceBetween(points[2],points[3])) == false && 
			EqualSides(DistanceBetween(points[1],points[2]),DistanceBetween(points[0],points[3])) == false) {
				throw 0;
		}
		// If there are not two sets of parallel lines, throw an exception
		if (Parallel(Vector(points[0],points[1]),Vector(points[2],points[3])) != Parallel(Vector(points[1],points[2]),Vector(points[0],points[3]))) {
				throw 0;
		}
	}
};

class IsoscelesTrapezoid : virtual public Trapezoid {
public:
	IsoscelesTrapezoid(const string &name,const vector<Point> &points) : Quadrilateral(name,points), Trapezoid(name,points) {
		// If two adjacent angles are not equal to each other, throw an exception
		if ((EqualAngles(Angle(points[0],points[1],points[2]),Angle(points[1],points[2],points[3])) == false ||
			EqualAngles(Angle(points[2],points[3],points[0]),Angle(points[3],points[0],points[1])) == false) &&
			(EqualAngles(Angle(points[1],points[2],points[3]),Angle(points[2],points[3],points[0])) == false ||
			EqualAngles(Angle(points[3],points[0],points[1]),Angle(points[0],points[1],points[2])) == false)) {
				throw 0;
		}
	}
};

class Rectangle : public IsoscelesTrapezoid , virtual public Parallelogram {
public:
	Rectangle(const string &name,const vector<Point> &points) 
		: Quadrilateral(name,points), Trapezoid(name,points), Parallelogram(name,points), IsoscelesTrapezoid(name,points) {
		// If not all of the angles are 90 degrees, throw an exception
		if (HasAllEqualAngles() == false) {
			throw 0;
		}
	}
};

class Rhombus : public Kite , virtual public Parallelogram {
public:
	Rhombus(const string &name,const vector<Point> &points) : 
		Quadrilateral(name,points), Trapezoid(name,points), Parallelogram(name,points), Kite(name,points) {
		// If not all of the sides are equal, throw an exception
		if (HasAllEqualSides() == false) {
			throw 0;
		}
	}
};

class Square : public Rectangle , public Rhombus {
public:
	// Both exceptions in the Rectangle and Rhombus constructors covers the exceptions for the Square
	Square(const string &name,const vector<Point> &points) : Quadrilateral(name,points), Trapezoid(name,points),
		Parallelogram(name,points), Rectangle(name,points), Rhombus(name,points) {}
};

class Arrow : public Quadrilateral {
public:
	Arrow(const string &name,const vector<Point> &points) : Quadrilateral(name,points) {
		// If there are not two unique pairs of equal adjacent sides, throw an exception
		if ((EqualSides(DistanceBetween(points[0],points[1]), DistanceBetween(points[1],points[2])) == false && 
			EqualSides(DistanceBetween(points[1],points[2]), DistanceBetween(points[2],points[3])) == false) ||
			(EqualSides(DistanceBetween(points[1],points[2]), DistanceBetween(points[2],points[3])) == false &&
			EqualSides(DistanceBetween(points[2],points[3]), DistanceBetween(points[0],points[3])) == false) ||
			(EqualSides(DistanceBetween(points[2],points[3]), DistanceBetween(points[0],points[3])) == false &&
			EqualSides(DistanceBetween(points[0],points[3]), DistanceBetween(points[0],points[1])) == false)) {
				throw 0;
		}
		// If none of the angles are a reflex angle, throw an exception
		if (ReflexAngle(Angle(points[0],points[1],points[2])) == false &&
			ReflexAngle(Angle(points[1],points[2],points[3])) == false &&
			ReflexAngle(Angle(points[2],points[3],points[0])) == false &&
			ReflexAngle(Angle(points[3],points[0],points[1])) == false) {
				throw 0;
		}
	}
};


#endif
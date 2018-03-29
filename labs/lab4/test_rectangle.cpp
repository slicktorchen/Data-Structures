#include <iostream>
#include <vector>
#include "Rectangle.h"
#include "Point2D.h"

using namespace std;

int main () {
	Point2D pt1(4,3);
	Point2D pt2(17,9);
	Point2D pt3(10,8);
	Point2D pt4(20,16);
	Point2D pt5(9,4);
	Point2D pt(1,2);
	pt.set(3,4);

	Rectangle rect1(pt1,pt2);
	Rectangle rect2(pt3,pt4);

	print_rectangle(rect1);
	print_rectangle(rect2);

	cout << rect1.is_point_within(pt5) << endl; // Should produce true
	cout << rect1.is_point_within(pt4) << endl; // Should produce false
	cout << rect2.is_point_within(pt2) << endl; // Should produce true
	cout << rect2.is_point_within(pt1) << endl; // Should produce false

}


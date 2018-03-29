#include <fstream>
#include <iostream>
#include <list>
#include <vector>
using namespace std;

//bool find_paths(int x, int y, int &paths) {
//
//	if ( x == 0 || y == 0) {
//		++paths;
//		return true;
//	}
//
//	find_paths(x-1,y,paths);
//	find_paths(x,y-1,paths);
//
//	return false;
//}

bool find_paths(int x, int y, int &paths) {

	if ( x == 0 && y == 0) {
		++paths;
		return true;
	}

	if (y == 0) {
		find_paths(x-1,y,paths);
		return true;
	}
	if ( x == 0 ) {
		find_paths(x,y-1,paths);
		return true;
	}
	find_paths(x-1,y,paths);
	find_paths(x,y-1,paths);


	return false;
}


int main() {
	int paths = 0, x,y;
	cout << "Enter a point (x,y): " << endl;
	cin >> x >> y;
	find_paths(x,y,paths);
	cout << "Number of paths between point (" << x << "," << y << ") and the origin: " <<  paths << " paths";

	return 0;
}
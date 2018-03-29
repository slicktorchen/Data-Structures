#include <map>
#include <iostream>
#include <vector>
#include <fstream>
#include <iterator>

using namespace std;

int main(int argc, char* argv[]) {
	ifstream istr(argv[1]);
	if (!istr.good()) {
		cerr << "Can't read " << argv[1] << endl;
		return 1;
	}
	int number,max;
	vector<int> numbers;
	map<int,int> counter;
	map<int,int>::iterator it;
	while (istr >> number) {
		//++counter[number];
		it = counter.find(number);
		if ( it != counter.end()) {
			++(it->second);
		} else {
			counter.insert(make_pair(number,0));
		}
	}
	max = 0;
	for (it = counter.begin(); it != counter.end(); ++it) {
		if (it->second > max) {
			max = it->second;
		}
	}
	cout << "The mode(s) are: ";
	for (it = counter.begin(); it != counter.end(); ++it) {
		if (it->second == max) {
			cout << it->first << " ";
		}
	}
	cout << endl;

	return 0;
}
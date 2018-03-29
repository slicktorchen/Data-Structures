#include <unordered_set>
#include <unordered_map>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

int main() {
	ifstream istr("hansel_and_gretel.txt");
	if (!istr.good()) {
		cerr << "This sux " << endl;
	}
	string word;
	unordered_set<string> uset;
	while (istr >> word) {
		uset.insert(word);
	}
	cout << "Unique words: " << uset.size() << endl;

}
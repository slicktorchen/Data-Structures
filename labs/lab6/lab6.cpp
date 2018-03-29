#include <iostream>
#include <vector>
#include <list>

using namespace std;


template <class T>
void reverse_vector(vector<T> &A) {
	T x, y;
	for( int i = 0; i < (A.size()/2); ++i) {
		x = A[i];
		y = A[A.size() - i - 1];
		A[i] = y;
		A[A.size() - i -1] = x;
	}
}

template <class T>
void print_vec(vector<T> &B) {
	cout << "Contents of the vector: ";
	for( int i = 0; i < B.size(); ++i) {
		cout << B[i] << " ";
	}
	cout << endl << "Size of vector: " << B.size();
}

template <class T>
void reverse_list(list<T> &C) {
	list<T> list;
	list<T>::reverse_iterator ri;
	for( ri = C.rbegin() ; ri != C.rend(); ++ri) {
		list.push_back(ri);
	}
	C = list;
}

template <class T>
void print_list(list<T> &D) {
	list<T>::iterator it;
	for (it = D.begin(); it != D.end(); ++it) {
		cout << *it << " ";
	}
	cout << endl << "Size of list: " << D.size();
}

int main() {
	vector<int> v1,v2;
	for( int i =0; i < 7; ++i) {
		v1.push_back(i);
	}
	print_vec(v1);
	reverse_vector(v1);
	cout << endl;
	print_vec(v1);
	cout << endl;

	print_vec(v2);
	reverse_vector(v2);
	cout << endl;
	print_vec(v2);
	cout << endl;

	v2.push_back(2);
	print_vec(v2);
	reverse_vector(v2);
	cout << endl;
	print_vec(v2);

	/*cout << endl;
	list<int> l1;
	for(int i = 0; i < 6; ++i) {
		l1.push_back(i);
	}
	print_list(l1);
	reverse_list(l1);
	print_list(l1);*/
	
	return 0;
}

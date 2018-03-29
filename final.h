#ifndef final_h_
#define final_h_

#include <string>
#include <iostream>
#include <iterator>

using namespace std;

/*
/////////////////////////// PROBLEM 1 //////////////////////////
// The three methods to operator overloading are non-member, member, and 
// friend functions.
class Superhero {
public:
	// ACCESSORS
	const string& getName() const { return name; }
	const string& getPower() const { return power; }
	// INPUT STREAM OPERATOR
	friend istream& operator>>(istream &istr, Superhero &hero);
	Superhero& operator/=(const string &id);
private:
	// REPRESENTATION
	string name;
	string true_identity;
	string power;
};
// OUTPUT STREAM OPERATOR
ostream& operator<<(ostream &ostr, const Superhero &hero);
*/

/*
///////////////////////////// PROBLEM 2 ///////////////////////////////
class Car {
public:
	// CONSTRUCTOR
	Car(const string &m, const string &c) : maker(m), color(c) {}
	// ACCESSORS
	const string& getMaker() const { return maker; }
	const string& getColor() const { return color; }
private:
	// REPRESENTATION
	string maker;
	string color;
};

bool operator<(const Car& left, const Car& right) {
	return left.getMaker() < right.getMaker() ||
		(left.getMaker() == right.getMaker() && left.getColor() < right.getColor());
}

void print_cars(const map<Car,vector<string> > &cars) {
	map<Car,vector<string> >::const_iterator it = cars.begin();
	for (it = cars.begin(); it != cars.end(); ++it) {
		Car car = it->first;
		cout << "People who drive a " << car.getColor() << " " << car.getMaker() << endl;
		vector<string>::const_iterator it2;
		for (it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
			cout << "  " << *it2 << endl;
		}
	}
}

bool remove_car(map<Car,vector<string> > &cars, const string &name, 
				const string &color, const string &maker) {
	map<Car,vector<string> >::iterator it = cars.find(Car(maker,color));
	if (it == cars.end()) {
		return false;
	} else {
		vector<string>::iterator it2 = it->second.begin();
		for (unsigned int i = 0; i < it->second.size(); ++i) {
			if (it->second[i] == name) {
				if (it->second.size() == 1) {
					cars.erase(it);
				} else {
					it.erase(it2+i);
				}
				return true;
			}
		}
	}
	return false;
}
*/


///////////////////////////// PROBLEM 3 ////////////////////////////////
/*
void insert_in_order(double x, queue<double>& q) {
	if (q.empty()) {
		q.push(x);
	} else {
		queue<double> temp(q);
		while (!q.empty()) { q.pop(); }
		while (!temp.empty() && x > temp.front()) {
			double item = temp.front();
			q.push(item);
			temp.pop()
		}
		q.push(x);
		while (!temp.empty()) {
			double item = temp.front();
			q.push(item);
			temp.pop();
		}
	}
}
*/

/*
////////////////////////// PROBLEM 4 ////////////////////////////////
template <class T>
void dslist<T>::reverse() {
	if (head == tail) { return; }
	Node *p = head;
	while (p) {
		Node *q = p->next;
		p->next = p->prev;
		p->prev = q;
		p = q;
	}
	p = head;
	head = tail;
	tail = p;
}

Node<T>* Sublist(Node<T>* head, int low, int high) {
	int counter;
	Node *p = head;
	while (counter != low) {
		p = p->next;
		++counter;
	}
	Node *nhead = new Node;
	nhead->value = p->value;
	Node *temp = nhead;
	while (counter != high + 1) {
		temp->next = new Node;
		temp->next->value = p->next->value;
		temp = temp->next;
		p = p->next;
		++counter;
	}
	temp->next = NULL;
	return nhead;
}

template<class T> 
void cs2list<T>::splice(iterator itr, cs2list<T>& second) {
	if (second.empty()) { return; }
	second.head->prev = itr.ptr;
	second.tail->next = itr.ptr->next;
	if (itr.ptr->next != NULL) {
		itr.ptr->next->prev = second.tail;
	} else {
		this->tail = second.tail;
	}
	itr.ptr->next = second.head;
	this->size = second.size;
	second.size = 0;
	second.head = second.tail = NULL;

}
*/

/*
////////////////////////// PROBLEM 14 //////////////////////
void priority_queue::pop_max() {
	int temp = (size()+1)/2;
	for (int i = temp + 1; i < size(); ++i) {
		if (m_heap[temp] < m_heap[i]) {
			temp = i;
		}
	}
	m_heap[temp] = m_heap.back();
	m_heap.pop_back();
	this->percolate_up(temp);
}
*/

/*
///////////////////////// PROBLEM 11 //////////////////////
// Office();                                       default constructor
// Office& operator=(const Office &office);        assignment operator
// Office(const Office &office);                   copy constructor
// ~Office();                                      destructor

Office::~Office() {
	for (int i = 0; i < _num_desks; ++i) {
		if (_desks[i] != "") {
			_unassigned.push(_desks[i]);
		}
	}
	delete [] _desks;
}
*/

/*
//////////////////////// PROBLEM 12 ///////////////////////
void even_array(const list<int>& b, int* &a, int &n) {
	list<int>::const_iterator it;
	int counter = 0;
	for (it = b.begin(); it != b.end(); ++it) {
		if ((*it)%2 == 0) {
			counter++;
		}
	}
	a = new int[counter];
	int* p = a;
	for (it = b.begin(); it != b.end(); ++it) {
		if ((*it)%2 == 0) {
			*p = *it;
			++p;
		}
	}
}
*/

/////////////////////// PROBLEM 13 //////////////////////////////
bool EqualsChildrenSum(Node *p) {
	if (p == NULL) {
		return false;
	}

	int sum = 0;
	if (p->left != NULL) { sum += p->left->value; }
	if (p->right != NULL) { sum += p->right->value; }
	if (p->middle != NULL) { sum += p->middle->value; }
	if (sum != p->value) {
		return false;
	}

	return EqualsChildrenSum(p->left) && EqualsChildrenSum(p->middle)
		&& EqualsChildrenSum(p->right);
}

#endif

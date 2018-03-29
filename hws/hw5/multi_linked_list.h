#ifndef multi_linked_list_h_
#define multi_linked_list_h_

#include <string>
#include <ctime>
#include "mtrand.h"

using namespace std;

template<class T>
class Node {
public:
	// Default constructor
	Node() : value(0), chrono_next(NULL), chrono_prev(NULL), sorted_next(NULL), sorted_prev(NULL) {}
	// Copy constructor
	Node(const T& v) : value(v), chrono_next(NULL), chrono_prev(NULL), sorted_next(NULL), sorted_prev(NULL) {}

	bool operator==(const Node<T>& old) const {
		return value == old.value;
	}
	bool operator!=(const Node<T>& old) const {
		return value != old.value;
	}

	// REPRESENTATION
	T value;
	Node<T>* chrono_next;
	Node<T>* chrono_prev;
	Node<T>* sorted_next;
	Node<T>* sorted_prev;
	Node<T>* random_next;
};


// Prototype class MultiLL 
template<class T> 
class MultiLL;

// Iterator that moves through MultiLL depending on order (chrono, sorted, or random)
template <class T>
class list_iterator {
public:
	// default constructor, copy constructor, assignment operator, & destructor
	list_iterator() : ptr_(NULL) {}
	list_iterator(Node<T>* p, string type) : ptr_(p), type_(type) {}
	list_iterator(const list_iterator<T>& old) : ptr_(old.ptr_), type_(old.type_) {}
	list_iterator<T>& operator=(const list_iterator<T>& old) {
	ptr_ = old.ptr_; type_ = old.type_;  return *this; }
	~list_iterator() {  }

	Node<T>* getPtr() { return ptr_; }

	// dereferencing operator gives access to the value at the pointer
	T& operator*()  { return ptr_->value;  }	

	// increment & decrement operators
	list_iterator<T>& operator++() { // pre-increment, e.g., ++iter
		if (type_ == "chrono") { ptr_ = ptr_->chrono_next; }
		else if (type_ == "sorted") { ptr_ = ptr_->sorted_next; }
		else if (type_ == "random") { 
			ptr_ = ptr_->random_next; 
		}
		return *this;
	}
	list_iterator<T> operator++(int) { // post-increment, e.g., iter++
		list_iterator<T> temp(*this);
		if (type_ == "chrono") { ptr_ = ptr_->chrono_next; }
		else if (type_ == "sorted") { ptr_ = ptr_->sorted_next; }
		else if (type_ == "random") { ptr_ = ptr_->random_next; }
	return temp;
	}
	list_iterator<T>& operator--() { // pre-decrement, e.g., --iter
		if (type_ == "chrono") { ptr_ = ptr_->chrono_prev; }
		else if (type_ == "sorted") { ptr_ = ptr_->sorted_prev; }
	return *this;
	}
	list_iterator<T> operator--(int) { // post-decrement, e.g., iter--
		list_iterator<T> temp(*this);
		if (type_ == "chrono") { ptr_ = ptr_->chrono_prev; }
		else if (type_ == "sorted") { ptr_ = ptr_->sorted_prev; }
	return temp;
	}
	// the dslist class needs access to the private ptr_ member variable
	friend class MultiLL<T>;

	// Comparions operators are straightforward
	bool operator==(const list_iterator<T>& r) const {
	return ptr_ == r.ptr_; }
	bool operator!=(const list_iterator<T>& r) const {
	return ptr_ != r.ptr_; }

private:
  // REPRESENTATION
  Node<T>* ptr_;    // ptr to node in the list
  string type_;     // defines which order the iterator goes through the list

};

// Mtrand function call
MTRand_int32 mtrand_autoseed(time(NULL));

// MultiLL contains the head and tail ptrs to the list of each specific order
template<class T> 
class MultiLL {
public:
	MultiLL() : count_(0), chrono_head_(NULL), chrono_tail_(NULL), sorted_head_(NULL), sorted_tail_(NULL), random_head_(NULL) {}
	MultiLL(const MultiLL<T>& old) { copy_list(old); }
	MultiLL& operator= (const MultiLL<T>& old);
	~MultiLL() { this->destroy_list(); }

	unsigned int size() const { return count_; }
	void clear() { this->destroy_list(); }
	bool empty() { return chrono_head_ == NULL; }
	void add(const T& v);

	typedef list_iterator<T> iterator;
	iterator erase(iterator itr);
	iterator begin_chronological() { return iterator(chrono_head_,"chrono"); }
	iterator begin_sorted() {return iterator(sorted_head_,"sorted"); }
	iterator end_chronological() { return iterator(NULL,"chrono"); }
	iterator end_sorted() { return iterator(NULL,"sorted"); }
	iterator begin_random() 
	{ 
		Node<T>* temp = chrono_head_;
		for (int i = 0; i < count_; ++i) {
			// Reset all random_next ptrs in each Node to NULL
			temp->random_next = NULL;
			temp = temp->chrono_next;
		}
		
		for (int i = 0; i < count_; ++i) {
			unsigned int rand_count,rand_num; 
			Node<T> *prev,*current;
			rand_count = 0;
			current = chrono_head_;
			// Continuous generation of random numbers
			rand_num = mtrand_autoseed() % (count_);
			// Traverse the list chronologically up to a certain number location in  
			// list depending on the random number
			while (rand_count < rand_num) {
				current = current->chrono_next;
				++rand_count;
			}
			if (current->random_next != NULL) { 
				// If the current is in new random list
				--i; 
			} else if (i == 0) { 
				// First random Node
				prev = current;
				current->random_next = current;
				random_head_ = current; 
			} else {
				// Adding more random Nodes
				prev->random_next = current;
				current->random_next = random_head_;
				prev = current;
			}
		}  
		// Returns the iterator pointing to the Node random_head_ is pointing to
		return iterator(random_head_,"random"); 
	}

private:
	// REPRESENTATION
	void copy_list(const MultiLL<T>& old);
	void destroy_list();

	int count_;
	Node<T>* chrono_head_;
	Node<T>* chrono_tail_;
	Node<T>* sorted_head_;
	Node<T>* sorted_tail_;
	Node<T>* random_head_;
};

/////////////////////// LIST IMPLEMENTATION /////////////////////////////
// Define operator= for MultiLL class
template <class T>
MultiLL<T>& MultiLL<T>::operator= (const MultiLL<T>& old) {
  // check for self-assignment
  if (&old != this) {
    this->destroy_list();
    this->copy_list(old);
  }
  return *this;
}

// Define the add function in the MultiLL class
template <class T>
void MultiLL<T>::add(const T& v) {
	Node<T>* temp_chrono, *temp_sorted;
	Node<T>* newNode = new Node<T>(v);
	++count_;
	// For an empty MultiLL, all head ptrs point to this new Node.
	// Node pointers all point to NULL, random is circular, points to self
	if (count_ == 1) {
		chrono_head_ = chrono_tail_ = sorted_head_ = sorted_tail_ = random_head_ = newNode;
		newNode->chrono_next = newNode->chrono_prev = newNode->sorted_next 
			= newNode->sorted_prev = NULL;
		newNode->random_next = newNode;
		return;
	}
	// Append new value in a new Node at the end of the chronological list
	temp_chrono = this->chrono_tail_;
	temp_chrono->chrono_next = newNode;
	newNode->chrono_next = NULL;
	newNode->chrono_prev = temp_chrono;
	this->chrono_tail_ = newNode;
	
	// Adjust the sorted pointers to include the new Node
	temp_sorted = this->sorted_head_;
	Node<T>* prev = NULL;
	while (temp_sorted != NULL && temp_sorted->value < v) {
		prev = temp_sorted;
		temp_sorted = temp_sorted->sorted_next;
	}
	if (prev == NULL) { 
		// Insert to the head
		this->sorted_head_ = newNode;
		newNode->sorted_prev = NULL;
		newNode->sorted_next = temp_sorted;
		temp_sorted->sorted_prev = newNode;
	} 
	else if (temp_sorted == NULL) {
		// Insert after tail
		prev->sorted_next = newNode;
		newNode->sorted_prev = prev;
		newNode->sorted_next = NULL;
		this->sorted_tail_ = newNode;
	} else { 
		// Insert in the middle
		newNode->sorted_prev = prev;
		newNode->sorted_next = temp_sorted;
		temp_sorted->sorted_prev = newNode;
		prev->sorted_next = newNode;
	}
}

// Define the erase function in the MultiLL class
template <class T>
typename MultiLL<T>::iterator MultiLL<T>::erase(iterator itr) {
	Node<T>* current,*temp; 
	// For an empty list, return the same iterator
	if (itr.getPtr() == NULL) {
		return itr;
	}
	temp = current = itr.getPtr();
	// Loop through the random list until temp->random_next goes back to the same Node
	while (temp->random_next != current) {
		temp = temp->random_next;
	}
	temp->random_next = current->random_next;
	// If the iterator points to the same Node as random_head_, reassign random_head_
	// to the next Node in the random list
	if (current == random_head_) {
		random_head_ = current->random_next;
	}
	
	if (current->chrono_prev == NULL) {
		// If the iterator is at the beginning of the chrono list
		current->chrono_next->chrono_prev = NULL;
		chrono_head_ = current->chrono_next;
	} else if (current->chrono_next == NULL) {
		// If the iterator is at the end of the chrono list
		current->chrono_prev->chrono_next = NULL;
		chrono_tail_ = current->chrono_prev;
	} else {
		// If the iterator is in the middle of the chrono list
		current->chrono_next->chrono_prev = current->chrono_prev;
		current->chrono_prev->chrono_next = current->chrono_next;
	}
	if (current->sorted_prev == NULL) {
		// If the iterator is at the beginning of the sorted list
		current->sorted_next->sorted_prev = NULL;
		sorted_head_ = current->sorted_next;
	} else if (current->sorted_next == NULL) {
		// If the iterator is at the end of the sorted list
		current->sorted_prev->sorted_next = NULL;
		sorted_tail_ = current->sorted_prev;
	} else {
		// If the iterator is in the middle of the sorted list
		current->sorted_next->sorted_prev = current->sorted_prev;
		current->sorted_prev->sorted_next = current->sorted_next;
	}
	++itr;
	--count_;
	delete current;
	return itr;
}

// Define the copy_list function in MultiLL class
template <class T>
void MultiLL<T>::copy_list(const MultiLL<T>& old) {
	// Creates a new MultiLL
	Node<T>* temp_old = old.chrono_head_;
	// Create a new Node and copy old Node
	while(temp_old != NULL) {
		add(temp_old->value);
		temp_old = temp_old->chrono_next;
	}
}

// Define the destroy_list function in MultiLL class
template <class T>
void MultiLL<T>::destroy_list() {
	// If the list is empty set all head/tail ptrs to NULL
	if (count_ == 0) {
		chrono_head_ = chrono_tail_ = sorted_head_ = sorted_tail_= random_head_ = NULL;
		return;
	}
	Node<T>* next, *current = chrono_head_;
	// Loop through the list chronologically and delete each Node as passing
	while(current != NULL) {
		next = current->chrono_next;
		delete current;
		current = next;	
	}
	chrono_head_ = chrono_tail_ = sorted_head_ = sorted_tail_ = random_head_ = NULL;
	count_ = 0;
}


#endif
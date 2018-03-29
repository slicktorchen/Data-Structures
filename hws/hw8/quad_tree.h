// ===================================================================
//
// We provide the Point class and the implementation of several
// QuadTree member functions for printing.  
//
// IMPORTANT: You should modify this file to add all of the necessary
// functionality for the QuadTree class and its helper classes: Node,
// DepthIterator, and BreadthIterator.
//
// ===================================================================

#ifndef quad_tree_h_
#define quad_tree_h_

#include <iostream>
#include <vector>
#include <cassert>
#include <map>
#include <list>
#include <iterator>

using namespace std;

// ==============================================================
// ==============================================================
// A tiny templated class to store 2D coordinates.  This class works
// with number_type = int, float, double, unsigned char (a 1 byte=8
// bit integer), short (a 2 byte=16 bit integer).

template <class number_type>
class Point {
public:
	Point() : x(0),y(0) {}
  Point(const number_type& x_, const number_type& y_) : x(x_),y(y_) {}
  Point& operator=(const Point &old) { x = old.x; y = old.y; return *this; }
  bool operator==(const Point<number_type> &other) { return x == other.x && y == other.y; }
  // REPRESENTATION
  number_type x;
  number_type y;
};

// a helper function to print Points to STL output stream
template <class number_type>
inline std::ostream& operator<<(std::ostream &ostr, const Point<number_type> &pt) {
  ostr << "(" << pt.x << "," << pt.y << ")";
  return ostr;
}


////////////////////// NODE CLASS ////////////////////////////////
template<class number_type, class label_type>
class Node {
public:
	Node() : pt(0,0), label(' ') {}
	Node(const Point<number_type> &point,label_type lbl = ' ') {
		pt = point;
		label = lbl;
		for (unsigned int i = 0; i < 4; ++i) {
			children[i] = NULL;
		}
		parent = NULL;
	}
	// REPRESENTATION
	Point<number_type> pt;
	label_type label;
	Node<number_type,label_type>* children[4];
	Node<number_type,label_type>* parent;
};

/////////////////////// DEPTH ITERATOR CLASS //////////////////////////
template <class number_type,class label_type>
class DepthIterator {
public:
  DepthIterator() : ptr_(NULL) {}
  DepthIterator(Node<number_type,label_type>* p) {
	  ptr_ = p; 
	  if (ptr_ != NULL && ptr_->parent == NULL) {
		  // Creation the df_list only occurs when begin() is called
		  Node<number_type,label_type> *temp = ptr_;
		  // Builds a list of Nodes in Depth First order
		  depth_first(ptr_,df_list);
		  ptr_ = temp;
	  }
  }
  DepthIterator(const DepthIterator& old) : ptr_(old.ptr_) {}
  ~DepthIterator() {}
  DepthIterator& operator=(const DepthIterator& old) { 
	  ptr_ = old.ptr_;  
	  
	  return *this; 
  }
  // operator* gives constant access to the value at the pointer
  const Point<number_type>& operator*() const { return ptr_->pt; }
  // comparions operators are straightforward
  bool operator== (const DepthIterator& rgt) { return ptr_ == rgt.ptr_; }
  bool operator!= (const DepthIterator& rgt) { return ptr_ != rgt.ptr_; }

  label_type getLabel() const { return ptr_->label; }

  ////////////// PRE INCREMENT OPERATOR //////////////////////////
  DepthIterator<number_type,label_type>& operator++() { 
	typename list<Node<number_type,label_type>*>::const_iterator itr;
	for (itr = df_list.begin(); itr != df_list.end(); ++itr) {
		if (*itr == ptr_) {
			// If the location of the current ptr is found, return the next iterator
			++itr;
			if (itr == df_list.end()) {
				// If the iterator is at last Node, return NULL
				ptr_ = NULL;
				return *this;
			} else {
				// Else return the next Node
				ptr_ = *itr;
				return *this;
			}
		}
	}
	return *this;
  }

  /////////////////// POST INCREMENT OPERATOR ////////////////////
  DepthIterator<number_type,label_type> operator++(int) { 
    DepthIterator<number_type,label_type> temp(*this);
	typename list<Node<number_type,label_type>*>::const_iterator itr;
	for (itr = df_list.begin(); itr != df_list.end(); ++itr) {
		if (*itr == ptr_) {
			// If the location of the current ptr is found, return the next iterator
			++itr;
			if (itr == df_list.end()) {
				// If the iterator is at last Node, return NULL
				ptr_ = NULL;
				return temp;
			} else {
				ptr_ = *itr;
				// Else return the next Node
				return temp;
			}
		}
	}
	return temp;
  }

  ///////////////////////////// GETDEPTH FUNCTION ///////////////////////////
  int getDepth() const {
	  int depth = 0;
	  Node<number_type,label_type> *temp = ptr_;
	  while (temp->parent) {
		  // Counts how many times the ptr travels up one level to a parent node
		  temp = temp->parent;
		  ++depth;
	  }
	  return depth;
  }

private:
  // representation
  Node<number_type,label_type>* ptr_;
  list<Node<number_type,label_type>*> df_list;

  // HELPER FUNCTIONS
  ////////////////////// DEPTH FIRST TRAVERSAL ///////////////////////////
  void depth_first(Node<number_type,label_type>* p,list<Node<number_type,label_type>*> &df_list) {
	if (p == NULL) {
		return;
	}
	// Add values to the list if it exists
	df_list.push_back(p);
	depth_first(p->children[0],df_list);
	depth_first(p->children[1],df_list);
	depth_first(p->children[2],df_list);
	depth_first(p->children[3],df_list);

  }
};

////////////////////////////// BREADTH ITERATOR CLASS ///////////////////////////
template <class number_type,class label_type>
class BreadthIterator {
public:
	// CONSTRUCTOR/ASSIGNMENT/DESTRUCTOR
  BreadthIterator() : ptr_(NULL) {}
  BreadthIterator(Node<number_type,label_type>* p) {
	  ptr_ = p; 
	  if (ptr_ != NULL && ptr_->parent == NULL) {
		  // Creation of the bf_list occurs only when the begin() is called
		  // Stores the location of the current pointer
		  Node<number_type,label_type> *temp = ptr_;
		  // Creates a list of the Nodes stored in breadth first order
		  breadth_first(ptr_,bf_list);
		  ptr_ = temp;
	  }
  }
  BreadthIterator(const BreadthIterator& old) : ptr_(old.ptr_) {}
  ~BreadthIterator() {}
  BreadthIterator& operator=(const BreadthIterator& old) { ptr_ = old.ptr_;  return *this; }
  
  // operator* gives constant access to the value at the pointer
  const Point<number_type>& operator*() const { return ptr_->pt; }
  // comparions operators are straightforward
  bool operator== (const BreadthIterator& rgt) { return ptr_ == rgt.ptr_; }
  bool operator!= (const BreadthIterator& rgt) { return ptr_ != rgt.ptr_; }

  const label_type getLabel() { return ptr_->label; }


  ///////////////////////////// PRE INCREMENT OPERATOR ///////////////////////////
  BreadthIterator<number_type,label_type>& operator++() { 
	typename list<Node<number_type,label_type>*>::const_iterator itr;
	for (itr = bf_list.begin(); itr != bf_list.end(); ++itr) {
		if (*itr == ptr_) {
			// If the location of the current ptr is found, return the next iterator
			++itr;
			if (itr == bf_list.end()) {
				// If the iterator is at last Node, return NULL
				ptr_ = NULL;
				return *this;
			} else {
				// Else return the next Node
				ptr_ = *itr;
				return *this;
			}
		}
	}
	return *this;
}

  ///////////////////////// POST INCREMENT OPERATOR ////////////////////////////
  BreadthIterator<number_type,label_type> operator++(int) { 
    BreadthIterator<number_type,label_type> temp(*this);
	typename list<Node<number_type,label_type>*>::const_iterator itr;
	for (itr = bf_list.begin(); itr != bf_list.end(); ++itr) {
		if (*itr == ptr_) {
			// If the location of the current ptr is found, return the next iterator
			++itr;
			if (itr == bf_list.end()) {
				// If the iterator is at last Node, return NULL
				ptr_ = NULL;
				return temp;
			} else {
				// Else return the next Node
				ptr_ = *itr;
				return temp;
			}
		}
	}
	return *this;
  }
  
  //////////////////////////// GETDEPTH FUNCTION //////////////////////////////////
  int getDepth() const {
	  int depth = 0;
	  Node<number_type,label_type> *temp = ptr_;
	  while (temp->parent) {
  		  // Counts how many times the ptr travels up one level to a parent node
		  temp = temp->parent;
		  ++depth;
	  }
	  return depth;
  }


private:
  // Representation
  Node<number_type,label_type>* ptr_;
  list<Node<number_type,label_type>*> bf_list;

  // HELPER FUNCTIONS
  void breadth_first(Node<number_type,label_type>* p,list<Node<number_type,label_type>*> &bf_list) {
	  if (p == NULL) {
		  return;
	  }
	  list<Node<number_type,label_type>*> queue;
	  Node<number_type,label_type>* node;
	  queue.push_back(p);
	  // Stores the nodes of the tree in breadth first order
	  bf_list.push_back(p);
	  while (queue.size() != 0) {
		  node = queue.front();
		  queue.pop_front();
		  for (int i = 0; i < 4; ++i) {
			  if (node->children[i] != NULL) {
				  queue.push_back(node->children[i]);
				  bf_list.push_back(node->children[i]);
			  }
		  }
	  }
  }
};

///////////////////////// QUAD TREE CLASS //////////////////////////////
template<class number_type, class label_type>
class QuadTree { 
public:
	// CONSTRUCTORS/ASSIGNMENT/DESTRUCTOR
	QuadTree() : size_(0), root_(NULL) {}
	QuadTree(const QuadTree<number_type,label_type>& old) : size_(old.size_) { 
		root_ = this->copy_tree(old.root_); }
	~QuadTree() { 
		if(root_) {
			this->destroy_tree(root_);  
			root_ = NULL; 
		}
	}
	QuadTree& operator=(const QuadTree<number_type,label_type>& old) {
		if (&old != this) {
			this->destroy_tree(root_);
			root_ = this->copy_tree(old.root_);
			size_ = old.size_;
		}
		return *this;
	}
	
	// PUBLIC METHODS
	unsigned int size() const { return size_; }
	int height() const{ return height(root_); }

	// ITERATORS
	typedef DepthIterator<number_type,label_type> iterator;
	typedef BreadthIterator<number_type,label_type> bf_iterator;
	iterator end() { return iterator(NULL); }
	iterator begin() {return iterator(root_);}
	bf_iterator bf_end() { return bf_iterator(NULL); }
	bf_iterator bf_begin() { return bf_iterator(root_); }
		
	////////////////////////////// find function /////////////////////////////////////
	iterator find(number_type x, number_type y) { 
		Point<number_type> point(x,y); 
		return find(point, root_); 
	}

	///////////////////////////// insert function ////////////////////////////////
	pair<iterator,bool> insert(const Point<number_type>& point,const label_type &label) {
		return insert(point,label,root_,NULL);
	}

	/////////////////////////// plot function ////////////////////////////////////
	// takes in the maximum x and y coordinates for these data points
	// the optional argument draw_lines defaults to true
	void plot(int max_x, int max_y, bool draw_lines=true) const {
		// allocate blank space for the center of the board
		std::vector<std::string> board(max_y+1,std::string(max_x+1,' '));
		// edit the board to add the point labels and draw vertical and
		// horizontal subdivisions
		plot(root_,board,0,max_x,0,max_y,draw_lines);
		// print the top border of the plot
		std::cout << "+" << std::string(max_x+1,'-') << "+" << std::endl;
		for (int i = 0; i <= max_y; i++) {
		// print each row of the board between vertical border bars
		std::cout << "|" << board[i] << "|" << std::endl;
		}
		// print the top border of the plot
		std::cout << "+" << std::string(max_x+1,'-') << "+" << std::endl;
	}

	

	//////////////////////// print_sideways function ////////////////////////////
	void print_sideways() const { print_sideways(root_,""); }

//////////////////////////// PRIVATE VARIBLES/METHODS //////////////////////////////
private:
	// QUAD TREE REPRESENTATION
	unsigned int size_;
	Node<number_type,label_type>* root_;

	// PRIVATE HELPER FUNCTIONS

	Node<number_type,label_type>* copy_tree(Node<number_type,label_type>* old_root);
	void destroy_tree(Node<number_type,label_type>* old);

	////////////////////////////// FIND FUNCTION ///////////////////////////////////
	iterator find(const Point<number_type> &point, Node<number_type,label_type>* p) {
		if (!p) { return iterator(NULL); }
		if (point.x == p->pt.x && point.y == p->pt.y) { 
			// If the point is found, return an iterator to this point
			return iterator(p); 
		}
		bool found = false;
		for (int i = 0; i < 4; ++i) {
			if (p->children[i] && p->children[i]->pt.x == point.x && p->children[i]->pt.y == point.y) {
				// If any of one of the children Nodes have the point that we are looking
				// for, return an iterator to that child
				found = true;
				return iterator(p->children[i]);
			}
		}
		if (!found) {
			// If the point is not found within the children Nodes, choose the 
			// appropriate child pointer to follow
			for (int i = 0; i < 4; ++i) {
				if (point.x < p->pt.x && point.y < p->pt.y) {
					// If the point is in the UPPER LEFT quadrant, go to the child
					// Node that is located in the same quadrant
					if (p->children[i] && p->children[i]->pt.x < p->pt.x && p->children[i]->pt.y < p->pt.y) {
						return find(point,p->children[i]);
					}
				} else if (point.x > p->pt.x && point.y < p->pt.y) {
					// If the point is in the UPPER RIGHT quadrant, go to the child
					// Node that is located in the same quadrant
					if (p->children[i] && p->children[i]->pt.x > p->pt.x && p->children[i]->pt.y < p->pt.y) {
						return find(point,p->children[i]);
					}
				} else if (point.x < p->pt.x && point.y > p->pt.y) {
					// If the point is in the LOWER LEFT quadrant, go to the child
					// Node that is located in the same quadrant
					if (p->children[i] && p->children[i]->pt.x < p->pt.x && p->children[i]->pt.y > p->pt.y) {
						return find(point,p->children[i]);
					}
				} else if (point.x > p->pt.x && point.y > p->pt.y) {
					// If the point is in the LOWER RIGHT quadrant, go to the child
					// Node that is located in the same quadrant
					if (p->children[i] && p->children[i]->pt.x > p->pt.x && p->children[i]->pt.y > p->pt.y) {
						return find(point,p->children[i]);
					}
				} 
			}
		} 
		return iterator(NULL);
	}

	///////////////////////////// INSERT FUNCTION //////////////////////////////////
	pair<iterator,bool> insert(const Point<number_type>& point,label_type label, Node<number_type,label_type> *&p
		, Node<number_type,label_type> *parent) {
		if (!p) {
			// When an open slot is found create a new Node node at this location
			// have it store the point
			p = new Node<number_type,label_type>(point,label);
			p->parent = parent;
			this->size_++;
			return pair<iterator,bool>(iterator(p), true);
		} 

		if (point.x < p->pt.x && point.y < p->pt.y) {
			// If the point is in the UPPER LEFT quadrant, go to the 0th child
			// and see if it can be inserted
			return insert(point,label,p->children[0],p);
		} else if (point.x > p->pt.x && point.y < p->pt.y) {
			// If the point is in the UPPER RIGHT quadrant, go to the 0th child
			// and see if it can be inserted
			return insert(point,label,p->children[1],p);
		} else if (point.x < p->pt.x && point.y > p->pt.y) {
			// If the point is in the LOWER LEFT quadrant, go to the 0th child
			// and see if it can be inserted
			return insert(point,label,p->children[2],p);
		} else if (point.x > p->pt.x && point.y > p->pt.y) {
			// If the point is in the LOWER RIGHT quadrant, go to the 0th child
			// and see if it can be inserted
			return insert(point,label,p->children[3],p);
		} else {
			// If the point already exists in the tree, return a pair with a bool
			// value of false
			return pair<iterator,bool>(iterator(p), false);
		}

	}

	//////////////////////////// HEIGHT FUNCTION ////////////////////////////////
	int height(Node<number_type,label_type>* p) const {
		if (p == NULL) {
			return -1;
		} 
		int value, max = -1;
		for (int i = 0; i < 4; ++i) {
			// The loop finds the paths among the four children and determines the 
			// max path length to a leaf node
			value = height(p->children[i]);
			if (value > max) {
				max = value;
			}
		}
		return 1 + max;
	}

	////////////////////// ACTUAL RECURSIVE PLOT FUNCTION ///////////////////////////
	void plot(Node<number_type,label_type> *p, std::vector<std::string> &board,
			  int x_min, int x_max, int y_min, int y_max, bool draw_lines) const {
		// base case, draw nothing if this node is NULL
		if (p == NULL) return;
		// check that the dimensions range of this node make sense
		assert (x_min >= 0 && x_min <= x_max);
		assert (y_min >= 0 && y_min <= y_max);
		assert (board.size() >= (unsigned int)y_max);
		assert (board[0].size() >= (unsigned int)x_max);
		// verify that the point stored at this node fits on the board
		assert (p->pt.y >= 0 && p->pt.y < (int)board.size());
		assert (p->pt.x >= 0 && p->pt.x < (int)board[0].size());
		// draw the vertical and horizontal bars extending across the
		// range of this node
		if (draw_lines) {
			for (int x = x_min; x <= x_max; x++) {
				board[p->pt.y][x] = '-';
			}
			for (int y = y_min; y <= y_max; y++) {
				board[y][p->pt.x] = '|';
			}
		}
		// draw this label
		board[p->pt.y][p->pt.x] = p->label;
		// recurse on the 4 children
		plot(p->children[0],board,x_min ,p->pt.x-1,y_min ,p->pt.y-1,draw_lines);
		plot(p->children[1],board,p->pt.x+1,x_max ,y_min ,p->pt.y-1,draw_lines);
		plot(p->children[2],board,x_min ,p->pt.x-1,p->pt.y+1,y_max ,draw_lines);
		plot(p->children[3],board,p->pt.x+1,x_max ,p->pt.y+1,y_max ,draw_lines);
	}
	// prints all of the tree data with a pre-order (node first, then
	// children) traversal of the tree structure

	////////////////// ACTUAL RECURSIVE PRINT SIDEWAYS FUNCTION //////////////////////
	void print_sideways(Node<number_type,label_type>* p, const std::string &indent) const {
		// base case
		if (p == NULL) return;
		// print out this node
		std::cout << indent << p->label << " (" << p->pt.x << "," << p->pt.y << ")" << std::endl;
		// recurse on each of the children trees
		// increasing the indentation
		print_sideways(p->children[0],indent+"  ");
		print_sideways(p->children[1],indent+"  ");
		print_sideways(p->children[2],indent+"  ");
		print_sideways(p->children[3],indent+"  ");
	}

};

///////////////////////////// DESTROY TREE FUNCTION /////////////////////////////
template<class number_type,class label_type> 
void QuadTree<number_type,label_type>::destroy_tree(Node<number_type,label_type>* p) {
	if (p != NULL) {
		// If the tree is not empty, delete the tree
		for (int i = 0; i < 4; ++i) {
			// Recursion through each of the children
			destroy_tree(p->children[i]);
		}
		delete p;
		p = NULL;
		size_ = 0;
	}
}

////////////////////////////// COPY TREE FUNCTION /////////////////////////////////
template<class number_type,class label_type> 
Node<number_type,label_type>* QuadTree<number_type,label_type>::copy_tree(Node<number_type,label_type>* old) {
	if (old == NULL) {
		// If the tree is empty, return NULL
		return NULL;
	}
	Node<number_type,label_type>* copyNode = new Node<number_type,label_type>;
	copyNode->pt = old->pt;
	copyNode->label = old->label;
	for (int i = 0; i < 4; ++i) {
		// Recursion through each of the children
		copyNode->children[i] = copy_tree(old->children[i]);
	}
	return copyNode;
}

#endif

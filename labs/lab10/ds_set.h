// Partial implementation of binary-tree based set class similar to std::set.  
// The iterator increment & decrement operations have been omitted.
#ifndef ds_set_h_
#define ds_set_h_
#include <iostream>
#include <utility>

using namespace std;

// -------------------------------------------------------------------
// TREE NODE CLASS 
template <class T>
class TreeNode {
public:
  TreeNode() : left(NULL), right(NULL) {}
  TreeNode(const T& init) : value(init), left(NULL), right(NULL) {}
  T value;
  TreeNode* left;
  TreeNode* right;
};

template <class T> class ds_set;

// -------------------------------------------------------------------
// TREE NODE ITERATOR CLASS
template <class T>
class tree_iterator {
public:
  tree_iterator() : ptr_(NULL) {}
  tree_iterator(TreeNode<T>* p) : ptr_(p) {}
  tree_iterator(const tree_iterator& old) : ptr_(old.ptr_) {}
  ~tree_iterator() {}
  tree_iterator& operator=(const tree_iterator& old) { ptr_ = old.ptr_;  return *this; }
  // operator* gives constant access to the value at the pointer
  const T& operator*() const { return ptr_->value; }
  // comparions operators are straightforward
  bool operator== (const tree_iterator& rgt) { return ptr_ == rgt.ptr_; }
  bool operator!= (const tree_iterator& rgt) { return ptr_ != rgt.ptr_; }
  // increment & decrement will be discussed in Lecture 19 and Lab 11

private:
  // representation
  TreeNode<T>* ptr_;
};

// -------------------------------------------------------------------
// CS2 SET CLASS
template <class T>
class ds_set {
public:
  ds_set() : root_(NULL), size_(0) {}
  ds_set(const ds_set<T>& old) : size_(old.size_) { 
    root_ = this->copy_tree(old.root_); }
  ~ds_set() { this->destroy_tree(root_);  root_ = NULL; }
  ds_set& operator=(const ds_set<T>& old) {
    if (&old != this) {
      this->destroy_tree(root_);
      root_ = this->copy_tree(old.root_);
      size_ = old.size_;
    }
    return *this;
  }

  typedef tree_iterator<T> iterator;

  int size() const { return size_; }
  bool operator==(const ds_set<T>& old) const { return (old.root_ == this->root_); }

  // FIND, INSERT & ERASE
  iterator find(const T& key_value) { return find(key_value, root_); }
  std::pair< iterator, bool > insert(T const& key_value) { return insert(key_value, root_); }
  int erase(T const& key_value) { return erase(key_value, root_); }
  
  // OUTPUT & PRINTING
  friend std::ostream& operator<< (std::ostream& ostr, const ds_set<T>& s) {
    s.print_in_order(ostr, s.root_);
    return ostr;
  }
  void print_as_sideways_tree(std::ostream& ostr) const {
    print_as_sideways_tree(ostr, root_, 0); }

  // ITERATORS
  iterator begin() const { 
    if (!root_) return iterator(NULL);
    TreeNode<T>* p = root_;
    while (p->left) p = p->left;
    return iterator(p);
  }
  iterator end() const { return iterator(NULL); }

private:
  // REPRESENTATION
  TreeNode<T>* root_;
  int size_;

  // PRIVATE HELPER FUNCTIONS
  TreeNode<T>*  copy_tree(TreeNode<T>* old_root) {
    // Implemented in Lab 10
	  TreeNode<T>* copyNode = new TreeNode<T>;
	  if (old_root == NULL) {
		  return NULL;
	  }
	  copyNode->value = old_root->value;
	  copyNode->left = copy_tree(old_root->left);
	  copyNode->right = copy_tree(old_root->right);
	  return copyNode;
  }

  void destroy_tree(TreeNode<T>*& p) { /* Implemented in Lecture 19 */  
	if (p != NULL) {
		destroy_tree(p->left);
		destroy_tree(p->right);
		delete p;
		p = NULL;
		size_ = 0;
	}
  }

  // Recursive method
  /*iterator find(const T& key_value, TreeNode<T>* p) {
    if (!p) return iterator(NULL);
    if (p->value > key_value)
      return find(key_value, p->left);
    else if (p->value < key_value)
      return find(key_value, p->right);
    else
      return iterator(p);
  }*/

  // Iterative method
iterator find(const T& key_value, TreeNode<T>* p) {
	TreeNode<T> *current = p;
	bool found = false;
	if (current->value == key_value) {
		return iterator(p);
	}
	while (current->value != key_value) {
		if (current->left == NULL && current->right == NULL) {
			break;
		}
		if (current->value > key_value) {
			current = current->left;
		} else if (current->value < key_value) {
			current = current->right;
		} 
		if (current->value == key_value){
			found = true;
			break;
		}
	}
	if (found) {
		return iterator(current);
	} else {
		return iterator(NULL);
	}
}

  std::pair<iterator,bool> insert(const T& key_value, TreeNode<T>*& p) {
    if (!p) {
      p = new TreeNode<T>(key_value);
      this->size_++;
      return std::pair<iterator,bool>(iterator(p), true);
    }
    else if (key_value < p->value)
      return insert(key_value, p->left);
    else if (key_value > p->value)
      return insert(key_value, p->right);
    else
      return std::pair<iterator,bool>(iterator(p), false);
  }
  
  TreeNode<T>* erase(T const& key_value, TreeNode<T>* &p) {  
	  if (p == NULL) { return NULL; }

	  if (key_value < p->value) {
		  p->left = erase(p_>left,key_value);
	  } else if (key_value > p->value) {
		  p->right = erase(p->right,key_value);

		// If key is same as p's key, this is the node to be deleted
	  } else {
		  // Node with only one child or no child
		  if (p->left == NULL) {
			  TreeNode<T>* temp = p->right;
			  delete p;
			  return temp;
		  } else if (p->right == NULL) {
			  TreeNode<T>* temp = p->left;
			  delete p;
			  return temp;
		  } else { // For two children, find leftmost node in right subtree
			  TreeNode<T>* temp = p->right;
			  whil(temp->left)
				  temp = temp->left;
			  p->value = temp->value; // copy the value
			  // recursively remove the vlaue from the left subtree - it has at most 1 child
			  p->right = erase(temp->value,p->right); 
		  }
	  }
	  return p;
  }

  // Erase with parent pointers
  bool erase(T const& key_value, TreeNode<T>* &p) {
	  if (!p) { return false; }
	  if (p->value < key_value) {
		  return erase(key_value,p->right);
	  } else if (p->value > key_value) {
		  return erase(key_value,p->left);
	  }
	  assert(p->value == key_value);
	  if (!p->left && !p->right) {
		  delete p;
		  p = NULL;
		  this->size_--;
	  } else if (!p->left) {
		  TreeNode<T>* q = p;
		  p = p->right;
		  p->parent = q->parent;
		  delete q;
		  this->size_--;
	  } else if (!p->right) {
		  TreeNode<T>* q = p;
		  p = p->left;
		  p->parent = q->parent;
		  delete q;
		  this->size_--;
	  } else {
		  TreeNode<T>* q = p->left;
		  while (q->right)
			  q = q->right;
		  p->value = q->value;
		  bool check = erase(q->value,p->left);
		  assert(check);
	  }
	  return true;
  }

  void print_in_order(std::ostream& ostr, const TreeNode<T>* p) const {
    if (p) {
      print_in_order(ostr, p->left);
      ostr << p->value << "\n";
      print_in_order(ostr, p->right);
    }
  }

  /*void print_in_order(ostream& ostr, const TreeNode<T>* root) {
	  vector<TreeNode<T>*> stack;
	  TreeNode<T>* current = root;
	  while (current != NULL) {
		  stack.push_back(curent);
		  current = current->left;
	  }
	  while(stack.size() != 0) {
		  current = stack.back();
		  stack.pop_back();
		  ostr << root->;
  }*/

  void bf(TreeNode<T>* tree) {
	  if (tree == NULL) {
		  return;
	  }
	  list<TreeNode<T>*> queue;
	  TreeNode<T>* node;
	  queue.push_back(tree);
	  while (queue.size() != 0) {
		  node = queue.front();
		  queue.pop_front();
		  cout << node->value << endl;
		  if (node->left != NULL) {
			  queue.push_back(node->left);
		  }
		  if (node->right != NULL) {
			  queue.push_back(node->right);
		  }
	  }
  }

  template<class T>
  int height(TreeNode<T>* p) {
	  if (p == NULL) {
		  return 0;
	  }

	  return 1 + max(height(p->left),height(p->right));
  }

  void print_as_sideways_tree(std::ostream& ostr, const TreeNode<T>* p, int depth) const {
    if (p) {
      print_as_sideways_tree(ostr, p->right, depth+1);
      for (int i=0; i<depth; ++i) ostr << "    ";
      ostr << p->value << "\n";
      print_as_sideways_tree(ostr, p->left, depth+1);
    }
  }
};

#endif

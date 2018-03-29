/*void bf(TreeNode<T>* tree) {
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
  }*/
	//if (!ptr_) {
	//	return *this;
	//}
	////while (!NULL) {

	//// Traverses depth first
	//for (int i = 0; i < 4; ++i) {
	//	if (ptr_->children[i] == NULL) {
	//		continue;
	//	} else {
	//		ptr_ = ptr_->children[i];
	//		return *this;
	//	}
	//}
	//// Find the next sibling
	//for (int i = 0; i < 4; ++i) {
	//	if (ptr_ == ptr_->parent->children[i]) {
	//		if (i < 3) {
	//			// If the iterator is not at the fourth child, the iterator points
	//			// to the next sibling
	//			ptr_ = ptr_->parent->children[i+1];
	//			return *this;
	//		} else {
	//			// If iterator is at fourth child, the iterator should move to the next
	//			// Node which is the next sibling of the parent 
	//			for (int j = 0; j < 4; ++j) {
	//				if (ptr_->parent == ptr_->parent->parent->children[j]) {
	//					if (j < 3) {
	//						// If the iterator is not at the fourth parent sibling 
	//						// move to the next sibling of the parent
	//						ptr_ = ptr_->parent->parent->children[j+1];
	//						return *this;
	//					} else {
	//						// If the iterator is at the fourth sibling of the parent
	//						// then the iterator has reached the end of the tree
	//						ptr_ = NULL;
	//						return *this;
	//					}
	//				}
	//			}
	//		}
	//	}
	//}
 //   return *this;

if (!ptr_) {
		return temp;
	}
	int j = this->getDepth();
	cout << j << endl;
	// Traverses depth first
	for (int i = 0; i < 4; ++i) {
		if (ptr_->children[i] == NULL) {
			continue;
		} else {
			ptr_ = ptr_->children[i];
			return temp;
		}
	}
	// Find the next sibling
	for (int i = 0; i < 4; ++i) {
		if (ptr_ == ptr_->parent->children[i]) {
			if (i < 3) {
				// If the iterator is not at the fourth child, the iterator points
				// to the next sibling
				ptr_ = ptr_->parent->children[i+1];
				return temp;
			} else {
				// If iterator is at fourth child, the iterator should move to the next
				// Node which is the next sibling of the parent 
				for (int j = 0; j < 4; ++j) {
					if (ptr_->parent == ptr_->parent->parent->children[j]) {
						if (j < 3) {
							// If the iterator is not at the fourth parent sibling 
							// move to the next sibling of the parent
							ptr_ = ptr_->parent->parent->children[j+1];
							return temp;
						} else {
							// If the iterator is at the fourth sibling of the parent
							// then the iterator has reached the end of the tree
							ptr_ = NULL;
							return temp;
						}
					}
				}
			}
		}
	}
    return temp;


	/////////////////// BREADTH FIRST //////////////////
	if (!ptr_) {
		return *this;
	}
	if (ptr_->parent == NULL) {
		// If the iterator is at the root, move the iterator to the first child
		// of the root
		ptr_ = ptr_->children[0];
		return *this;
	}
	  
		// Find the next sibling
	for (int i = 0; i < 4; ++i) {
		if (ptr_ == ptr_->parent->children[i]) {
			if (i < 3) {
				// If the iterator is not at the fourth child, the iterator points
				// to the next sibling
				ptr_ = ptr_->parent->children[i+1];
				return *this;
			} else if (ptr_->parent->parent) {
				// If the iterator has a depth of at least 2
				for (int j = 0; j < 4; ++j) {
					if (ptr_->parent == ptr_->parent->parent->children[j]) {
						// Find the next parent sibling 
						if (j < 3) {
							ptr_ = ptr_->parent->parent->children[j+1]->children[0];
							return *this;
						}
					}
				}
			} else {
				ptr_ = ptr_->parent->children[0]->children[0];
				return *this;
			}
		}
	}
	ptr_ = NULL;
	return *this;


	void breadth_first(Node<number_type,label_type>* p,list<Node<number_type,label_type>*> &bf_list) {
	  if (p == NULL) {
		  return;
	  }
	  /*vector<int> val;
	  bf_list.push_back(p);
	  for (int i = 0; i < 4; ++i) {
		  if (p->children[i] != NULL) {
			  val.push_back(i);
			  bf_list.push_back(p->children[i]);
		  }
	  }

	  for (int i = 0; i < val.size(); ++i) {
		  breadth_first(p->children[val[i]],bf_list);
	  }*/

	  list<Node<number_type,label_type>*> queue;
	  Node<number_type,label_type>* node;
	  queue.push_back(p);
	  bf_list.push_back(p);
	  while (queue.size() != 0) {
		  node = queue.front();
		  queue.pop_front();
		  //cout << node->value << endl;
		  bf_list.push_back(node);
		  for (int i = 0; i < 4; ++i) {
			  if (node->children[i] != NULL) {
				  queue.push_back(node->children[i]);
			  }
		  }
	  }
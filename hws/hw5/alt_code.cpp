		// For the first Node, chrono_prev points to NULL
		if (counter == 0) { 
			temp->chrono_prev = NULL; 
		} else if (counter < old.size()) {
			temp->chrono_prev = chrono_itr->chrono_prev;
		// For the last Node, chrono_next points to NULL and head->chrono_tail_ points to this Node
		} else {
			temp->next = NULL;
			temp->chrono_prev = chrono_itr->chrono_prev;
			head->chrono_tail_ = chrono_itr;
			break;
		}
		// Create a new Node for copying (only happens in first loop)
		temp->chrono_next = new Node;
		temp->chrono_next = chrono_itr->chrono_next;
		temp = temp->chrono_next;
		++counter;
	}
	head->sorted_head_ = old->sorted_head_;
	sorted_itr = head.begin_chronological();
	random_itr = head.begin_random();
	// Goes through each element chronologically and copies the pointers for sorted and random
	for (chrono_itr = old.begin_chronological(); chrono_itr != old.end_chronological(); ++chrono_itr) {
		if (chrono_itr->sorted_next == NULL) {
			head->sorted_tail_ = chrono_itr;
		}
		random_itr->random_next = chrono_itr->random_next;
		sorted_itr->sorted_next = chrono_itr->sorted_next;
		sorted_itr->sorted_prev = chrono_itr->sorted_prev;
		++sorted_itr;
	}
	/*temp = old->random_head_;
	head->random_head_ = temp;
	random_itr = head.begin_random();
	while(temp->random_next != head->random_head_) {
		temp->random_next = new Node;
		temp->random_next = random_itr->random_next;
		temp = temp->random_next;
	}*/



	// Goes through each element chronologically and copies the pointers for sorted_head_, sorted_tail_, and random_head_
	//for (chrono_itr1 = head.begin_chronological(); chrono_itr1 != head.end_chronological; ++chrono_itr1) {
	//	for (chrono_itr2 = old.begin_chronological(); chrono_itr2 != old.end_chronological(); ++chrono_itr2) {
	//		if (chrono_itr == random_itr) {
	//			head->random_head_ = chrono_itr;
	//		}
	//		if (chrono_itr == sorted_itr) {
	//			if (sorted_itr->sorted_prev == NULL) {
	//				head->chrono_head_ = chrono_itr;
	//			} else if (sorted_itr->sorted_next == NULL) {
	//				head->chrono_tail_ = chrono_itr;
	//			}
	//			////////////////////////////////////////////////////////////
	//			//chrono_itr->sorted_prev = sorted_itr->sorted_prev;
	//			//chrono_itr->sorted_next = sorted_itr->sorted_next;
	//			//chrono_itr->random_next = sorted_itr->random_next;
	//		}
	//	}
	//}

	temp = old.begin_chronological();
	head->chrono_head_ = temp;
	typename MultiLL<T>::iterator chrono_itr1(old.begin_chronological(),"chrono"), chrono_itr2(old.begin_chronologcial(),"chrono"), sorted_itr("sorted"), random_itr("random");
	for (chrono_itr1 = old.begin_chronological(); chrono_itr1 != old.end_chronological(); ++chrono_itr1) {
		// For the first Node, chrono_prev points to NULL
		if (counter == 0) { 
			temp->chrono_prev = NULL; 
		} else if (counter < old.size()) {
			temp->chrono_prev = prev;
		// For the last Node, chrono_next points to NULL and head->chrono_tail_ points to this Node
		} else {
			temp->next = NULL;
			temp->chrono_prev = prev;
			head->chrono_tail_ = temp;
			break;
		}
		// Copies values 
		temp = chrono_itr1;
		prev = temp;
		// Create a new Node for copying (only happens in first loop)
		temp->chrono_next = new Node<T>;
		temp->chrono_next = chrono_itr1->chrono_next;
		temp = temp->chrono_next;
		++counter;
	}
	count_ = counter;
	
	random_itr = old.begin_random();
	// Fixes MultiLL pointers to the new locations in the new MultiLL
	for (chrono_itr1 = head.begin_chronological(),chrono_itr2 = old.begin_chronological(); chrono_itr1 != head.end_chronological,chrono_itr2 != old.end_chronological(); ++chrono_itr1,++chrono_itr2) {
		if (chrono_itr2->sorted_next == NULL) {
			head->sorted_tail_ = chrono_itr1;
		} if (chrono_itr2->sorted_prev == NULL) {
			head->sorted_head_ = chrono_itr1;
		} if (*chrono_itr2 == *random_itr) {
			head->random_head_ = chrono_itr1;
		}
	}
	// temp1 stores the current Node in the old list
	// temp2 stores the next sorted Node from the current Node
	// temp3 stores the current Node in the new list
	typename MultiLL<T>::iterator  chrono_itr3("chrono");
	Node<T>* temp1, temp2, temp3;
	// Iterates through the old list
	for (chrono_itr2 = old.begin_chronological(); chrono_itr2 != old.end_chronological(); ++chrono_itr2) {
		temp1 = *chrono_itr2;
		temp2 = chrono_itr2->sorted_next;
		// Iterates through the new list
		for (chrono_itr3 = head.begin_chronological(); chrono_itr3 != head.end_chronological(); ++chrono_itr3) {
			// 
			if (*chrono_itr2 == *chrono_itr3) {
				temp3 = *chrono_itr3;
			}
			if (temp2 == *chrono_itr3) {
				temp3->sorted_next = chrono_itr3;
			}
		}
	}


	//cout << "seeded by the current time: ";
		int random_count = 1;
		MTRand_int32 mtrand_autoseed(time(NULL));
		iterator itr = iterator(chrono_head_,"chrono");
		for (int i = 0; i < count_; ++i,++itr) {
			itr.getPtr()->random_next = NULL;
		}
		iterator itr_head = iterator(chrono_head_,"chrono");
		iterator *itr_chrono, *itr_random;
		itr_random = itr_chrono = &(itr_head+(mtrand_autoseed() % (count_)));
		random_head_ = itr_random->getPtr();
		std::cout << "HEAD " << **itr_random << std::endl;
		/*(*prev)->random_next = *itr_chrono;
		iterator itr = iterator(random_head_,"random"); 
		iterator itr_random = itr+(mtrand_autoseed() % (count_+1));*/
		for ( ; random_count < count_; ) {
			iterator *itr_temp;

			itr_temp = &(itr_head+(mtrand_autoseed() % (count_)));
			if (itr_temp->getPtr()->random_next == NULL) {
				++random_count;
				itr_chrono->getPtr()->random_next = itr_temp->getPtr();
				itr_temp->getPtr()->random_next = itr_random->getPtr();
				itr_chrono = itr_temp;
				std::cout << "HELLO " << **itr_temp << std::endl;
			} else {
				std::cout << "NULL " << random_count << std::endl;
			}
		}  
		return *itr_random;//iterator(random_head_,"random"); 

		/*list_iterator<T>& operator+(int inc) {
		list_iterator<T>* temp = new list_iterator<T>(this->ptr_,this->type_);
		std::cout << inc << std::endl;
		if (temp->type_ == "chrono") { 
			for (int i = 0; i < inc; ++i) {
				temp->ptr_ = temp->ptr_->chrono_next;
			}
		}
		else if (temp->type_ == "sorted") { 
			for (int i = 0; i < inc; ++i) {
				temp->ptr_ = temp->ptr_->sorted_next; 
			}
		}
		else if (temp->type_ == "random") { 
			for (int i = 0; i < inc; ++i) {
				temp->ptr_ = temp->ptr_->random_next; 
			}
		}
		return *temp;
	}*/
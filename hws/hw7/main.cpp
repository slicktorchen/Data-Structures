#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <cstring>
#include <vector>
#include <iterator>

#include "query.h"

using namespace std;

// Finds and prints the original query, location, amount of error in the
// query found, and the query found
void find_query(string sequence, string kmer, Query query) {
	string search;
	unsigned int i,j,k;
	// Iterates through the sequence to search for the given kmer
	for (i = 0, k = kmer.size() +i; i < sequence.size()-kmer.size(); ++i) {
		search = sequence.substr(i,k);
		if (search == kmer) {
			// If the kmer is found, add the index of the kmer to the query 
			// indices vector
			query.addIndex(i);
		}
	}
	vector<int> indices = query.getIndices();
	int counter,num_found = 0;
	bool found;
	cout << "Query: " << query.getQuery() << endl;
	// Iterates through the indices of kmer locations 
	for (i = 0; i < indices.size(); ++i) {
		counter = 0;
		found = true;
		// Checks if the rest of the segment of the sequence after the kmer 
		// matches the original query within an acceptable error
		for (j = indices[i] + kmer.size(),k = kmer.size(); j < indices[i] + query.getQuery().size(),k < query.getQuery().size(); ++j,++k) {
			if (query.getQuery()[k] != sequence[j]) {
				// Counts up the errors
				++counter;
			}
			if (counter > query.getError()) {
				// If error exceeds the acceptable limit, 
				// continue on to the next kmer location
				found = false;
				break;
			}
		}
		if (found) {
			// If the segment of sequence matches the query, print out that segment
			cout << indices[i] << " " << counter << " " << sequence.substr(j-query.getQuery().size(),query.getQuery().size()) <<  endl;
			++num_found;
		}
	}
	if (num_found == 0) {
		// If no query matches are found, print out "No Match"
		cout << "No Match" << endl;
	}
}

int main(int argc, char* argv[]) {
	int k,error;
	string word,sequence_section,sequence,query,kmer,filename;
	map<string,Query> kmers;
	// Parses data
	cin >> word >> filename;
	fstream istr2(filename.c_str());
	if (!istr2.good()) {
		cerr << "Can't open " << argv[1] << " to read" << endl;
		return 1;
	}
	while (istr2 >> sequence_section) {
		// Stores the sequence in one large string
		sequence += sequence_section;
	}
	cin >> word >> k;
	while(cin >> word) {
		if (word == "query") {
			cin >> error >> query;
			kmer = query.substr(0,k);
			// Query class stores the entire query, the error, and the indices 
			// at which the kmer is found 
			Query newQuery(query,error);
			// Kmers maps associates a kmer key with a value of a Query class
			kmers[kmer] = newQuery;
			// Finds and prints out the queries
			find_query(sequence,kmer,newQuery);
		} else if (word == "quit") {
			// Keyword to exit program
			return 0;
		}
	}
}
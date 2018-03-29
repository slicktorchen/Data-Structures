#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <cstring>
#include <vector>
#include <iterator>

#include "query.h"

using namespace std;

void find_query(string sequence, string kmer, Query query) {
	string search;
	unsigned int i,j,k;
	for (i = 0, k = kmer.size() +i; i < sequence.size()-kmer.size(); ++i) {
		search = sequence.substr(i,k);
		if (search == kmer) {
			query.addIndex(i);
		}
	}
	vector<int> indices = query.getIndices();
	int counter,num_found = 0;
	bool found;
	cout << "Query: " << query.getQuery() << endl;
	for (i = 0; i < indices.size(); ++i) {
		counter = 0;
		found = true;
		for (j = indices[i] + kmer.size(),k = kmer.size(); j < indices[i] + query.getQuery().size(),k < query.getQuery().size(); ++j,++k) {
			if (query.getQuery()[k] != sequence[j]) {
				++counter;
			}
			if (counter > query.getError()) {
				found = false;
				break;
			}
		}
		if (found) {
			cout << indices[i] << " " << counter << " " << sequence.substr(j-query.getQuery().size(),query.getQuery().size()) <<  endl;
			++num_found;
		}
	}
	if (num_found == 0) {
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
			kmers[kmer] = newQuery;
			find_query(sequence,kmer,newQuery);
		} else if (word == "quit") {
			return 0;
		}
	}
}

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <cstring>
#include <vector>
#include <iterator>

#include "query.h"

using namespace std;

// Finds and stores the locations of kmers in a vector of ints using maps
void find_kmer_indices(string kmer, string sequence, map<string,vector<int> > &kmers) {
	unsigned int i,k;
	string search;
	// Iterates through the entire sequence looking for a section that matches the kmer
	for (i = 0, k = kmer.size() +i; i < sequence.size()-kmer.size(); ++i) {
		search = sequence.substr(i,k);
		if (search == kmer) {
			kmers[kmer].push_back(i);
		}
	}
}

void find_query(string sequence, const vector<int> &indices, string query, string kmer, int error) {
	string search;
	unsigned int i,j,k;
	int counter,num_found = 0;
	bool found;
	cout << "Query: " << query << endl;
	for (i = 0; i < indices.size(); ++i) {
		counter = 0;
		found = true;
		for (j = indices[i] + kmer.size(),k = kmer.size(); j < indices[i] + query.size(),k < query.size(); ++j,++k) {
			if (query[k] != sequence[j]) {
				++counter;
			}
			if (counter > error) {
				found = false;
				break;
			}
		}
		if (found) {
			cout << indices[i] << " " << counter << " " << sequence.substr(j-query.size(),query.size()) <<  endl;
			++num_found;
		}
	}
	if (num_found == 0) {
		cout << "No Match" << endl;
	}
}

int main(int argc, char* argv[]) {
	int k,error;
	string word,sequence_section,sequence,query,kmer,filename;
	//map<string,Query> kmers;
	map<string,vector<int> > kmers;
	// Parses data
	cin >> word >> filename;
	fstream istr2(filename.c_str());
	if (!istr2.good()) {
		cerr << "Can't open " << argv[1] << " to read" << endl;
		return 1;
	}
	while (istr2 >> sequence_section) {
		sequence += sequence_section;
	}
	cin >> word >> k;
	while(cin >> word) {
		if (word == "query") {
			cin >> error >> query;
			kmer = query.substr(0,k);
			find_kmer_indices(kmer,sequence,kmers);
			map<string,vector<int> >::iterator map_itr;
			//for (int i = 0; i < kmers[kmer].size(); ++i) {
			//	cout << kmers[kmer][i] << endl;
			//}
			/*for (map_itr = kmers.begin(); map_itr != kmers.end(); ++map_itr) {
				for (int i = 0; i < map_itr->second.size(); ++i) {
					cout << map_itr->second[i] << endl;
				}
			}*/
			//Query newQuery(query,error);
			//kmers[kmer] = newQuery;
			find_query(sequence,kmers[kmer],query,kmer,error);
		} else if (word == "quit") {
			return 0;
		}
	}
}
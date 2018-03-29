#ifndef query_h_
#define query_h_

#include <string>
#include <vector>

using namespace std;

class Query {
public:
	Query(string query = "default", int error = 0) : query_(query), error_(error) {}
	const string getQuery() { return query_; }
	const int getError() { return error_; }
	const vector<int> getIndices() { return index_; }
	void addIndex(int index) {
		index_.push_back(index);
	}

private:
	string query_;
	vector<int> index_;
	int error_;
};


#endif
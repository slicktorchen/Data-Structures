#include <iostream>
#include <string>
#include <vector>
#include "tetris.h"

using namespace std;


int Tetris::remove_full_rows() {
	int i = 0, j, counter, row_removed = 2, number_rows_removed = 1;
	vector<int> rows_removed;
	char *temp;
	for (j = 0; j < heights[i]; ++j) {
		counter = 0;
		for (i = 0; i < width; ++i) {
			if (data[i][j] != ' ' ) {
				// Counts whether a row is full of blocks
				counter += 1;
			} else if (data[i][j] == ' ' || data[i][j] == 0) {
				break;
			}
			// Determines number of rows removed and which rows are removed
			if (counter == width-1) {
				row_removed = j;
				number_rows_removed += 1;
				rows_removed.push_back(j);
				break;
			}
		}
	}
	for (i = 0; i < width; ++i) {
		temp = new char[heights[i] - 1];
		for (j = 0; j < row_removed; ++j) {
			// Copies old array to new array
			temp[j] = data[i][j];
		}
		// Skips over the row that is deleted
		for (j = row_removed+1; j < heights[i]; ++j) {
			temp[j-1] = data[i][j];
		}
		delete [] data[i];
		data[i] = temp;
		heights[i] -= 1;
	}
	return number_rows_removed;
}

#include <iostream>
#include <string>
#include <vector>
#include "tetris.h"

using namespace std;

Tetris::Tetris(int width_) {
	width = width_;
	heights = new int[width]();
	data = new char*[width]();
}

void Tetris::add_piece(char character, int rotation, int x) {
	int max_height, i, j;
	char *temp;
	switch(character) {
	case 'I':
		if (rotation == 90 || rotation == 270) {
			max_height = get_max_height_columns(x,x+3);
			for (i = 0; i < 4; ++i) { 
				// Create four new arrays for new heights 
				// Increases height to max height +1
				temp = new char[max_height+1];

				for (j = 0; j < heights[x+i]; ++j) {
					// Copies old array to new array
					temp[j] = data[x+i][j];
				}
				for (j = heights[x+i]; j < max_height; ++j) {
					// Fills in spaces between old height and new height
					temp[j] = ' ';
				}
				// Sets the top with new character
				temp[max_height] = character;
				// Deletes old array and reassign data
				delete [] data[x+i];
				data[x+i] = temp;
				heights[x+i] = max_height + 1;
			}

		} else if (rotation == 180 || rotation == 0) {
			// Creates a new larger array increased by 4
			temp = new char[heights[x]+4];
			for (i = 0; i < heights[x]; ++i) {
				// Copies old array to new array
				temp[i] = data[x][i];
			}
			for (i = heights[x]; i < heights[x] + 4; ++i) {
				// Sets pieces in new array
				temp[i] = character;
			}
			// Deletes old array and reassigns data
			delete [] data[x];
			data[x] = temp;
			heights[x] += 4;
		}
		break;
	case 'O':
		max_height = get_max_height_columns(x,x+1);
		if (rotation%90 == 0) {
			for (i = 0; i < 2; ++i) {
				temp = new char[max_height + 2];
				for (j = 0; j < heights[x+i]; ++j) {
					temp[j] = data[x + i][j];
				}
				for (j = heights[x+i]; j < max_height; ++j) {
					temp[j] = ' ';
				}
				temp[max_height] = character;
				temp[max_height + 1] = character;
				delete [] data[x+i];
				data[x+i] = temp;
				heights[x+i] = max_height + 2;
			}
		}
		break;
	default:
		cout << "Not a valid piece" << endl;
		break;
	}

}


int Tetris::get_max_height_columns(int first,int last) const{
	int max, i;
	for (i = first + 1, max = heights[first]; i <= last;++i) {
		if (heights[i] > max) {
			max = heights[i];
		}
	}
	return max;
}

int Tetris::get_max_height() const {
	int max = 0, i;
	for (i = 0; i < width; ++i) {
		if (heights[i] > max) {
			max = heights[i];
		}
	}
	return max;
}

int Tetris::count_squares() const {
	int i, j, counter = 0;
	for (i = 0; i < width; ++i) {
		for (j = 0; j < heights[i]; ++j) {
			if (data[i][j] != ' ') {
				counter += 1;
			}
		}
	}
	return counter;
}

int Tetris::remove_full_rows() {
	int i = 0, j, row, count, row_removed, number_rows_removed = 0;
	int min_height = 100;
	vector<int> number_of_rows_removed;
	char *temp;
	// If any column is NULL nothing to be done
	for (i = 0; i < width-1; ++i ) {
		if (heights[i] < min_height) {
			min_height = heights[i];
		}
	}
	if (min_height == 0) {
		return 0;
	}
	for (j = 0; j < min_height; ++j) {
		count = 0;
		for (i = 0; i < width; ++i) {
			if (data[i][j] != ' ') {
				// Counts whether a row is full of blocks
				count += 1;
			} else if (data[i][j] == ' ') { //|| j >= heights[i]) {
				break;
			}
			// Determines number of rows removed and which rows are removed
			if (count == width) {
				row_removed = j;
				number_rows_removed += 1;
				number_of_rows_removed.push_back(j);
				break;
			}
		}
	}
	if (number_of_rows_removed.size() == 0) {
		return 0;
	}
	for (row = 0; row < number_of_rows_removed.size(); ++row) {
		for (i = 0; i < width; ++i) {
			if (heights[i] == 1) {
				delete data[i];
				data[i] = 0;
				heights[i] = 0;
				continue;
			}
			temp = new char[heights[i] - 1];
			for (j = 0; j < number_of_rows_removed[row]; ++j) {
				// Copies old array to new array
				temp[j] = data[i][j];
			}
			// Skips over the row that is deleted
			for (j = number_of_rows_removed[row]+1; j < heights[i]; ++j) {
				temp[j-1] = data[i][j];
			}
			delete [] data[i];
			data[i] = temp;
		
			heights[i] -= 1;
		}
	}
	for (i = 0; i < width; ++i) {
		int to_be_removed = 1, space_removed = 0;
		for (j = heights[i]; j >= 0; --j) {
			if (data[i][j] != ' ') {
				to_be_removed = 0;
			} else {
				space_removed += 1;
			}
		}
		if (space_removed == heights[i]) {
			delete [] data[i];
			data[i] = 0;
			heights[i] = 0;
		} else if (space_removed) {
			to_be_removed = 1;
		}
	}


	return number_rows_removed;
}

//void Tetris::add_left_column() {
//	int i;
//	char *ctemp;
//	int itemp;
//	for (i = 0; i < width; ++i) {
//		ctemp[i] = data[i+1];
//		heights[i] = heights[i+1];
//	}
//	delete data[width-1];
//	delete heights[width-1];
//}
//
//void Tetris::add_right_column() {
//
//}
//
//void Tetris::remove_left_column() {
//
//}
//
//void Tetris::remove_right_column() {
//
//}

void Tetris::destroy() {
	
	for (int i = 0; i < width; ++i) {
		delete [] data[i];
		
	}
	delete [] data;
	delete [] heights;
}
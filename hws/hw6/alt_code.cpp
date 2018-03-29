for (int i = std::max(current.getRow()-1, 0); i < std::min(int(board.size()), current.getRow()+2); ++i) {
		if (current.getSize() <= rows[i]) {
			for ( int j = current.getCols(); j < current.getCols() + current.getSize() ; ++j) {
				if (j == current.getCols()) {
					board[i][j] = '<';
				} else if (j == current.getCols() + current.getSize() -1) {
					board[i][j] = '>';
				}
				ship_num += 1;
				if (!place_ships(ships[ship_num])) {
					current.setOrient("vertical");
					break;
				}
			}
		}
		for (int j = std::max(ship.getCol()-1, 0); j < std::min(int(board[i].size()), ship.getCol()+2); ++j) {
			if (board[i][j] == word[path.size()]) {
				if (search_from_loc(loc(i,j), board, word, path))
					return true;
				}
		}
	}

//if (board[i][j] != 'X') {
			//	for (k = j + 1; k < j + current.getSize()-1; ++k) {
			//		// Checks if the ship fits 
			//		if (board[i][k] != 'X' || columns[k] < 1) {
			//			// Checks if the blocks are not occupied and fits vertically
			//			fits = false;
			//			break;
			//		} 
			//	}
			//}
for (k = j; k < j + current.getSize(); ++k) {
					// Marks locations as occupied
					board[i][k] = 'X';
					if (i > 1) {
						board[i-1][k] = 'Y';
					}
					if (i < board.size()) {
						board[i+1][k] = 'Y';
					}
					// Decrements num blocks occupied in column by 1
					--columns[k];
				}
// Tests ship locations vertically
	current.setOrient("vertical");
	for (j = 0; j < board[i].size(); ++j) {
		if (current.getSize() > columns[j]) {
			// Checks if the ship fits vertically
			continue;
		}
		for (i = 0; i < board.size() - current.getSize(); ++i) {
			bool fits = true;
			fits = check_spacing(current,board,rows,columns,i,j);
			if (fits) {
				// Subtracts num blocks occupied in row by size of ship
				columns[j] -= current.getSize();
				bool works = false;
				for (k = i; k < i + current.getSize(); ++k) {
					// Marks locations as occupied
					board[k][j] = 'X';
					// Decrements num blocks occupied in column by 1
					--rows[k];
					cout << 'X';
				}
				works = place_ships(ships,board,rows,columns,num_ships+1,find_all);
				if (works) {
					// If the rest of the ships are placed, set the current row and 
					// column as the location of the current ship
					current.setRow(i);
					current.setCol(j);
					return true;
				} else {
					remove_mark(current,board,rows,columns);
				}
			}
		}
	}


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <string.h>

#include "ship.h"

using namespace std;

bool check_spacing(Ship ship, const vector<string> &board, const vector<int> &rows, const vector<int> &columns, int row, int col, bool vertical = false) {
	if (vertical) {
		if (columns[col] < ship.getSize()) {
			// Checks if ship fits in the column
			return false;
		}
		for (int i = row; i < row + ship.getSize(); ++i) {
			// Checks if ship fits in the rows
			if ( rows[i] < 1) {
				return false;
			}
		}
		// Checks spacing between other ships
		for (int i = (row < 1)? 0:row-1; i < row + ship.getSize() && i < board.size(); ++i) {
			for (int j = (col < 1)? 0:col-1; j < col+1 && j < board[i].size(); ++j) {
				if (board[i][j] == 'X' || board[i][j] == 'Y') {
					// checks if blocks are not occupied and fits horizontally
					return false;
				}
			}
		}
	} else {
		//cout << "H Row: " << row << " Col: " << col << endl;
		if (rows[row] < ship.getSize()) {
			// Checks if ship fits in the row
			//cout << "Row: " << row << " rows[row]: " << rows[row] <<
			//	" ship.getSize(): " << ship.getSize() << endl; 
			return false;
		}
		for (int i = col; i < col + ship.getSize() && (unsigned int) i <= board.size() -2; ++i) {
			// Checks if ship fits in the columns
			if ( columns[i] < 1) {
				//cout << "Col: " << i << " columns[i]: " << columns[i] << endl;
				return false;
			}
		}
		// Checks spacing between other ships
		for (int i = (row < 1)? 0:row-1; i < row+1 && i < board.size(); ++i) {
			for (int j = (col < 1)? 0:col-1; j < col + ship.getSize() && j < board[i].size(); ++j) {
				if (board[i][j] == 'X' || board[i][j] == 'Y') {
					// checks if blocks are not occupied and fits horizontally
					return false;
				}
			}
		}
	}
	return true;
}

void remove_mark(Ship ship, vector<string> &board, vector<int> &rows, vector<int> &columns, int row,int col, bool vertical = false) {
	int i;
	if (vertical) {		
		// Spacing top of ship
		if (row > 0) {
			board[row-1][col] = ' ';
		}
		// Spacing bottom of ship
		if (row < board.size()-1) {
			board[row+1][col] = ' ';
		}
		for (i = row; i < row + ship.getSize(); ++i) {
			// Marks locations as unoccupied
			board[i][col] = ' ';
			++rows[i];
			++columns[col];
		}
	} else {
		// Horizontal
		// Spacing left of ship
		if (col > 0) {
			board[row][col-1] = ' ';
		}
		// Spacing right of ship
		if (col + ship.getSize() < board[1].size()) {
			board[row][col+1] = ' ';
		}
		for (i = col; i < col + ship.getSize(); ++i) {
			// Marks locations as unoccupied
			board[row][i] = ' ';
			++rows[row];
			++columns[i];
		}
	}
}

void add_mark(Ship ship,vector<string> &board, vector<int> &rows, vector<int> &columns, int row,int col, bool vertical = false) {
	int i;
	if (vertical) {		
		// Spacing top of ship
		if (row > 0) {
			board[row-1][col] = 'Y';
		}
		// Spacing bottom of ship
		if (row < board.size()-1) {
			board[row+1][col] = 'Y';
		}
		for (i = row; i < row + ship.getSize(); ++i) {
			// Marks locations as occupied
			board[i][col] = 'X';
			--rows[i];
			--columns[col];
		}
	} else {
		// Horizontal
		// Spacing left of ship
		if (col > 0) {
			board[row][col-1] = 'Y';
		}
		// Spacing right of ship
		if (col + ship.getSize() < board[0].size()) {
			board[row][col+1] = 'Y';
		}
		for (i = col; i < col + ship.getSize(); ++i) {
			// Marks locations as occupied
			board[row][i] = 'X';
			--rows[row];
			--columns[i];
		}
	}
}

void print_result(const vector<Ship> &ships) {
	for (unsigned int i = 0; i < ships.size(); ++i) {
		cout << ships[i].getName() << ": " << ships[i].getRow() << " " << ships[i].getCol();
		if (ships[i].getSize() > 1) {
			if (ships[i].getOrient() == "vertical") {
				cout << " vertical" ;
			} else {
				cout << " horizontal" ;
			}
		}
		cout << endl;
	}
}

bool place_ships(vector<Ship> &ships, vector<string> board, vector<int> rows, 
				 vector<int> columns, unsigned int num_ships, bool find_all = false) {
	
	if (num_ships == ships.size()) {
		return true;
	} 
	Ship* current = &ships[num_ships];
	//cout << current->getName() << " number ships: " << num_ships << endl;
	unsigned int i,j,k;
	// Tests ship locations horizontally
	for (i = 0; i < board.size(); ++i) {			
		for (j = 0; j < board[i].size() ; ++j) {
			bool fits, orient;

			for (k = 0, orient = true; k < 2 ; ++k, orient = false) {
				if (current->getSize() == 1 && k == 1) {
					continue;
				}
				if (!orient) {
					if (rows[i] < current->getSize()) {
						continue;
					}
				} else {
					if (columns[j] < current->getSize()) {
						continue;
					}
				}
				fits = check_spacing(*current,board,rows,columns,i,j,orient);
	
			/*	cout << "Fits: " << fits << " ship: " << current->getName() << " orient: " << orient << endl;
				cout << "j: " << j << " i: " << i << " board[i].size: " << board[i].size()
					<< " current: " << current->getSize() << endl;*/
				if (fits) {
					bool works = false;
					add_mark(*current,board,rows,columns,i,j,orient);
					//cout << "Recursion: " << current->getName() << " " << i << " " << j << endl;
					current->setRow(i);
					current->setCol(j);
					if (orient) {
						current->setOrient("vertical");
					} else {
						current->setOrient("horizontal");
					}
					works = place_ships(ships, board, rows, columns, num_ships+1,find_all);
					if (works){
						
						// If the rest of the ships are placed, set the current row and 
						// column as the location of the current ship

						if (num_ships == ships.size()-1) {
							print_result(ships);
						}
						if (!find_all) {
							return true;
						}
					} else {
						remove_mark(*current, board, rows,columns,i,j,orient);
					}
				} 
			}
		}
	}
	
	return false;
}


int main(int argc, char* argv[]) {
	ifstream istr(argv[1]);
	bool find_all = false;
	if (!istr.good()) {
		cerr << "Can't open " << argv[1] << " to read" << endl;
	}
	if (argc == 3 && strcmp(argv[2], "find_all_solutions") == 0) {
		find_all = true;
	}
	int board_rows, board_cols, row, col;
	vector<int> rows, columns;
	vector<string> board;
	vector<Ship> ships;
	string word;
	while (istr >> word) {
		// Parses info from input file
		if (word == "board") {
			istr >> board_rows >> board_cols;
		} else if (word == "rows") {
			for (int i = 0; i < board_rows; ++i) {
				istr >> row;
				rows.push_back(row);
			}
		} else if (word == "cols") {
			for (int i = 0; i < board_cols; ++i) {
				istr >> col; 
				columns.push_back(col);
			}
		} else {
			//cout << word << endl;
			Ship newShip(word);
			ships.push_back(newShip);
		}
	}
	// Sorts ships based on size
	//sort(ships.begin(),ships.end(),sort_size);
	// Creates a blank board with padding on four sides to make check_space easier
	for (int i = 0; i < board_rows; ++i) {
		string newline(board_cols, ' ');
		board.push_back(newline);
	}
	
	
	place_ships(ships,board,rows,columns,0,false);
	
	return 0;
}

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <string.h>

#include "ship.h"

using namespace std;

bool check_spacing(Ship ship, const vector<string> &board, const vector<int> &rows, const vector<int> &columns, int row, int col, bool vertical = false) {
	if (vertical) {
		if (columns[col] < ship.getSize()) {
			// Checks if ship fits in the column
			return false;
		}
		for (int i = row; i < row + ship.getSize(); ++i) {
			// Checks if ship fits in the rows
			if ( rows[i] < 1) {
				return false;
			}
		}
		// Checks if ship fits on board
		if ( row + ship.getSize() > board.size() ) {
			return false;
		}
		// Checks spacing between other ships
		for (int i = (row < 1)? 0:row-1; i < row + ship.getSize() && i < board.size(); ++i) {
			for (int j = (col < 1)? 0:col-1; j < col+1 && j < board[i].size(); ++j) {
				if (board[i][j] == 'X' || board[i][j] == 'Y') {
					// checks if blocks are not occupied and fits horizontally
					return false;
				}
			}
		}
	} else {
		// Horizontal
		//cout << "H Row: " << row << " Col: " << col << endl;
		if (rows[row] < ship.getSize()) {
			// Checks if ship fits in the row
			//cout << "Row: " << row << " rows[row]: " << rows[row] <<
			//	" ship.getSize(): " << ship.getSize() << endl; 
			return false;
		}
		for (int i = col; i < col + ship.getSize() && (unsigned int) i <= board.size() ; ++i) {
			// Checks if ship fits in the columns
			if ( columns[i] < 1) {
				//cout << "Col: " << i << " columns[i]: " << columns[i] << endl;
				return false;
			}
		}
		// Checks if ship fits on board
		if ( col + ship.getSize() > board[0].size() ) {
			return false;
		}
		// Checks spacing between other ships
		for (int i = (row < 1)? 0:row-1; i < row+1 && i < board.size(); ++i) {
			for (int j = (col < 1)? 0:col-1; j < col + ship.getSize() && j < board[i].size(); ++j) {
				if (board[i][j] == 'X' || board[i][j] == 'Y') {
					// checks if blocks are not occupied and fits horizontally
					return false;
				}
			}
		}
	}
	return true;
}

void remove_mark(Ship ship, vector<string> &board, vector<int> &rows, vector<int> &columns, int row,int col, bool vertical = false) {
	int i;
	if (vertical) {		
		// Spacing top of ship
		if (row > 0) {
			board[row-1][col] = ' ';
		}
		// Spacing bottom of ship
		if (row < board.size()-1) {
			board[row+1][col] = ' ';
		}
		for (i = row; i < row + ship.getSize(); ++i) {
			// Marks locations as unoccupied
			board[i][col] = ' ';
			++rows[i];
			++columns[col];
		}
	} else {
		// Horizontal
		// Spacing left of ship
		if (col > 0) {
			board[row][col-1] = ' ';
		}
		// Spacing right of ship
		if (col + ship.getSize() < board[1].size()) {
			board[row][col+1] = ' ';
		}
		for (i = col; i < col + ship.getSize(); ++i) {
			// Marks locations as unoccupied
			board[row][i] = ' ';
			++rows[row];
			++columns[i];
		}
	}
}

void add_mark(Ship ship,vector<string> &board, vector<int> &rows, vector<int> &columns, int row,int col, bool vertical = false) {
	int i;
	if (vertical) {		
		// Spacing top of ship
		if (row > 0) {
			board[row-1][col] = 'Y';
		}
		// Spacing bottom of ship
		if (row < board.size()-1) {
			board[row+1][col] = 'Y';
		}
		for (i = row; i < row + ship.getSize(); ++i) {
			// Marks locations as occupied
			board[i][col] = 'X';
			--rows[i];
			--columns[col];
		}
	} else {
		// Horizontal
		// Spacing left of ship
		if (col > 0) {
			board[row][col-1] = 'Y';
		}
		// Spacing right of ship
		if (col + ship.getSize() < board[0].size()) {
			board[row][col+1] = 'Y';
		}
		for (i = col; i < col + ship.getSize(); ++i) {
			// Marks locations as occupied
			board[row][i] = 'X';
			--rows[row];
			--columns[i];
		}
	}
}

void print_result(const vector<Ship> &ships, vector<string> board, const vector<int> &rows,) {
	for (unsigned int i = 0; i < ships.size(); ++i) {
		cout << ships[i].getName() << ": " << ships[i].getRow() << " " << ships[i].getCol();
		if (ships[i].getSize() > 1) {
			if (ships[i].getOrient() == "vertical") {
				cout << " vertical" ;
			} else {
				cout << " horizontal" ;
			}
		}
		cout << endl;
	}
}

bool place_ships(vector<Ship> &ships, vector<string> board, vector<int> rows, 
				 vector<int> columns, unsigned int num_ships, bool find_all = false) {
	
	if (num_ships == ships.size()) {
		return true;
	} 
	Ship* current = &ships[num_ships];
	//cout << current->getName() << " number ships: " << num_ships << endl;
	unsigned int i,j,k;
	// Tests ship locations horizontally
	for (i = 0; i < board.size(); ++i) {			
		for (j = 0; j < board[i].size() ; ++j) {
			bool fits, orient;

			for (k = 0, orient = true; k < 2 ; ++k, orient = false) {
				if (current->getSize() == 1 && k == 1) {
					continue;
				}
				if (!orient) {
					if (rows[i] < current->getSize()) {
						continue;
					}
				} else {
					if (columns[j] < current->getSize()) {
						continue;
					}
				}
				fits = check_spacing(*current,board,rows,columns,i,j,orient);
	
			/*	cout << "Fits: " << fits << " ship: " << current->getName() << " orient: " << orient << endl;
				cout << "j: " << j << " i: " << i << " board[i].size: " << board[i].size()
					<< " current: " << current->getSize() << endl;*/
				if (fits) {
					bool works = false;
					add_mark(*current,board,rows,columns,i,j,orient);
					//cout << "Recursion: " << current->getName() << " " << i << " " << j << endl;
					current->setRow(i);
					current->setCol(j);
					if (orient) {
						current->setOrient("vertical");
					} else {
						current->setOrient("horizontal");
					}
					works = place_ships(ships, board, rows, columns, num_ships+1,find_all);
					if (works){
						
						// If the rest of the ships are placed, set the current row and 
						// column as the location of the current ship

						if (num_ships == ships.size()-1) {
							print_result(ships);
						}
						if (!find_all) {
							return true;
						}
					} else {
						remove_mark(*current, board, rows,columns,i,j,orient);
					}
				} 
			}
		}
	}
	
	return false;
}
//string constraints(Ship ship, string &constr, int &row, int column) {
//	int i;
//	switch constr {
//	case ">":
//		if (ships[i].getSize() > 1 && column >= ships[i].getSize()) {
//			column -= ships[i].getSize();
//		}
//		return "<";
//	case "<":
//		break;
//	case "o":
//		break;
//	case "^":
//		break;
//	case "v":
//		if (ships[i].getSize() > 1 && row >= ships[i].getSize()) {
//			row -= ships[i].getSize();
//		}
//
//		return "^";
//	case "_":
//		break;
//	case "X":
//
//			if (ships[i].getSize() > 1 && 
//		}
//		break;
//	default:
//		break;
//	}
//}



int main(int argc, char* argv[]) {
	ifstream istr(argv[1]);
	bool find_all = false;
	if (!istr.good()) {
		cerr << "Can't open " << argv[1] << " to read" << endl;
	}
	if (argc == 3 && strcmp(argv[2], "find_all_solutions") == 0) {
		find_all = true;
	}
	int board_rows, board_cols, row, col, i;
	vector<int> rows, columns;
	vector<string> board;
	vector<Ship> ships, constraints;
	string word,constr;
	while (istr >> word) {
		// Parses info from input file
		if (word == "board") {
			istr >> board_rows >> board_cols;
		} else if (word == "rows") {
			for (i = 0; i < board_rows; ++i) {
				istr >> row;
				rows.push_back(row);
			}
		} else if (word == "cols") {
			for (i = 0; i < board_cols; ++i) {
				istr >> col; 
				columns.push_back(col);
			}
		} else if (word == "constraint") {
			istr >> row >> col >> constr;
		} else {
			//cout << word << endl;
			Ship newShip(word);
			ships.push_back(newShip);
		}
	}
	// Sorts ships based on size
	//sort(ships.begin(),ships.end(),sort_size);
	// Creates a blank board with padding on four sides to make check_space easier
	for (int i = 0; i < board_rows; ++i) {
		string newline(board_cols, ' ');
		board.push_back(newline);
	}
	
	//mark_board
	//board[row][col] == 'X';
	
	place_ships(ships,board,rows,columns,0,find_all);
	
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <string.h>

#include "ship.h"

using namespace std;

bool check_spacing(Ship ship, const vector<string> &board, const vector<int> &rows, const vector<int> &columns, int row, int col, bool &vertical) {
	if (vertical) {
		if (columns[col] < ship.getSize()) {
			// Checks if ship fits in the column
			return false;
		}
		for (int i = row; i < row + ship.getSize(); ++i) {
			// Checks if ship fits in the rows
			if ( rows[i] < 1) {
				return false;
			}
		}
		// Checks if ship fits on board
		if ( row + ship.getSize() > board.size() ) {
			return false;
		}
		// Checks spacing between other ships
		for (int i = (row < 1)? 0:row-1; i < row + ship.getSize() && i < board.size(); ++i) {
			for (int j = (col < 1)? 0:col-1; j < col+1 && j < board[i].size(); ++j) {
				if (board[i][j] == 'X' || board[i][j] == 'Y') {
					// checks if blocks are not occupied and fits horizontally
					return false;
				}
			}
		}
	} else {
		// Horizontal
		//cout << "H Row: " << row << " Col: " << col << endl;
		if (rows[row] < ship.getSize()) {
			// Checks if ship fits in the row
			//cout << "Row: " << row << " rows[row]: " << rows[row] <<
			//	" ship.getSize(): " << ship.getSize() << endl; 
			return false;
		}
		for (int i = col; i < col + ship.getSize() && (unsigned int) i <= board.size() ; ++i) {
			// Checks if ship fits in the columns
			if ( columns[i] < 1) {
				//cout << "Col: " << i << " columns[i]: " << columns[i] << endl;
				return false;
			}
		}
		// Checks if ship fits on board
		if ( col + ship.getSize() > board[0].size() ) {
			return false;
		}
		// Checks spacing between other ships
		for (int i = (row < 1)? 0:row-1; i < row+1 && i < board.size(); ++i) {
			for (int j = (col < 1)? 0:col-1; j < col + ship.getSize() && j < board[i].size(); ++j) {
				if (board[i][j] == 'X' || board[i][j] == 'Y') {
					// checks if blocks are not occupied and fits horizontally
					return false;
				}
			}
		}
	}
	return true;
}

void remove_mark(Ship ship, vector<string> &board, vector<int> &rows, vector<int> &columns, int row,int col, bool vertical = false) {
	int i;
	if (vertical) {		
		// Spacing top of ship
		if (row > 0) {
			board[row-1][col] = ' ';
		}
		// Spacing bottom of ship
		if (row < board.size()-1) {
			board[row+1][col] = ' ';
		}
		for (i = row; i < row + ship.getSize(); ++i) {
			// Marks locations as unoccupied
			board[i][col] = ' ';
			++rows[i];
			++columns[col];
		}
	} else {
		// Horizontal
		// Spacing left of ship
		if (col > 0) {
			board[row][col-1] = ' ';
		}
		// Spacing right of ship
		if (col + ship.getSize() < board[1].size()) {
			board[row][col+1] = ' ';
		}
		for (i = col; i < col + ship.getSize(); ++i) {
			// Marks locations as unoccupied
			board[row][i] = ' ';
			++rows[row];
			++columns[i];
		}
	}
}

void add_mark(Ship ship,vector<string> &board, vector<int> &rows, vector<int> &columns, int row,int col, bool vertical = false) {
	int i;
	if (vertical) {		
		// Spacing top of ship
		if (row > 0) {
			board[row-1][col] = 'Y';
		}
		// Spacing bottom of ship
		if (row < board.size()-1) {
			board[row+1][col] = 'Y';
		}
		for (i = row; i < row + ship.getSize(); ++i) {
			// Marks locations as occupied
			board[i][col] = 'X';
			--rows[i];
			--columns[col];
		}
	} else {
		// Horizontal
		// Spacing left of ship
		if (col > 0) {
			board[row][col-1] = 'Y';
		}
		// Spacing right of ship
		if (col + ship.getSize() < board[0].size()) {
			board[row][col+1] = 'Y';
		}
		for (i = col; i < col + ship.getSize(); ++i) {
			// Marks locations as occupied
			board[row][i] = 'X';
			--rows[row];
			--columns[i];
		}
	}
}

void print_result(const vector<Ship> &ships) {
	for (unsigned int i = 0; i < ships.size(); ++i) {
		cout << ships[i].getName() << ": " << ships[i].getRow() << " " << ships[i].getCol();
		if (ships[i].getSize() > 1) {
			if (ships[i].getOrient() == "vertical") {
				cout << " vertical" ;
			} else {
				cout << " horizontal" ;
			}
		}
		cout << endl;
	}
}

bool place_ship(Ship &ship, vector<string> &board, vector<int> rows, vector<int> columns) {
	unsigned int i,j,k;
	bool vert,fits;
	for (i = 0; i < board.size(); ++i) {
		for (j = 0; j < board[i].size(); ++j) {
			for (k = 0, vert = true; k < 2; ++k, vert = false) {
				if (ship.getSize() == 1 && k == 1) {
					continue;
				}
				if (!vert) {
					if (rows[i] < ship.getSize()) {
						continue;
					}
				} else {
					if (columns[j] < ship.getSize()) {
						continue;
					}
				}
				fits = check_spacing(ship,board,rows,columns,i,j,vert);
				if (fits) {
					ship.setRow(i);
					ship.setCol(j);
					if (vert) {
						ship.setOrient("vertical");
					} else {
						ship.setOrient("horizontal");
					}
					break;
				}
			}
		}
	}
	return fits;
}

bool find_solutions(vector<Ship> &ships, vector<string> &board, vector<int> rows, 
				 vector<int> columns, unsigned int num_ships, bool find_all = false) {
	bool works,placed,vert;
	Ship* current = &ships[num_ships];
	if (num_ships == ships.size()) {
		return true;
	}
	placed = place_ship(*current,board,rows,columns);
	if (current->getOrient() == "vertical") {
		vert = true;
	} else if (current->getOrient() == "horizontal") {
		vert = false;
	}
	if (placed) {
		add_mark(*current,board,rows,columns,current->getRow(),current->getCol(),vert);
		works = find_solutions(ships,board,rows,columns,num_ships+1,find_all);
		if (works) {
			if (num_ships == ships.size()-1) {
				print_result(ships);
			}
			if (!find_all) {
				return true;
			}
		} else {
			remove_mark(*current,board,rows,columns,current->getRow(),current->getCol(),vert);
			current->setRow(0);
			current->setCol(0);
			return false;
		}
	}
	return works;
}


//string constraints(Ship ship, string &constr, int &row, int column) {
//	int i;
//	switch constr {
//	case ">":
//		if (ships[i].getSize() > 1 && column >= ships[i].getSize()) {
//			column -= ships[i].getSize();
//		}
//		return "<";
//	case "<":
//		break;
//	case "o":
//		break;
//	case "^":
//		break;
//	case "v":
//		if (ships[i].getSize() > 1 && row >= ships[i].getSize()) {
//			row -= ships[i].getSize();
//		}
//
//		return "^";
//	case "_":
//		break;
//	case "X":
//
//			if (ships[i].getSize() > 1 && 
//		}
//		break;
//	default:
//		break;
//	}
//}



int main(int argc, char* argv[]) {
	ifstream istr(argv[1]);
	bool find_all = false;
	if (!istr.good()) {
		cerr << "Can't open " << argv[1] << " to read" << endl;
		return 1;
	}
	if (argc == 3 && strcmp(argv[2], "find_all_solutions") == 0) {
		find_all = true;
	}
	int board_rows, board_cols, row, col, i;
	vector<int> rows, columns;
	vector<string> board;
	vector<Ship> ships, constraints;
	string word,constr;
	while (istr >> word) {
		// Parses info from input file
		if (word == "board") {
			istr >> board_rows >> board_cols;
		} else if (word == "rows") {
			for (i = 0; i < board_rows; ++i) {
				istr >> row;
				rows.push_back(row);
			}
		} else if (word == "cols") {
			for (i = 0; i < board_cols; ++i) {
				istr >> col; 
				columns.push_back(col);
			}
		} else if (word == "constraint") {
			istr >> row >> col >> constr;
		} else {
			//cout << word << endl;
			Ship newShip(word);
			ships.push_back(newShip);
		}
	}
	// Sorts ships based on size
	//sort(ships.begin(),ships.end(),sort_size);
	// Creates a blank board with padding on four sides to make check_space easier
	for (int i = 0; i < board_rows; ++i) {
		string newline(board_cols, ' ');
		board.push_back(newline);
	}
	
	//mark_board
	//board[row][col] == 'X';
	
	find_solutions(ships,board,rows,columns,0,find_all);
	for (unsigned int i = 0; i < ships.size(); ++i) {
		cout << ships[i].getName() << ": " << ships[i].getRow() << " " << ships[i].getCol();
		if (ships[i].getSize() > 1) {
			if (ships[i].getOrient() == "vertical") {
				cout << " vertical" ;
			} else {
				cout << " horizontal" ;
			}
		}
		cout << endl;
	}
	for (unsigned int i = 0; i < board.size(); ++i) {
		cout << board[i] << endl;
	}


	return 0;
}
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <string.h>

#include "ship.h"

using namespace std;

//////////////////////////////// Checks if the ship can be placed at the current location //////////////////////////////////////////
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
		if (rows[row] < ship.getSize()) {
			// Checks if ship fits in the row
			return false;
		}
		for (int i = col; i < col + ship.getSize() && (unsigned int) i <= board.size() ; ++i) {
			// Checks if ship fits in the columns
			if ( columns[i] < 1) {
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

////////////////////// Removes a ship's marks on the board if the current recursion path fails //////////////////////////////////
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

//////////////////////////// Marks the board if a ship can be placed on the board //////////////////////////////////
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

////////////////////////////////////// Saves a solution /////////////////////////////////////////

void save_results(vector<Ship> ships, vector<vector<Ship> > &ship_results, vector<string> board, vector<vector<string> > &board_results) {
	unsigned int i,j;
	vector<string> newboard;
	// Creates a seperate board to edit and print
	for (i = 0; i < board.size(); ++i) {
		string newline(board[i].size(),' ');
		newboard.push_back(newline);
	}
	for (i = 0; i < ships.size(); ++i) {
		// Replaces corresponding characters at corresponding locations
		if (ships[i].getName() == "submarine") {
			newboard[ships[i].getRow()][ships[i].getCol()] = 'o';
			continue;
		}
		if (ships[i].getOrient() == "vertical") {
			// Marks the top of the ship
			newboard[ships[i].getRow()][ships[i].getCol()] = '^';
			if (ships[i].getSize() >= 3) {
				// If ship size is >= 3 fill in the middle with the character X
				for (j = ships[i].getRow()+1; j < ships[i].getRow() + ships[i].getSize()-1; ++j) {
					newboard[j][ships[i].getCol()] = 'X';
				}
			}
			// Marks the bottom of the ship
			newboard[ships[i].getRow()+ships[i].getSize()-1][ships[i].getCol()] = 'v';
		} else if (ships[i].getOrient() == "horizontal") {
			// Marks the left side of the ship
			newboard[ships[i].getRow()][ships[i].getCol()] = '<';
			if (ships[i].getSize() >= 3) {
				// If ship size is >= 3 fill in the middle with the character X
				for (j = ships[i].getCol()+1; j < ships[i].getCol() + ships[i].getSize()-1; ++j) {
					newboard[ships[i].getRow()][j] = 'X';
				}
			}
			// Marks the right side of the ship
			newboard[ships[i].getRow()][ships[i].getCol()+ships[i].getSize()-1] = '>';
		}
	}
	
	board_results.push_back(newboard);
	ship_results.push_back(ships);
}


////////////////////////////////////// Prints the solution /////////////////////////////////////////

void print_result(const vector<string> &board, vector<Ship> ships,const vector<Constraint> &constraints,int &solutions) {
	unsigned int i,j;
	sort(ships.begin(),ships.end(),sort_coord);
	
	// Checks if the ships fits within the given constraints otherwise the board is not printed
	for (i = 0; i < constraints.size(); ++i) {
		if (board[constraints[i].row_][constraints[i].col_] != constraints[i].constr_) {
			--solutions;
			return;
		}
	}

	// Prints out the solution
	cout << endl << "Solution: " << endl;
	for (i = 0; i < board.size(); ++i) {
		cout << ships[i].getName() << setw(12-ships[i].getName().size()) << ships[i].getRow() << " " << ships[i].getCol();
		if (ships[i].getSize() > 1) {
			if (ships[i].getOrient() == "vertical") {
				cout << " vertical" ;
			} else {
				cout << " horizontal" ;
			}
		}
		cout << endl; 
	}
	// Recalculates the initial rows and columns occupancy values
	vector<int> rows,columns;
	for (i = 0; i < board.size(); ++i) {
		int row = 0;
		for (j = 0; j < board[i].size(); ++j) {
			if (board[i][j] != ' ') {
				++row;
			}
		}
		rows.push_back(row);
	}
	for (j = 0; j < board[0].size(); ++j) {
		int col = 0;
		for (i = 0; i < board.size(); ++i) {
			if (board[i][j] != ' ') {
				++col;
			}
		}
		columns.push_back(col);
	}
	
	// Actual board is printed out
	string border(board[0].size(),'-');
	cout << "+" + border + "+" << endl;
	for (i = 0; i < board.size(); ++i) {
		cout << "|" + board[i] + "|" << rows[i] << endl;
	}
	cout << "+" + border + "+" << endl << " ";
	for (i = 0; i < board[0].size(); ++i) {
		cout << columns[i];
	}
	cout << endl;
}

// The recursive function that 
bool place_ships(vector<Ship> &ships, vector<string> board, vector<int> rows, 
				 vector<int> columns, unsigned int num_ships, bool find_all, 
				 vector<Constraint> constraints, vector<vector<Ship> > &ship_results,
				 vector<vector<string> > &board_results,int &solutions) {
	// The ending condition is when all the ships have been succesfully placed
	if (num_ships == ships.size()) {
		++solutions;
		return true;
	} 
	Ship* current = &ships[num_ships];
	unsigned int i,j,k;
	// Checks ship locations on all points of the board
	for (i = 0; i < board.size(); ++i) {			
		for (j = 0; j < board[i].size() ; ++j) {
			bool fits, vert;
			// At each point, check if the vertical or horizontal positions work
			for (k = 0, vert = true; k < 2 ; ++k, vert = false) {
				if (current->getSize() == 1 && k == 1) {
					// If the ship is a submarine, orientations doesn't matter
					continue;
				}
				if (!vert) {
					// If horizontal, check if the ship size is not larger 
					// than the allowed row occupancy
					if (rows[i] < current->getSize()) {
						continue;
					}
				} else {
					// If vertical, check if the ship size is not larger 
					// than the allowed column occupancy
					if (columns[j] < current->getSize()) {
						continue;
					}
				}
				// Checks if the ship fits in the current location and that there
				// are no ships adjacent to its location
				fits = check_spacing(*current,board,rows,columns,i,j,vert);
				if (fits) {
					bool works = false;
					// If the ship fits, mark the ship on the board at the corresponding locations
					add_mark(*current,board,rows,columns,i,j,vert);
					// Set the values of the ship
					current->setRow(i);
					current->setCol(j);
					if (vert) {
						current->setOrient("vertical");
					} else {
						current->setOrient("horizontal");
					}
					// The function calls itself until all of the ships have been placed
					works = place_ships(ships, board, rows, columns, num_ships+1,find_all,constraints,ship_results,board_results,solutions);
					if (works){
						if (num_ships == ships.size()-1) {
							// Print the results of the current solution found
							save_results(ships,ship_results,board,board_results);
						} 
						if (!find_all) {
							return true;
						} 
					} else {
						// If the recursive function fails, remove the current ship from the board
						remove_mark(*current, board, rows,columns,i,j,vert);
					}
				} 
			}
		}
	}
	
	return false;
}

//////////////////////////////////////// MAIN //////////////////////////////////////////////////
int main(int argc, char* argv[]) {
	ifstream istr(argv[1]);
	int board_rows, board_cols, row, col, i;
	vector<int> rows, columns;
	vector<string> board;
	vector<Ship> ships;
	vector<Constraint> constraints; 
	string word;
	char constr;
	vector<vector<string> > board_results;
	vector<vector<Ship> > ship_results;
	bool find_all = false;
	if (!istr.good()) {
		cerr << "Can't open " << argv[1] << " to read" << endl;
	}
	if (argc == 3 && strcmp(argv[2], "find_all_solutions") == 0) {
		find_all = true;
	}

	while (istr >> word) {
		// Parses info from input file
		if (word == "board") {
			istr >> board_rows >> board_cols;
		} else if (word == "rows") {
			// Stores the rows occupancy
			for (i = 0; i < board_rows; ++i) {
				istr >> row;
				rows.push_back(row);
			}
		} else if (word == "cols") {
			// Stores the columns occupancy
			for (i = 0; i < board_cols; ++i) {
				istr >> col; 
				columns.push_back(col);
			}
		} else if (word == "constraint") {
			// Stores the constraints
			istr >> row >> col >> constr;
			Constraint constraint(constr,row,col);
			constraints.push_back(constraint);
		} else {
			// Saves the ships in a vector of ships
			Ship newShip(word);
			ships.push_back(newShip);
		}
	}
	// Creates a blank board with padding on four sides to make check_space easier
	for (int i = 0; i < board_rows; ++i) {
		string newline(board_cols, ' ');
		board.push_back(newline);
	}
	// If there exists any constraints, all solutions should be considered
	if (constraints.size() > 0) {
		find_all = true;
	}
	// Used to count solutions
	int solutions = 0;
	
	// Finds the solutions
	place_ships(ships,board,rows,columns,0,find_all,constraints,ship_results, board_results,solutions);	
	bool same;
	for (i = 0; i < ship_results.size(); ++i) {
		same = false;
		if (board_results[i] == board_results[i+1]) {
			same = true;
		}
		if (!same) {
			print_result(board_results[i],ship_results[i],constraints,solutions);
		} else {
			--solutions;
		}
	}

	if (find_all) {
		cout << endl << "Found " <<  solutions << " solution(s)" ;
	}

	return 0;
}
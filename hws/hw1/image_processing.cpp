#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
using namespace std;

/* Note: in each of the functions, "image" is a vector of strings from the input txt file and "new_image"
   is a vector of strings of the same dimensions except without any special characters. "new_image" is the 
   vector that will be edited. */

/* Replace Function: takes two char inputs and two vector inputs. Identifies the character being replaced
   from the original image (in the form of a string of vectors) and returns a new image with the replaced character. */

vector<string> replace(char old_val, char new_val, vector<string> image, vector<string> new_image) {
	for (unsigned int i = 0; i < image.size(); ++i) {
		for (unsigned int j = 0; j < image[i].size(); ++j) {
			if (image[i][j] == old_val) {
				new_image[i][j] = new_val;
			}
		}
	}
	return new_image;
}

/* Erosion Function: takes one character input and two vector inputs. Checks each pixel in the original image.
   If a character pixel is surrounded by 4 characters, the character pixel is NOT eroded and is saved into the "new_image". 
   Otherwise, if a character pixel is surrounded by fewer than 4 characters, then the character pixel IS eroded. 
   The function returns the resulting image in vector form. */

vector<string> erosion(char val, vector<string> image, vector<string> new_image) {
	for (unsigned int i = 0; i < image.size(); ++i) {
		for (unsigned int j = 0; j < image[i].size(); ++j) {
			if (image[i][j] == val) {
				if (image[i+1][j] == val && image[i-1][j] == val && image[i][j+1] == val && image[i][j-1] == val) {
					new_image[i][j] = val;
				} else if (image[i+1][j] == val || image[i-1][j] == val || image[i][j+1] == val || image[i][j-1] == val) {
					new_image[i][j] = '.';
				}
			}
		}
	}
	return new_image;
}

/* Dilation Function: takes one char input and two vector inputs. Checks each pixel in the original image.
   If a background pixel is surrounded by at least 1 character pixel, that background pixel turns into the character pixel.
   There is extensive boundary checking to avoid segmentation error.
*/

vector<string> dilation(char val, vector<string> image, vector<string> new_image) {
	new_image = image;
	for (unsigned int i = 0; i < image.size(); ++i) {
		for (unsigned int j = 0; j < image[i].size(); ++j) {
			/// Covers the corner cases
			if (i == 0 && j == 0) {
				if (image[i+1][j] == val || image[i][j+1] == val) {
					new_image[i][j] = val;
				}
			} else if (i == 0 && j == image[i].size() -1) {
				if (image[i+1][j] == val || image[i][j-1] == val) {
					new_image[i][j] = val;
				}
			} else if (i == image.size() -1 && j == 0) {
				if (image[i-1][j] == val || image[i][j+1] == val) {
					new_image[i][j] = val;
				}
			} else if (i == image.size() -1 && j == image[i].size()) {
				if (image[i-1][j] == val || image[i][j-1] == val) {
					new_image[i][j] = val;
				}
			////// Covers the edge cases
			} else if (i == 0) {
				if (image[i+1][j] == val || image[i][j+1] == val || image[i][j-1] == val) {
					new_image[i][j] = val;
				}
			} else if (i == image.size() -1) {
				if (image[i-1][j] == val || image[i][j+1] == val || image[i][j-1] == val) {
					new_image[i][j] = val;
				}
			} else if (j == 0) {
				if (image[i+1][j] == val || image[i-1][j] == val || image[i][j+1] == val) {
					new_image[i][j] = val;
				}
			} else if ( j == image[i].size() -1) {
				if (image[i+1][j] == val || image[i-1][j] == val || image[i][j-1] == val) {
					new_image[i][j] = val;
				}
			////// After all the boundary checks, the rest of the pixels can be checked safely
			} else {
				if (image[i+1][j] == val || image[i-1][j] == val || image[i][j+1] == val || image[i][j-1] == val) {
					new_image[i][j] = val;
				}
			}
		}
	}
	return new_image;
}

/* Floodfill Function: takes two char* inputs each representing respective coordinate points in the image, one char input,
   and two vector of strings. The char* inputs are converted to integers and set to the values "row" and "column". All special
   characters in rows and columns greater or equal to the row and column input are converted to the specified new character. */
vector<string> floodfill (unsigned int row, unsigned int column, char val, vector<string> image, vector<string> new_image) {

	bool finished = false;
	bool sweep_down = false;
	unsigned int column_up = column,row_down = row,column_down = column;
	new_image = image;
	//while (image[row][column] == val) {
	if (image[row][column] != val) {
		new_image[row][column] = val;
		char old_val = image[row][column];
		cout << old_val;
		while(!sweep_down) {
			while(!finished) {
				cout << "COLUMN: " << column_up << " ROW: " << row_down << endl;
				if (image[row_down][column_up] == old_val) {
					new_image[row_down][column_up] = val;
					column_up += 1;
				} else {
					row_down += 1;
					column_up -= 1;
					cout << "COLUMN: " << column_up << " ROW: " << row_down << endl;
					finished = true;
				}
			}
			finished = false;
			column_down = column_up;
			while(!finished) {
				cout << "COLUMN: " << column_down << " ROW: " << row_down << endl;
				if (image[row_down][column_down] == old_val) {
					new_image[row_down][column_down] = val;
					column_down -= 1;
				} else {
					
					row_down += 1;
					column_down += 1;
					cout << "COLUMN: " << column_down << " ROW: " << row_down << endl;
					finished = true;
				}
			}
			finished = false;
			column_up = column_down;
			if (image[row_down][column_down] != old_val) {
				sweep_down = true;
			}
		}
	}
	return new_image;
}


	/*for (unsigned int i = 0; i < image.size(); ++i) {
		for (unsigned int j = 0; j < image[i].size(); ++j) {
			if (i >= row && j >= column && image[i][j] != val && image[i][j] != '.') {
				new_image[i][j] = val;
			} else {
				new_image[i][j] = image[i][j];
			}
		}
	}*/
	//return new_image;


int main(int argc, char* argv[]) 
{
	string function = argv[3];
	string input;
	string output;
	ifstream in_str(argv[1]);
	ofstream out_str(argv[2]);
	if (!in_str.good()) {
		cerr << "Can't open " << argv[1] << " to read." << endl;
		return 1;
	} if (!out_str.good()) {
		cerr << "Can't open " << argv[2] << " to write." << endl;
		return 1;
	}
	vector<string> image;
	vector<string> new_image;

	while (in_str >> input) {
		image.push_back(input);
	}
	for (unsigned int lines = 0; lines < image.size(); ++lines) {
		new_image.push_back(string(image[lines].size(),'.'));
	}
	
	if (function == "replace") {
		new_image = replace(*argv[4],*argv[5],image,new_image);
	} else if (function == "erosion") {
		new_image = erosion(*argv[4],image,new_image);
	} else if (function == "dilation") {
		new_image = dilation(*argv[4],image,new_image);
	} else if (function == "floodfill") {
		unsigned int row = atoi(argv[4]);
		unsigned int column = atoi(argv[5]);
		new_image = floodfill(row,column,*argv[6],image,new_image);
	}


	for (unsigned int j = 0; j < new_image.size(); ++j) {
		//cout << new_image[j] << endl;
		out_str << new_image[j] << endl;
	}
}
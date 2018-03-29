#ifndef __tetris_h_
#define __tetris_h_

class Tetris {

public:
	Tetris(int width_ = 6);

	int get_width() const { return width; }
	int get_max_height() const;
	int count_squares() const;
	int remove_full_rows();

	void add_left_column();
	void add_right_column();
	void remove_left_column();
	void remove_right_column();
	void add_piece(char character, int rotation, int x);
	void destroy();
	void print() const;

private:
	int get_max_height_columns(int first,int length) const;
	int width;
	int *heights;
	char** data; //data[x][y]  data[width][height]


};


#endif
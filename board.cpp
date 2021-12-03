#include "board.hpp"

Cell::Cell(bool mine) {
	if (mine)
		mine_count = BOMB;
	is_visible = false;
}

bool Cell::IsMine() {
	return mine_count == BOMB;
}

char Cell::Symbol() {
	return mine_count;
}

bool Cell::IsVisible() {
	return is_visible;
}

void Cell::MakeVisible() {
	is_visible = true;
}

/*
8|8
-+-
8|8
*/
Board::Board(int screen_width, int screen_height, float percent_mines) {
	int width = (screen_width - 2) / 2 + 1;
	int height = (screen_height - 2) / 2 + 1;
	board.resize(height);
	for (auto & r : board)
		r.resize(width);
}

#include "board.hpp"

using namespace std;

Cell::Cell() {
	is_visible = false;
	mine_count = ' ';
}

bool Cell::IsMine() {
	return mine_count == BOMB;
}

const char & Cell::GetSymbol() const {
	return mine_count;
}

bool Cell::IsVisible() {
	return is_visible;
}

void Cell::MakeVisible() {
	is_visible = true;
}

void Cell::SetSymbol(const int & count) {
	assert(count >= 0 && count <= 9);
	mine_count = count + '0';
}

void Cell::MakeMine() {
	mine_count = BOMB;
}

float Board::frand() {
	return (float) rand() / (float) RAND_MAX;
}

int Board::Probe(const int x, const int y) {
	int retval = 0;
	if (x >= 0 and x < width and y >= 0 and y < height) {
		if (board[y][x].IsMine())
			retval = 1;
	}
	return retval;
}

void Board::Render() {
	for (auto & r : board) {
		stringstream ss;
	}
}
/*
8|8
-+-
8|8
*/
Board::Board(int screen_width, int screen_height, float percent_mines) {
	width = (screen_width - 2) / 2 + 1;
	height = (screen_height - 2) / 2 + 1;
	board.resize(height);
	for (auto & r : board) {
		r.resize(width);
		for (auto & c : r) {
			if (frand() <= percent_mines)
				c.MakeMine();
		}
	}
	int bomb_count = 0;
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++, bomb_count = 0) {
			if (board[y][x].IsMine())
				continue;
			for (int dy = -1; dy <= 1; dy++)
				for (int dx = -1; dx <= 1; dx++)
					bomb_count += Probe(x + dx, y + dy);
			board[y][x].SetSymbol(bomb_count);
		}
	}
}

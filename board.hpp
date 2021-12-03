#pragma once
#include <vector>

struct Cell {
	Cell(bool mine = false);
	bool IsMine();
	char Symbol();
	bool IsVisible();
	void MakeVisible();

private:
	char mine_count;
	bool is_visible;

	static const char BOMB = '*';
};

using BOARD = std::vector<std::vector<Cell>>;

struct Board {
	Board(int screen_width, int screen_height, float percent_mines);

private:
	BOARD board;
};

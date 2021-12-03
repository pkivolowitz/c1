#pragma once
#include <cassert>
#include <sstream>
#include <vector>

struct Cell {
	Cell();
	bool IsMine();
	const char & GetSymbol() const;
	bool IsVisible();
	void MakeVisible();
	void SetSymbol(const int & count);
	void MakeMine();

private:
	char mine_count;
	bool is_visible;

	static const char BOMB = '*';
};

using BOARD = std::vector<std::vector<Cell>>;

struct Board {
	Board(int screen_width, int screen_height, float percent_mines);
	void Render();
	float frand();

private:
	BOARD board;
	int Probe(const int x, const int y);
	int width;
	int height;
};

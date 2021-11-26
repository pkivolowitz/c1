#include "curses_setup.hpp"

using namespace std;

static mutex m;

void BeginUpdate() {
	lock_guard<mutex> l(m);
	erase();
}	
	
void InitCurses() {
	extern WINDOW *main_window;

	main_window = initscr();
	cbreak();
	noecho();
	nonl();
	intrflush(stdscr, FALSE);
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
	curs_set(0);
}

void TakedownCurses() {
	curs_set(1);
	nodelay(stdscr, FALSE);
	keypad(stdscr, FALSE);
	intrflush(stdscr, TRUE);
	nl();
	echo();
	nocbreak();
	endwin();
}

void Refresh(void (*CustomBorder)()) {
	extern WINDOW *main_window;
	lock_guard<mutex> l(m);
	ostringstream ss;

	auto t = std::time(nullptr);
	auto tm = *std::localtime(&t);

	ss << put_time(&tm, " %H:%M:%S ");
	box(main_window, 0, 0);
	mvaddstr(0, COLS - 12, ss.str().c_str());

	if (CustomBorder) {
		CustomBorder();
	}
	refresh();
}

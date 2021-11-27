#include "curses_setup.hpp"

using namespace std;

static mutex m;

void BeginUpdate() {
	lock_guard<mutex> l(m);
	erase();
}

/*	This function initializes the curses library and defines its operating state.
	Specifically, this includes setting up a non-blocking, non-echoing immediate
	mode.
*/
WINDOW * InitCurses() {
	WINDOW * main_window = initscr();
	if (main_window) {
		cbreak();
		noecho();
		nonl();
		intrflush(stdscr, FALSE);
		keypad(stdscr, TRUE);
		nodelay(stdscr, TRUE);
		curs_set(0);
	}
	return main_window;
}

/*	This function will only be called if curses successfully initialized.
*/
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

string GetTime() { 
	ostringstream ss;
	auto t = std::time(nullptr);
	auto tm = *std::localtime(&t);

	ss << put_time(&tm, " %H:%M:%S ");
	return ss.str();
}

void Refresh(WINDOW * main_window, void (*CustomBorder)()) {
	lock_guard<mutex> l(m);
	box(main_window, 0, 0);
	mvwaddstr(main_window, 0, COLS - 12, GetTime().c_str());
	if (CustomBorder) {
		CustomBorder();
	}
	wrefresh(main_window);
}

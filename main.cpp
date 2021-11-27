#include <ncurses.h>

#include <iostream>

#include "curses_setup.hpp"
#include "signal_handling.hpp"

using namespace std;

WINDOW* main_window = nullptr;
struct sigaction sigIntHandler;
bool keep_going = true;

enum ACTION {
	ACTION_NONE,
	ACTION_QUIT,
	ACTION_TEST1,
	ACTION_TEST2,
	ACTION_TIME,
	ACTION_ABOUT
};

ACTION GetCH() {
	int c;
	ACTION action = ACTION_NONE;
	if ((c = getch()) != ERR) {
		switch (c) {
			case 'q':
			case 'Q':
				action = ACTION_QUIT;
				break;

			case KEY_F(1):
				action = ACTION_TEST1;
				break;

			case KEY_F(2):
				action = ACTION_TEST2;
				break;
		}
	}
	return action;
}

void MainLoop() {
	static string previous_time_string;

	while (keep_going) {
		string current_time_string = GetTime();
		ACTION action;

		action = (previous_time_string != current_time_string) ? ACTION_TIME : GetCH();
		previous_time_string = current_time_string;

		// If ACTION_QUIT - leave the main loop.
		if (action == ACTION_QUIT) {
			break;
		}

		switch (action) {
			default:
				// A default case is useful when switching on an enum as
				// without  one, a warning is generated if any cases are
				// ommitted.
				break;

			case ACTION_TEST2:
				mvaddch(10, 10, ' ');
				break;

			case ACTION_TEST1:
				mvaddch(10, 10, '*');
				break;
		}

		if (action != ACTION_NONE) {
			Refresh();
		}

		this_thread::sleep_for(chrono::milliseconds(100));
	}
}

int main(int argc, char** argv) {
	InitCurses();
	SetSignalHandlers(sigIntHandler);
	Refresh();

	MainLoop();

	TakedownCurses();
	cerr << "Normal shutdown.\n";
	return 0;
}

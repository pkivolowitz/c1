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
	ACTION_TEST,
	ACTION_ABOUT
};

void MainLoop() {
	while (keep_going) {
		int c;
		ACTION action = ACTION_NONE;

		// getch() causes a refresh. This interferes with the erase() in
		// BeginUpdate().  Therefore, all screen updates begin after the
		// processing of keyboard events.
		if ((c = getch()) != ERR) {
			switch (c) {
				case 'q':
				case 'Q':
					action = ACTION_QUIT;
					break;

				case KEY_F(12):
					action = ACTION_TEST;
					break;
			}
		}

		// If ACTION_QUIT - leave the main loop.
		if (action == ACTION_QUIT) {
			break;
		}

		// If NOT ACTION_NONE, begin a screen update.
		if (action != ACTION_NONE) {
			BeginUpdate();
		}

		switch (action) {
			case ACTION_ABOUT:
			case ACTION_QUIT:
			case ACTION_NONE:
				// NOP.
				break;

			case ACTION_TEST:
				mvaddch(10, 10, '*');
				break;
		}

		// If NOT ACTION_NONE, complete the screen update.
		if (action != ACTION_NONE) {
			Refresh();
		}

		// Our continuous monitoring of the keyboard causes us to
		// hog the processor. Calling yield() is a minor kindness
		// to others.
		this_thread::yield();
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

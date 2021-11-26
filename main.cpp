#include <ncurses.h>

#include <iostream>

#include "curses_setup.hpp"
#include "signal_handling.hpp"

using namespace std;

WINDOW* main_window = nullptr;
struct sigaction sigIntHandler;
bool keep_going = true;

void MainLoop() {
	while (keep_going) {
		int c;

		// getch() causes a refresh. This interferes with the erase() in
		// BeginUpdate().  Therefore, all screen updates begin after the
		// processing of keyboard events.
		if ((c = getch()) != ERR) {
			switch (c) {
				case 'q':
				case 'Q':
					keep_going = false;
					break;
			}
		}

		if (keep_going) {
			BeginUpdate();
			Refresh();
			// Our continuous monitoring of the keyboard causes us to
			// hog the processor. Calling yield() is a minor kindness
			// to others.
			this_thread::yield();
		}
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

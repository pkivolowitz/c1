#include <iostream>

#include "actions.hpp"
#include "board.hpp"
#include "curses_setup.hpp"
#include "signal_handling.hpp"

using namespace std;

bool keep_going = true;			// externally visible in signal_handling.cpp, for example.

static WINDOW* main_window = nullptr;
static struct sigaction sigIntHandler;
static const auto SLEEP_PERIOD = chrono::milliseconds(100);

void MainLoop(Board & board) {
	static string previous_time_string;
	MEVENT mouse_event;

	while (keep_going) {
		string current_time_string = GetTime();
		ACTION action;

		action = (previous_time_string != current_time_string) ? ACTION_TIME : GetCH(mouse_event);
		previous_time_string = current_time_string;

		// If ACTION_QUIT - leave the main loop.
		if (action == ACTION_QUIT) {
			break;
		}

		if (action != ACTION_NONE) {
			clear();
		}
		switch (action) {
			default:
				// A default case is useful when switching on an enum as
				// without  one, a warning is generated if any cases are
				// ommitted.
				break;

			case ACTION_TEST2:
				mvaddch(10, 10, ACS_LRCORNER);		
				break;

			case ACTION_TEST1:
				mvaddch(10, 10, '*');
				break;

			case ACTION_MOUSEUP:
				stringstream ss;
				ss << "Mouse up: " << mouse_event.x << ", " << mouse_event.y << ", " << mouse_event.z;
				mvaddstr(10, 10, ss.str().c_str());
				break;
		}

		if (action != ACTION_NONE) {

			Refresh(main_window);
		}

		this_thread::sleep_for(SLEEP_PERIOD);
	}
}

int main(int argc __attribute__((unused)), char ** argv __attribute__((unused))) {
	if ((main_window = InitCurses())) {
		Board board(COLS, LINES, 0.1);
		SetSignalHandlers(sigIntHandler);
		MainLoop(board);
		TakedownCurses();
		cerr << "Normal shutdown.\n";
	}
	else {
		cerr << "curses failed to initialize.\n";
	}
	return 0;
}

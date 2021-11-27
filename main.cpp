#include <iostream>

#include "actions.hpp"
#include "curses_setup.hpp"
#include "signal_handling.hpp"

using namespace std;

bool keep_going = true;			// externally visible
WINDOW* main_window = nullptr;	// externally visible
struct sigaction sigIntHandler; // externally visible

static const auto SLEEP_PERIOD = chrono::milliseconds(100);

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

		this_thread::sleep_for(SLEEP_PERIOD);
	}
}

int main(int argc __attribute__((unused)), char ** argv __attribute__((unused))) {
	InitCurses();
	SetSignalHandlers(sigIntHandler);

	MainLoop();

	TakedownCurses();
	cerr << "Normal shutdown.\n";
	return 0;
}

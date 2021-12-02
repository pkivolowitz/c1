#include "actions.hpp"
#include <iostream>
#include <ncurses.h>
#include <sstream>

using namespace std;

/*	This  function translates key codes  (if present)  to ACTION enum
	values.  If no key code is available, the program does NOT block.
	Rather, ACTION_NONE is returned.

	If the action is found to be mouse related, mouse_event is filled
	in and returned. Note that any other action, clears mouse_event.
*/
ACTION GetCH(MEVENT & mouse_event) {
	int c;

	memset(&mouse_event, 0, sizeof(MEVENT));
	ACTION action = ACTION_NONE;
	if ((c = getch()) != ERR) {
		switch (c) {
			case KEY_MOUSE:
				if ((getmouse(&mouse_event) == OK) && (mouse_event.bstate & BUTTON1_RELEASED)) {
					action = ACTION_MOUSEUP;
				}
				break;

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

#include "actions.hpp"

/*	This function translates key codes  (if present)  to ACTION enum
	values. If no key code is available, the program does NOT block.
	Rather, ACTION_NONE is returned.
*/
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

# Unknown Curses Program

As of this writing, I have no idea what this program is going to do. But it is looking good so far!

## Non-blocking I/O used

This program sets `ncurses` up to avoid blocking on I/O. 

* The upside of this is that the program
*can* continue running at all times.

* The downside of this is that the program *will* continue running at all times.

Consequently, the main loop calls the OS `yield()` function as a courtesy.

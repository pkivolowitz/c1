# Unknown Curses Program

As of this writing, I have no idea what this program is going to do. But it is looking good so far!

Will this be a game? Will it be a utility? No idea.

## Non-blocking I/O

This program sets `ncurses` up to avoid blocking on I/O.

* The upside of this is that the program
*can* continue running at all times.

* The downside of this is that the program *will* continue running at all times.

Consequently, the main loop calls the  `sleep_for()` function to sleep for 100 milliseconds as a courtesy.

Programs which use ncurses in this way have the potential to leave the user's terminal in an unusable state (typically solved with `stty sane`). To ward this sort of problem away, the program catches `SIGINT` to properly shutdown.

## Keyboard controls

| Key | Function |
| --- | -------- |
| q \| Q | Terminates the program

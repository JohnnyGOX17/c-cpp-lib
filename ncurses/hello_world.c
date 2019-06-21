#include <ncurses.h>

int main()
{
	initscr();			/* Start curses mode */
	printw("Hello World !!!");	/* Print message to buffer */
	refresh();			/* Print buffer on real screen */
	getch();			/* Wait for user input */
	endwin();			/* End curses mode */

	return 0;
}

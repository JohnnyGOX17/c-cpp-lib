#include <ncurses.h>

int main()
{
	int ch;

	initscr();
	raw();			/* disable line buffering	*/
	keypad(stdscr, TRUE);	/* Get function & arrow keys	*/
	noecho();		/* don't echo user input	*/

	printw("Type any character to see it in bold\n");
	ch = getch();		/* If raw() not called, user would
				 * have to press enter before it
				 * gets to the program		*/
	if(ch == KEY_F(1)) {
		printw("F1 Key pressed");
	}
	else {
		printw("The key pressed  is: ");
		attron(A_BOLD);
		printw("%c", ch);
		attroff(A_BOLD);
	}

	refresh();
	getch();		/* wait for user input		*/
	endwin();

	return 0;
}

#include <stdio.h>

int main(void)
{
	int c;
	/* inner parentheses are needed since comparison operator takes
	 * precedence over assignment operator */
	while ((c = getchar()) != EOF)
		putchar(c);
	return 0;
}

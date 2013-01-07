#include <stdio.h>

void main()
{
	int c, blanks, tabs, nl;

	blanks = tabs = nl = 0;

	while ((c = getchar()) != EOF) {
		if (c == ' ')
			++blanks;
		else if (c == '\t')
			++tabs;
		else if (c == '\n')
			nl++;
	}

	printf ("blanks: %d, tabs: %d, newlines: %d\n", blanks, tabs, nl);
}

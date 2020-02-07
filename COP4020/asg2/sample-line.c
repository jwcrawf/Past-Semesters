static char *sccsid = "@(#)echo.c	4.1 (Berkeley) 10/1/80";
#include <stdio.h>

main(argc, argv)
int argc;
char *argv[];
{
        // this is the line comment
	register int i, nflg;

        /* That is the block comment. This should not be considered as
           a block for the ident */
	nflg = 0;
	if(argc > 1 && argv[1][0] == '-' && argv[1][1] == 'n') {
		nflg++;
		argc--;
		argv++;
	}
	for(i=1; i<argc; i++) {
		fputs(argv[i], stdout);
		if (i < argc-1)
			putchar(' ');
	}
	if(nflg == 0)
		putchar('\n');
	exit(0);
}
